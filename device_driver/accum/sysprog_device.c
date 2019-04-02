#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

static char *buffer = NULL;
static int accum = 0;

int sysprog_device_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "sysprog_device open function called\n");
	return 0;
}

int sysprog_device_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "sysprog_device release function called\n");
	return 0;
}

ssize_t sysprog_device_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	int temp = 0;
	printk(KERN_ALERT "sysprog_device write function called\n");
	copy_from_user(buffer, buf, 1024);
	kstrtoint(buffer,10,&temp);
	accum += temp;
	printk(KERN_ALERT "[sysprog] Write the number: %d\n",temp);
	return count;
}

ssize_t sysprog_device_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "sysprog_device read function called\n");
	snprintf(buffer, 1024, "%d", accum);
	copy_to_user(buf, buffer, 1024);
	printk(KERN_ALERT "[sysprog] Read the number: %d\n",accum);
	return count;
}

static struct file_operations sys_fops = {
	.owner = THIS_MODULE,
	.read = sysprog_device_read,
	.write = sysprog_device_write,
	.open = sysprog_device_open,
	.release = sysprog_device_release
};

int __init sysprog_device_init(void)
{
	if(register_chrdev(255, "sysprog_device", &sys_fops) < 0 )
		printk(KERN_ALERT "[sysprog] driver init failed\n");
	else
		printk(KERN_ALERT "[sysprog] driver init successful\n");
	buffer = (char*) kmalloc(1024, GFP_KERNEL);
	if(buffer != NULL)
		memset(buffer, 0, 1024);
	return 0;
}

void __exit sysprog_device_exit(void)
{
	unregister_chrdev(255, "sysprog_device");
	printk(KERN_ALERT "[sysprog] driver cleanup\n");
	kfree(buffer);
}

// Funciton Pointer
// 함수 이름을 함수의 주소로 지정했다.
// 파라미터로 받은 프로시져(함수, 알고리즘)을 호출시켜준다. 일종의 콜백함수.
module_init(sysprog_device_init);	// module이 init될때 콜백
module_exit(sysprog_device_exit);	// module이 제거될때 콜백

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jongin Park");
MODULE_DESCRIPTION("This is the hello world example for device driver in system programming lecture.");
