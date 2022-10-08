#include <linux/init.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fanglores");
MODULE_DESCRIPTION("Cringe");
MODULE_VERSION("0.9");

#define FOO_NAME "foo_chrdev"
dev_t Major;
int Device_Open = 0;
int signal_cnt = 0;
char msg[100];

// read-write operations
int foo_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "\t[OPEN] foo was open\n");
	signal_cnt = 0;
	
	Device_Open++;
	try_module_get(THIS_MODULE);
	
	return 0;
}

ssize_t foo_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	printk(KERN_INFO "\t[READ] foo was read\n");
	
	length = sizeof(int);
	memcpy(msg, &signal_cnt, length);
	
	copy_to_user(buffer, msg, length);
	signal_cnt++;
	
	return length;
}

int foo_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "\t[RELEASE] foo was released\n");
	Device_Open--;
	module_put(THIS_MODULE);
	
	return 0;
}

// ioctl
#define FOOIOC_1 'a'
#define FOOIOC_2 'b'
#define FOOIOC_3 'c'

static inline long foo_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "\t[IOCTL] foo was ioctl`ed\n");
	static int retval = 0;
	switch(cmd)
	{
		case FOOIOC_1:
			printk(KERN_INFO "a cmd is called\n");
			retval++;
			break;
		case FOOIOC_2:
			printk(KERN_INFO "b cmd is called\n");
			retval--;
			break;
		case FOOIOC_3:
			printk(KERN_INFO "c cmd is called\n");
			retval = 0;
			break;
		default:
			printk(KERN_ALERT "Unknown cmd is called\n");
			return -EINVAL;
	}
	
	return retval;
}

// threads
struct task_struct *ts;
int thread(void *data)
{
	while(true)
	{
		printk(KERN_INFO "I am a thread!!!\n");
		ssleep(5);
		
		if (kthread_should_stop())
			break;
	}
	
	return 0;
}

// file operations and module initialization/destruction
static const struct file_operations file_ops = {
	.read = foo_read,
	.unlocked_ioctl = foo_ioctl,
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
	printk(KERN_INFO "sudo mknod /dev/%s c %d 0\n", FOO_NAME, Major);
	
	//ts = kthread_run(thread, NULL, "foo_kthread");
	
	return 0;
}

void cleanup_module(void) 
{
	unregister_chrdev(Major, FOO_NAME);
	//kthread_stop(ts);
	printk(KERN_ALERT "Foo module disengaged!\n");
}
