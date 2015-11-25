/* 
 * The necessary header files 
 */

/*
 * Standard in kernel modules 
 */
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module, */
#include <linux/moduleparam.h>	/* which will have params */
#include <linux/unistd.h>	/* The list of system calls */
#include <linux/pid.h>          /* get_pid_task */
#include <linux/sched.h>
#include <linux/slab.h>		/* kmalloc */
#include <linux/mm.h>           /* get_user_pages */
#include <asm/uaccess.h>

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
static int v; /* verbosity */
module_param(v, int, 0644);

static int proc_id;
module_param(proc_id, int, 0644);

struct vm_area_struct **vmas; 
struct page **pages; 

struct vm_area_struct *(*gatevma)(struct mm_struct*) = (void*) 0xffffffff8101a550;
int (*wpr) (unsigned long, unsigned long, struct mm_walk *) = 
						       (void*) 0xffffffff811a67d0; 

static int pgd_entry(pgd_t *pgd, unsigned long addr, unsigned long next, struct
		 mm_walk *walk) 
{
	if (v >= 0)
		printk(KERN_INFO "pgd_entry: addr = %16lx, next = %16lx\n", addr, next);
	return 0; 
}
static int pud_entry(pud_t *pud, unsigned long addr, unsigned long next, struct
		 mm_walk *walk) 
{ 
	if (v >= 1)
		printk(KERN_INFO "pud_entry: addr = %16lx, next = %16lx\n", addr, next);
	return 0;
}
static int pmd_entry(pmd_t *pmd, unsigned long addr, unsigned long next, struct
		 mm_walk *walk) 
{ 
	if (v >= 2)
		printk(KERN_INFO "pmd_entry: addr = %16lx, next = %16lx\n", addr, next);
	return 0; 
}
static int pte_entry(pte_t *pte, unsigned long addr, unsigned long next, struct
		 mm_walk *walk) 
{ 
	if (v >= 3)
		printk(KERN_INFO "pte_entry: addr = %16lx, next = %16lx\n", addr, next);
	return 0; 
}

struct mm_walk walk = {
	.pgd_entry = pgd_entry, 
	.pud_entry = pud_entry, 
	.pmd_entry = pmd_entry, 
	.pte_entry = pte_entry
}; 
/* 
 * Initialize the module - replace the system call 
 */
int init_module()
{
	int i, tot_pages, n_pages; 
	struct task_struct * task;
	struct vm_area_struct *vm, *gate; 
	char maps_file_name; 



	tot_pages = 5; 
	vmas = kmalloc (tot_pages * sizeof(struct vm_area_struct *), GFP_KERNEL); 
	pages= kmalloc (tot_pages * sizeof(struct page *), GFP_KERNEL); 
	
	for_each_process(task){
		if (proc_id == (int)task->pid)
			break; 
	}

	printk(KERN_INFO "proc_id = %d\n", task->pid); 

	down_read(&task->mm->mmap_sem); 

	gate = gatevma(task->mm); 
	walk.mm = task->mm; 
	
	n_pages = get_user_pages(task, task->mm, 0x400000, 1, 0, 1, NULL, vmas); 
	up_read(&task->mm->mmap_sem);

	printk(KERN_INFO "n_pages = %d\n", n_pages); 
	printk(KERN_INFO "gate = %lx\n", gate); 

	vm = vmas[0]; 
	for (; 1; ) {
		if (vm < 0x400000)
			break; 
		if (vm == gate)
			break; 
		printk(KERN_INFO "  VM_AREA_STRUCT %8lx: \n", (void*)vm);
		/* printk(KERN_INFO "  struct_page: mapping: %lx, index: %lx\n", 
		pages[i]->mapping, pages[i]->index);  */
		printk(KERN_INFO "  Start: %8lx, End: %8lx\n",
		vm->vm_start, vm->vm_end); 
		wpr(vm->vm_start, vm->vm_end, &walk); 
		vm = vm->vm_next; 
	}

	kfree(vmas); 
	kfree(pages);
	return 0;
}

/* 
 * Cleanup - unregister the appropriate file from /proc 
 */
void cleanup_module()
{
}

MODULE_LICENSE("GPL"); 
 
