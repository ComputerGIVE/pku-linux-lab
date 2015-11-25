/*
 *  newfork.c
 *
 *  System fork "stealing" sample.
 */

/*
 * Standard in kernel modules 
 */
#define _GNU_SOURCE
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module, */
#include <linux/moduleparam.h>	/* which will have params */
#include <linux/unistd.h>	/* The list of system calls */
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#include <asm/uaccess.h>

void **sys_call_table = (void **)0xffffffff81801440;  

static int uid;
module_param(uid, int, 0644);

static int cpu_id;
module_param(cpu_id, int, 0644);

static struct cpumask mask; 

typedef long (*t_setaff) (pid_t pid, const struct cpumask *cpumask); 
typedef long (*t_getaff) (pid_t pid, struct cpumask *cpumask); 
static t_setaff s_aff = (t_setaff) 0xffffffff8109cf60;  
static t_getaff g_aff = (t_getaff) 0xffffffff8109bac0; 

static int thread_function(void *data)
{
	int i = 0, child_pid = 0;
	struct task_struct *task;
	struct cpumask curmask; 

	while (1) {
		for_each_process(task){
			if (uid == (int)task->loginuid.val) {
	
				g_aff(task->pid, &curmask);
				/* printk("task->pid = %d\n"); */
				if (!cpumask_equal(&curmask, &mask)) {
					printk(KERN_INFO "User %d: process %d\n", uid, (int)
						task->pid);
					if (! s_aff(task->pid, &mask)) {
						printk(KERN_INFO "Affinity successfully modified.\n"); 
					} else {
						printk(KERN_ALERT "Failure.\n"); 
					}
				}
			}
		}
		msleep(2000); 
		if (kthread_should_stop())
			break; 
	}
}

static struct task_struct *this_task; 

/* 
 * Initialize the module - replace the system call 
 */
int init_module()
{
	cpumask_clear(&mask); 
	if (cpu_id & 1){
		printk("set 0\n"); 
		cpumask_set_cpu(0, &mask); 
	}
	if (cpu_id & 2){
		printk("set 1\n"); 
		cpumask_set_cpu(1, &mask); 
	}
	if (cpu_id & 4)
		cpumask_set_cpu(2, &mask); 
	if (cpu_id & 8)
		cpumask_set_cpu(3, &mask); 
    
	printk(KERN_INFO "Spying on UID:%d\n", uid);
	this_task = kthread_run(&thread_function, NULL, "spy"); 
	return 0;
}

/* 
 * Cleanup - unregister the appropriate file from /proc 
 */
void cleanup_module()
{
	kthread_stop(this_task); 
}
 
