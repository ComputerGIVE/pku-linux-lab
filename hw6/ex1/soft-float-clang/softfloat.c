#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int  __init init_float(void)
{
	double a = 3.1415926; 
	double b = 1.2345678; 
	printk(KERN_INFO "[soft-float] hex(a) = %llx\n", *((u64*)&a)); 
	printk(KERN_INFO "[soft-float] hex(b) = %llx\n", *((u64*)&b)); 
	b = a * b; 
	printk(KERN_INFO "[soft-float] hex(a*b) = %llx\n", *((u64*)&b)); 
	return 0; 
}

static void __exit exit_float(void)
{
	printk(KERN_INFO "[soft-float] Goodbye.\n");
}

module_init(init_float); 
module_exit(exit_float); 


