#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <linux/list.h>
#include <linux/slab.h>

struct data_node {
	char * str; 
	struct list_head link; 
}; 

struct data_node *new_node(char *data)
{
	struct data_node *node 
		= kmalloc(sizeof(struct data_node), GFP_KERNEL); 
	node->str = data; 
	INIT_LIST_HEAD(&(node->link)); 
	return node; 
}

inline void add_node(struct data_node *node, struct list_head *list)
{
	list_add(&(node->link), list); 
}

inline void add_node_tail(struct data_node *node, struct list_head *list)
{
	list_add_tail(&(node->link), list); 
}

inline void del_node(struct data_node *node)
{
	list_del(&(node->link)); 
	kfree(node->str); 
	kfree(node); 
}

#endif
