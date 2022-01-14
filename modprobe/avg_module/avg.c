#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include "add.h"

static int n = 5;
static int arr[5] = {10,20,30,40,50};
static int __init avg_init (void)
{
   printk(KERN_ALERT "\n going to add functionality\n");
  printk(KERN_ALERT "\n avg =  %d\n",(add(arr,n))/n);

  return 0;
}
 static void __exit avg_exit(void)
{
   printk(KERN_ALERT "\n leaving bye \n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAJU SINGH YADAV");
module_init(avg_init);
module_exit(avg_exit);
