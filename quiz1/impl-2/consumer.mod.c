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
	{ 0xac75c61f, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x688539b8, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x52d6b6cc, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x7701e164, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb075147d, __VMLINUX_SYMBOL_STR(rbuf) },
	{ 0x78959b0d, __VMLINUX_SYMBOL_STR(wbuf) },
	{ 0xc50643b5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x951d2df, __VMLINUX_SYMBOL_STR(lock) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x4f68e5c9, __VMLINUX_SYMBOL_STR(do_gettimeofday) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=producer";


MODULE_INFO(srcversion, "6AF8109DD928BB68B0A5C77");
