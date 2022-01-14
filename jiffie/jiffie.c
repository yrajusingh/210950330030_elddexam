#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAJENDRA");

dev_t device_number;
bool dynamic = true;
struct class *my_class;
static struct cdev my_cdev;

static int jiffiedevice_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	return 0;
}

static int jiffiedevice_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	return 0;
}

ssize_t jiffiedevice_read(struct file *file, char __user *user_buffer,
		size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
	if (count < sizeof(jiffies))
		return -EINVAL;
	if (!put_user(jiffies, (u64 *)user_buffer))
            return sizeof(jiffies);
        else
            return -EFAULT;

}

ssize_t jiffiedevice_write(struct file *file, const char __user *user_buffer,
		size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
	return count;
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = jiffiedevice_open,
	.release = jiffiedevice_release,
	.read = jiffiedevice_read,
	.write = jiffiedevice_write
};


static int jiffie_device_init(void)
{
	int retval;
	pr_info("%s: In init\n", __func__);
	if (dynamic) {
		retval = alloc_chrdev_region(&device_number, 0, 1, "embedded");
	}
	else {
		device_number = MKDEV(180, 0);
		retval = register_chrdev_region(device_number, 1, "embedded");
	}
	if (!retval) {
		pr_info("%s: Major Number:%d\t Minor Number:%d\n",
				__func__, MAJOR(device_number), MINOR(device_number));
		my_class = class_create(THIS_MODULE, "my_driver_class");
		cdev_init(&my_cdev, &fops);
		retval = cdev_add(&my_cdev, device_number, 1);
		if (retval) {
			pr_info("%s: Failed in adding cdev to subsystem "
					"retval:%d\n", __func__, retval);
		}
		else {
			device_create(my_class, NULL, device_number, NULL, "jiffies");
		}
	}
	else
		pr_err("%s: Failed in allocating device number "
				"Error:%d\n", __func__, retval);
	return retval;
}

static void jiffie_device_exit(void)
{
	cdev_del(&my_cdev);
	device_destroy(my_class, device_number);
	class_destroy(my_class);
	unregister_chrdev_region(device_number, 1);
	pr_info("%s: In exit\n", __func__);
}

module_init(jiffie_device_init);
module_exit(jiffie_device_exit);
