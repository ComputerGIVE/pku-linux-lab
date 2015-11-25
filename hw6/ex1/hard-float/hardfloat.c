#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <asm/i387.h>

static int  __init init_float(void)
{
	double a, b;
	kernel_fpu_begin(); 
	a = 3.1415926; 
	b = 1.2345678; 
	printk(KERN_INFO "[hard-float] hex(a) = %llx\n", *((u64*)&a)); 
	printk(KERN_INFO "[hard-float] hex(b) = %llx\n", *((u64*)&b)); 
	b = a * b; 
	printk(KERN_INFO "[hard-float] hex(a*b) = %llx\n", *((u64*)&b)); 
	kernel_fpu_end(); 
	return 0; 
}

static void __exit exit_float(void)
{
	printk(KERN_INFO "[hard-float] Goodbye.\n");
}

module_init(init_float); 
module_exit(exit_float); 


