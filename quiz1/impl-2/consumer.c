#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h> /* memory allocation */
#include <linux/delay.h>  /* use msleep function */
#include <linux/random.h>
#include <linux/spinlock.h> /* use spin lock */ 
#include <linux/kthread.h> 
#include <linux/string.h> /* use memcpy and strcpy */
#include "quiz1.h"
#include "buffer.h"

extern struct mutex lock;
extern struct buffer rbuf, wbuf; 

static struct task_struct *task;

static int consumer_thread_function(void *data)
{
	int sleep_ms = 999;  /* time to sleep */
	int count = 0;
	int i; 
	char *print_str; 
	
	s64 ns_before, ns_after; 
	struct timeval tv; 

	while (1){
		do_gettimeofday(&tv); 
		ns_before = timeval_to_ns(&tv); 

		if (kthread_should_stop())
			break; 

		mutex_lock(&lock); 
		memcpy(&rbuf, &wbuf, sizeof(struct buffer)); 
		buffer_clear(&wbuf); 
		mutex_unlock(&lock); 

		i = 0; print_str = rbuf.data[0]; 
		for(; i <= rbuf.tail; print_str = rbuf.data[++i]){
			printk(KERN_INFO "%s\n", print_str); 
			count++; 
		}

		printk(KERN_INFO "[Consumer] count = %d\n", count);

		do_gettimeofday(&tv); 
		ns_after = timeval_to_ns(&tv);

#ifdef DEBUG
		printk(KERN_ALERT "[Consumer] after = %lld, before = %lld, minus = %lld\n", 
		ns_after % 100000000 / 1000, 
		ns_before% 100000000 / 1000, 
		(ns_after - ns_before)/1000); 
#endif
		
		ms_sleep(sleep_ms - (ns_after - ns_before) / 1000000); 
	}
	return 0; 
}

static int __init consumer_init(void)
{
	printk(KERN_INFO "[Consumer] Consumer Starts. \n");
	task = kthread_run(&consumer_thread_function, NULL, "consumer");
	printk(KERN_INFO "[Consumer] Kernel Thread : %s\n", task->comm);
	return 0;
}

static void __exit consumer_exit(void)
{
	kthread_stop(task); 
	printk(KERN_INFO "Consumer exits. \n");
}

module_init(consumer_init);
module_exit(consumer_exit);

