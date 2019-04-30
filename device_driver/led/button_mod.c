#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>

#define A1 18

MODULE_LICENSE("GPL");

#define IOCTL_MAGIC_NUMBER 'H'

#define IOCTL_BUTTON_REQ        _IO( IOCTL_MAGIC_NUMBER, 2)

static int prev = 0;
static int now;

long button_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
    switch(cmd)
    {
        case IOCTL_BUTTON_REQ:
            now = gpio_get_value(A1);
            if(prev != now)
            {
                copy_to_user((void*)arg, &now, 4);
                prev = now;
            }
            break;
    }
}

struct file_operations fops = {
	.unlocked_ioctl = button_ioctl
};

static int __init button_init(void)
{
	printk(KERN_INFO "Button : Starting ...\n");

	register_chrdev(241, "button_dev", &fops);

	gpio_request(A1, "A1");
	gpio_direction_input(A1);

	printk(KERN_INFO "Button : Starting Complete\n");

	return 0;
}

static void __exit button_exit(void)
{
	gpio_free(A1);

	unregister_chrdev(241, "button_dev");

	printk(KERN_INFO "Button : Exit Done");
}

module_init(button_init);
module_exit(button_exit);
