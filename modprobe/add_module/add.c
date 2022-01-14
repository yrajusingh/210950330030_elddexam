#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

static int add(int arr[],int n)
{
  int i,sum=0;

for (i=0;i<n;i++)
{
   sum += arr[i];
}
  printk(KERN_ALERT "\n add = %d \n",sum);
   return sum;
}
EXPORT_SYMBOL_GPL(add);
static int  __init add_init (void)
{
  printk(KERN_ALERT "\n radhe radhe\n");
  return 0;
}
static void __exit add_exit(void)
{
   printk(KERN_ALERT "\n  bye bye\n");
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAJU SINGH YADAV");
module_init(add_init);
module_exit(add_exit);
