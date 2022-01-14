#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>                 //kmalloc()
#include <linux/uaccess.h>              //copy_to/from_user()
 
#include <linux/kthread.h>
#include <linux/completion.h>           // Required for the completion
 
 
uint32_t read_count = 0;
static struct task_struct *wait_thread;
 
struct completion data_read_done;
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev comp_cdev;
int completion_flag = 0;
 
static int __init comp_driver_init(void);
static void __exit comp_driver_exit(void);
 
/*************** Driver Functions **********************/
static int comp_open(struct inode *inode, struct file *file);
static int comp_release(struct inode *inode, struct file *file);
static ssize_t comp_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t comp_write(struct file *filp, const char *buf, size_t len, loff_t * off);
/******************************************************/

//File operation structure
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = comp_read,
        .write          = comp_write,
        .open           = comp_open,
        .release        = comp_release,
};

/*
** Waitqueue thread
*/ 
static int wait_function(void *unused)
{
        
        while(1) {
                pr_info("Waiting For Event...\n");
                wait_for_completion (&data_read_done);
                if(completion_flag == 2) {
                        pr_info("Event Came From Exit Function\n");
                        return 0;
                }
                pr_info("Event Came From Read Function - %d\n", ++read_count);
                completion_flag = 0;
        }
        do_exit(0);
        return 0;
}

/*
** This function will be called when we open the Device file
*/ 
static int comp_open(struct inode *inode, struct file *file)
{
        pr_info("Device File Opened...!!!\n");
        return 0;
}

/*
** This function will be called when we close the Device file
*/ 
static int comp_release(struct inode *inode, struct file *file)
{
        pr_info("Device File Closed...!!!\n");
        return 0;
}

/*
** This function will be called when we read the Device file
*/
static ssize_t comp_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        pr_info("Read Function\n");
        completion_flag = 1;
        if(!completion_done (&data_read_done)) {
            complete (&data_read_done);
        }
        return 0;
}

/*
** This function will be called when we write the Device file
*/
static ssize_t comp_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        pr_info("Write function\n");
        return len;
}

/*
** Module Init function
*/
static int __init comp_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "comp_Dev")) <0){
                pr_err("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&comp_cdev,&fops);
        comp_cdev.owner = THIS_MODULE;
        comp_cdev.ops = &fops;
 
        /*Adding character device to the system*/
        if((cdev_add(&comp_cdev,dev,1)) < 0){
            pr_err("Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"comp_class")) == NULL){
            pr_err("Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"comp_device")) == NULL){
            pr_err("Cannot create the Device 1\n");
            goto r_device;
        }
 
        //Create the kernel thread with name 'mythread'
        wait_thread = kthread_create(wait_function, NULL, "WaitThread");
        if (wait_thread) {
                pr_info("Thread Created successfully\n");
                wake_up_process(wait_thread);
        } else {
                pr_err("Thread creation failed\n");
        }
 
        //Initializing Completion
        init_completion(&data_read_done);
 
        pr_info("Device Driver Insert...Done!!!\n");
        return 0;
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}

/*
** Module exit function
*/ 
static void __exit comp_driver_exit(void)
{
        completion_flag = 2;
        if(!completion_done (&data_read_done)) {
            complete (&data_read_done);
        }
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&comp_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!!\n");
}
 
module_init(comp_driver_init);
module_exit(comp_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAJENDRA");
MODULE_DESCRIPTION("A simple device driver - Completion (Dynamic Method)");
