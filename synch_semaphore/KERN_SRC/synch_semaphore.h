#define DRIVER_NAME "synch_semaphore"
#define PDEBUG(fmt,args...) printk(KERN_DEBUG"%s:"fmt,DRIVER_NAME, ##args)
#define PINFO(fmt,args...) printk(KERN_INFO"%s:"fmt,DRIVER_NAME, ##args)
#define PERR(fmt,args...) printk(KERN_ERR"%s:"fmt,DRIVER_NAME,##args)

#include<linux/init.h>
#include<linux/module.h>



#include<linux/device.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/semaphore.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/delay.h>
