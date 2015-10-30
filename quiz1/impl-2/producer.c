#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h> /* memory allocation */
#include <linux/delay.h>  /* use msleep function */
#include <linux/random.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include "quiz1.h"
#include "buffer.h"

/*
 * 基本思路: 每sleep 一段时间, 就往[写缓冲区]里插入一个新节点。
 * 插入新的节点的时候，需要先对现在的[写缓冲区]上锁。
 * 每次consumer读的时候，把[写缓冲区]的内容拷贝到[读缓冲区]
 * 里去, 同时清空[写缓冲区]。然后把[读缓冲区]里的内容
 * 全部读出来。
 */

DEFINE_MUTEX(lock); 
struct buffer wbuf, rbuf; 

EXPORT_SYMBOL(lock); 
EXPORT_SYMBOL(wbuf); 
EXPORT_SYMBOL(rbuf); 

static struct task_struct *task;

static int producer_thread_function(void *data)
{
	int sleep_ms;  /* time to sleep */
	int count = 0;
	char print_str[STR_SIZE];
	s64 ns_before, ns_after; 
	struct timeval tv;

	while (1){
		do_gettimeofday(&tv); 
		ns_before = timeval_to_ns(&tv); 

		if (kthread_should_stop())
			break;

		sleep_ms = get_random_int() % 1024 + 1; 
		count++; 
		sprintf(print_str, "%s (%d): count %d random %d time %lld", 
			__func__, __LINE__, count, sleep_ms, 
			ns_before / 100000 % 1000000);

		/* add node to the linked list */

		mutex_lock(&lock);
		buffer_add(&wbuf, print_str); 
		mutex_unlock(&lock);

		do_gettimeofday(&tv); 
		ns_after = timeval_to_ns(&tv);

#ifdef DEBUG
		printk(KERN_ALERT"[Producer] after = %lld, before = %lld, minus = %lld\n", 
		  ns_after % 100000000 / 1000, 
		  ns_before% 100000000 / 1000, 
		  (ns_after - ns_before)/1000); 
#endif	  

		usleep_range(sleep_ms * 1000 -(ns_after-ns_before)/1000-50,
			     sleep_ms * 1000 -(ns_after-ns_before)/1000+50);
	}
	return 0; 
}

static int __init producer_init(void)
{
	printk(KERN_INFO "[Producer] Producer starts. \n");
	INIT_BUFFER(&wbuf); 
	INIT_BUFFER(&rbuf); 
	task = kthread_run(&producer_thread_function, NULL, "producer");
	printk(KERN_INFO "[Producer] Kernel Thread : %s\n",task->comm);
	return 0; 
}

static void __exit producer_exit(void)
{
	kthread_stop(task); 
	printk(KERN_INFO "Producer exits. \n"); 
}

module_init(producer_init); 
module_exit(producer_exit); 

