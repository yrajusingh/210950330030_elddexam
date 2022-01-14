#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xeeab4c1e, "module_layout" },
	{ 0xc498609c, "device_destroy" },
	{ 0xf437babb, "kthread_stop" },
	{ 0x3c03d27a, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x7c038979, "class_destroy" },
	{ 0x2fbefc53, "wake_up_process" },
	{ 0xe554678a, "kthread_create_on_node" },
	{ 0xba9cf391, "device_create" },
	{ 0xbd59df1c, "__class_create" },
	{ 0x44d7ad45, "cdev_add" },
	{ 0xdc74c97c, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x1a81ff9c, "pv_ops" },
	{ 0xba8fbd64, "_raw_spin_lock" },
	{ 0xf9a482f9, "msleep" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "52F8AE84A10819BB3820D4D");
