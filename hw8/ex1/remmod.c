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


static void free_notes_attrs(struct module_notes_attrs *notes_attrs,
			     unsigned int i)
{
	if (notes_attrs->dir) {
		while (i-- > 0)
			sysfs_remove_bin_file(notes_attrs->dir,
					      &notes_attrs->attrs[i]);
		kobject_put(notes_attrs->dir);
	}
	kfree(notes_attrs);
}

static void remove_notes_attrs(struct module *mod)
{
	if (mod->notes_attrs)
		free_notes_attrs(mod->notes_attrs, mod->notes_attrs->notes);
}

static void free_sect_attrs(struct module_sect_attrs *sect_attrs)
{
	unsigned int section;

	for (section = 0; section < sect_attrs->nsections; section++)
		kfree(sect_attrs->attrs[section].name);
	kfree(sect_attrs);
}

static void remove_sect_attrs(struct module *mod)
{
	if (mod->sect_attrs) {
		sysfs_remove_group(&mod->mkobj.kobj,
				   &mod->sect_attrs->grp);
		/* We are positive that no one is using any sect attrs
		 * at this point.  Deallocate immediately. */
		free_sect_attrs(mod->sect_attrs);
		mod->sect_attrs = NULL;
	}
}

void remove_module(struct module *mod)
{
	module_remove_modinfo_attrs(mod);
	_module_param_sysfs_remove(mod); 
	/* remove_notes_attrs(mod);
	remove_sect_attrs(mod); */
}
