#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/delay.h>

#define IOCTL_MAGIC_NUMBER			'j'

#define IOCTL_CMD_SUM				_IOWR( IOCTL_MAGIC_NUMBER, 0, int )
#define IOCTL_CMD_READ				_IOR( IOCTL_MAGIC_NUMBER, 1, int )
#define IOCTL_CMD_WRITE				_IOW( IOCTL_MAGIC_NUMBER, 2, int )

static int sum = 0;
static int number = 0;

//struct semaphore sem;
struct rw_semaphore rwsem;

int sysprog_open(struct inode *inode, struct file *filep)
{
	printk(KERN_INFO "[SYSPROG] open function called\n");
	
	// printk("Holding Semaphore\n");
	// down_interruptible(&sem);
	return 0;
}

int sysprog_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "[SYSPROG] release function called\n");
	
	// prink("Releasing Semaphore\n");
	// up(&sem);
	return 0;
}

long sysprog_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int temp = 0;
	switch(cmd)
	{
	case IOCTL_CMD_SUM:
		copy_from_user(&temp, (const void*)arg, 4);
		sum += temp;
		copy_to_user((void*) arg, &sum, 4);
		break;

	case IOCTL_CMD_READ:
		down_read(&rwsem);
		copy_to_user((void*)arg, &number, 4);
		
		ssleep(10);
		up_read(&rwsem);
		break;

	case IOCTL_CMD_WRITE:
		down_write(&rwsem);
		copy_from_user(&number,(const void*)arg, 4);
		up_write(&rwsem);
		break;
	}

	return 0;
}

struct file_operations sys_fops = {
	.open = sysprog_open,
	.release = sysprog_release,
	.unlocked_ioctl = sysprog_ioctl,
};

int __init sysprog_device_init(void)
{
	if(register_chrdev(255, "sysprog_device", &sys_fops) < 0 )
		printk(KERN_INFO "[SYSPROG] driver init failed\n");
	else
		printk(KERN_INFO "[SYSPROG] driver init successful\n");
	
	// sema_init(&sem, 1);
	init_rwsem(&rwsem);
	return 0;
}

void __exit sysprog_device_exit(void)
{
	unregister_chrdev(255, "sysprog_device");
	printk(KERN_INFO "[SYSPROG] driver cleanup successful\n");
}

module_init(sysprog_device_init);
module_exit(sysprog_device_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jongin Park");
