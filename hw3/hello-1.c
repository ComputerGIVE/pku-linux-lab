#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void)
{
    printk(KERN_INFO "Hello world 1. \n"); 

    /*
     * A non 0 return means init_module failed; module can't be loaded. 
     */ 
    return 0; 
}

int cleanup_module(void)
{
    printk(KERN_INFO "Goodbye world 1. \n"); 
}


