#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fanglores");
MODULE_DESCRIPTION("Cringe");
MODULE_VERSION("0.9");

#define FOO_NAME "foo_chrdev"
dev_t Major;
int Device_Open = 0;
int signal_cnt = 0;
char msg[100];

int foo_open(struct inode *inode, struct file *file)
{
	signal_cnt = 0;
	if (Device_Open)
		return -EBUSY;
	
	Device_Open++;
	try_module_get(THIS_MODULE);
	
	return 0;
}

ssize_t foo_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	memcpy(msg, &signal_cnt, sizeof(int));
	
	if(length > 100)
		length = 100;
	
	copy_to_user(buffer, msg, length);
	signal_cnt++;
	
	return length;
}

int foo_release(struct inode *inode, struct file *file)
{
	Device_Open--;
	module_put(THIS_MODULE);
	
	return 0;
}

struct file_operations file_ops = {
	.read = foo_read,
	//.write = foo_write,
	.open = foo_open,
	.release = foo_release
};


int init_module(void) 
{
	Major = register_chrdev(0, FOO_NAME, &file_ops);
	if (Major < 0)
	{
		printk(KERN_ALERT "Error while registering chrdev with %d\n", Major);
		return Major;
	}
	
	printk(KERN_INFO "foo chrdev has got major number %d\n", Major);
	printk(KERN_INFO "use mknod /dev/%s c %d 0\n", FOO_NAME, Major);

	return 0;
}

void cleanup_module(void) 
{
	unregister_chrdev(Major, FOO_NAME);
	printk(KERN_ALERT "Foo module disengaged!\n");
}
