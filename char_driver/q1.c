#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>
int dev_no ;
int device_open (struct inode *,struct file *);
int device_release (struct inode *,struct file *);
struct cdev *device_cdev;

struct file_operations fops=
{
.owner = THIS_MODULE,
.open = device_open,
.release = device_release,
};

static int __init chardev_init (void)
{
    int result;
    int MAJOR;
    int MINOR;
    dev_no = MKDEV (244,0);
    MAJOR = MAJOR(dev_no);
    MINOR = MINOR(dev_no);
    printk(KERN_ALERT "char driver initialization function  dev no = %d\n",dev_no);
    printk(KERN_ALERT " char device  MAJOR = %d ,MINOR = %d \n",MAJOR ,MINOR);
     result = register_chrdev_region(dev_no,1,"device");

       if(result <0)
      {
        printk(KERN_ALERT "ERROR \n");
      }
     device_cdev = cdev_alloc ( );
       device_cdev->ops = &fops;
     result = cdev_add(device_cdev,dev_no,1);
     if(result <0)
    {
     printk(KERN_ALERT "ERROR \n");
    }
     return 0;
   }
static void __exit chardev_exit(void)
{
   unregister_chrdev_region(dev_no,1);
   cdev_del(device_cdev);
   printk(KERN_INFO "releasing char driver ....\n");
}
int device_open (struct inode *inode,struct file *filp)
{
      printk(KERN_ALERT "I am in open function \n");
   return 0;
 }
int device_release (struct inode *inode ,struct file *filp)
 {
   printk("I am in release function \n");
    return 0;
  }
  module_init (chardev_init);
  module_exit (chardev_exit);
MODULE_AUTHOR("RAJU");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OPEN CLOSE OPERATION IN CHAR DRIVER");
