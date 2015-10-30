#include "quiz1.h"
#include "deque.h"
#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h> /* memory allocation */
#include <linux/delay.h>  /* use msleep function */
#include <linux/random.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>

#define STR_SIZE 100

/*
 * 基本思路: 每sleep 一段时间, 就往链表尾部插入一个新的节点。
 * 插入新的节点的时候，需要先对现在的[链表指针]上锁，使用
 * spin_lock, spin_unlock实现。
*/

extern spinlock_t lock;
extern struct list_head *list;

static struct task_struct *task;
static int consumer_thread_function(void *data)
{
	int sleep_ms = 1000;  /* time to sleep */
	int count = 0;
	struct list_head *list_backup; 

	struct list_head *position = NULL; 
	struct data_node *node = NULL; 
	struct data_node *lentry = NULL; 
	
	s64 ns_before, ns_after; 
	struct timeval tv; 

	while (1){
		do_gettimeofday(&tv); 
		ns_before = timeval_to_ns(&tv); 

		if (kthread_should_stop())
			break; 

		spin_lock(&lock); 
		list_backup = list; 
		list = (struct list_head *) kmalloc(sizeof(struct list_head),
						    GFP_KERNEL); 
		INIT_LIST_HEAD(list); 
		spin_unlock(&lock); 

		if (!list_empty(list_backup)){
			list_for_each(position, list_backup){
				node = list_entry(position, 
						  struct data_node, 
						  link); 
				printk(KERN_INFO "%s\n", node->str); 
				count++; 
			}
		}

		while (!list_empty(list_backup)){
			lentry = list_first_entry(list_backup, 
				 struct data_node, link);
			del_node(lentry); 
		}
		kzfree(list_backup); 

		printk(KERN_INFO "[Consumer] count = %d\n", count);

		do_gettimeofday(&tv); 
		ns_after = timeval_to_ns(&tv);

		/* printk(KERN_ALERT "[Consumer] after = %lld, before = %lld, minus = %lld\n", 
		 * ns_after % 100000000 / 1000, 
		 * ns_before% 100000000 / 1000, 
		 * (ns_after - ns_before)/1000); 
		 */ 

		/* ms_sleep(sleep_ms - (ns_after - ns_before) / 1000000);  */
		usleep_range(sleep_ms * 1000 - (ns_after - ns_before) / 1000 - 50, 
			     sleep_ms * 1000 - (ns_after - ns_before) / 1000 + 50); 
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

