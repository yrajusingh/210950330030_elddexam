#include<linux/module.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include<asm/rwonce.h>

static int __init hello_init(void)
{
printk("Hello world\n");
return 0;
}
static void __exit hello_exit(void)
{
printk("Good Bye\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAJU");
MODULE_DESCRIPTION("A simple hello_world kernel module");
