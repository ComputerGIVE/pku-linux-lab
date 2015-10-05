#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#define DRIVER_AUTHOR "Li Yilong"
#define DRIVER_DESC "A sample driver"

static int __init hello_4_init(void)
{
    printk(KERN_INFO "Hello, world 4. \n"); 
    return 0; 
}

static void __exit hello_4_exit(void)
{
    printk(KERN_INFO "Goodbye, world 4. \n"); 
}

module_init(hello_4_init); 
module_exit(hello_4_exit); 

MODULE_LICENSE("GPL"); 

MODULE_AUTHOR(DRIVER_AUTHOR); 
MODULE_AUTHOR(DRIVER_DESC); 
MODULE_SUPPORTED_DEVICE("testdevice");
