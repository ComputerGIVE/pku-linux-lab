#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h> /* memory allocation */
#include <linux/delay.h>  /* use msleep function */
#include <linux/random.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include "quiz1.h"
#include "deque.h"
#define STR_SIZE 100

/*
 * 基本思路: 每sleep 一段时间, 就往链表尾部插入一个新的节点。
 * 插入新的节点的时候，需要先对现在的[链表指针]上锁，使用
 * spin_lock, spin_unlock实现。
 */

DEFINE_SPINLOCK(lock); 
struct list_head *list; 

EXPORT_SYMBOL(lock); 
EXPORT_SYMBOL(list); 

static struct task_struct *task;

static int producer_thread_function(void *data)
{
	int sleep_ms;  /* time to sleep */
	int count = 0;
	struct data_node *node = NULL; 
	char *print_str;
	/* the string which will be printed, dynamically 
	 * allocated every time and will be freed when 
	 * it s been printed.
	 */
	
	s64 ns_before, ns_after; 
	struct timeval tv;

	list = kzalloc(sizeof (struct list_head), GFP_KERNEL); 
	INIT_LIST_HEAD(list); 
	
	while (1){
		do_gettimeofday(&tv); 
		ns_before = timeval_to_ns(&tv); 

		if (kthread_should_stop())
			break;

		sleep_ms = get_random_int() % 1024 + 1; 
		count++; 
		print_str = (char *) kcalloc(STR_SIZE, 
					     sizeof(char), GFP_KERNEL); 
		sprintf(print_str, "%s (%d): count %d random %d time %lld", 
			__func__, __LINE__, count, sleep_ms, ns_before / 100000 %
			1000000);
		node = new_node(print_str); 

		/* add node to the linked list */
		/* 加不加锁? 对方写list的时候你在读...gg */

		spin_lock(&lock); 
		add_node_tail(node, list);
		spin_unlock(&lock);

		do_gettimeofday(&tv); 
		ns_after = timeval_to_ns(&tv);

		/* printk(KERN_ALERT "[Producer] after = %lld, before = %lld,
		 * minus = %lld\n", 
		 * ns_after % 100000000 / 1000, 
		 * ns_before% 100000000 / 1000, 
		 * (ns_after - ns_before)/1000); 
		 */ 

		usleep_range(sleep_ms * 1000 - (ns_after - ns_before) / 1000 - 10, 
			     sleep_ms * 1000 - (ns_after - ns_before) / 1000 + 10);
	}
	return 0; 
}

static int __init producer_init(void)
{
	printk(KERN_INFO "[Producer] Producer starts. \n");
	task = kthread_run(&producer_thread_function, NULL, "producer");
	printk(KERN_INFO "[Producer] Kernel Thread : %s\n",task->comm);
	return 0; 
}

static void __exit producer_exit(void)
{
	struct data_node *lentry = NULL;
	kthread_stop(task); 
	while (!list_empty(list)){
		lentry = list_first_entry(list, struct data_node, link); 
		del_node(lentry); 
	}
	printk(KERN_INFO "Producer exits. \n"); 
}

module_init(producer_init); 
module_exit(producer_exit); 

