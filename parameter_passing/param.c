#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


MODULE_AUTHOR("RAJU");

static char* name = "module";
static int num = 12;

module_param (name,charp,S_IRUGO);
module_param (num,int,S_IRUGO);

static int __init param_init (void)
{
  printk(KERN_ALERT "\n we are in init function \n");
  printk(KERN_ALERT "\n The value of name is %s\n",name);
  printk(KERN_ALERT "\n The value of  num is %d\n",num);
  return 0;
}
static void __exit param_exit (void)
{
printk(KERN_ALERT "\n bye bye\n");

}
module_init(param_init);
module_exit(param_exit);
