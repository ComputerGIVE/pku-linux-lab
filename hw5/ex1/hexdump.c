#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>

extern char __initdata boot_command_line[];
extern char* saved_command_line;

int init_module(void)
{
	printk(KERN_INFO "print_hex_dump starts. \n"); 
	
	printk(KERN_INFO "print hexdump of boot_command_line_addr\n"); 
	print_hex_dump(KERN_INFO, "boot: ", DUMP_PREFIX_ADDRESS, 
		       16, 1, boot_command_line, 512, 1); 
	
	printk(KERN_INFO "print hexdump of saved_command_line_addr\n"); 
	print_hex_dump(KERN_INFO, "save: ", DUMP_PREFIX_ADDRESS, 
		       16, 1, saved_command_line, 512, 1); 
	return 0; 
}

void cleanup_module(void)
{
	printk(KERN_INFO "print_hex_dump exits. \n"); 
}
