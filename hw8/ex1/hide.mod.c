#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x40d7414e, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x9b05bcc, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x7701e164, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xe0cb0001, __VMLINUX_SYMBOL_STR(kobject_del) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x52d6b6cc, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xac75c61f, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xc50643b5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x7dd241f6, __VMLINUX_SYMBOL_STR(init_task) },
	{ 0xf7afdae5, __VMLINUX_SYMBOL_STR(sysfs_remove_file_ns) },
	{ 0x688539b8, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0xbf091312, __VMLINUX_SYMBOL_STR(remove_proc_subtree) },
	{ 0xcc0c5a4c, __VMLINUX_SYMBOL_STR(find_module) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x35f183e, __VMLINUX_SYMBOL_STR(module_mutex) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "1291C0FDF0F4AFFE7C9E28D");
