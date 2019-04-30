#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IOCTL_MAGIC_NUMBER	'H'
#define IOCTL_LED_ON	    	_IO( IOCTL_MAGIC_NUMBER, 0)
#define IOCTL_LED_OFF	    	_IO( IOCTL_MAGIC_NUMBER, 1)
#define IOCTL_BUTTON_REQ        _IO( IOCTL_MAGIC_NUMBER, 2)

int main(int argc, char ** argv)
{
	int fd_led = open("/dev/led_dev",O_RDWR);
    int fd_but = open("/dev/button_dev",O_RDWR);
    int led = 1;
    int prev = -1;

    if( fd_led < 0 || fd_but < 0 )
    {
        perror("Failed to open the device");
    }

    while(1)
    {
        ioctl(fd_but, IOCTL_BUTTON_REQ, &led);
        //if(led == 0) led = 1;
        //else led = 0;

        if(led == 1)
        {
            ioctl(fd_led, IOCTL_LED_OFF, 0);
            prev = led;
        }
        else if(led == 0)
        {
            ioctl(fd_led, IOCTL_LED_ON, 0);
            prev = led;
        }
    }

	close(fd_led);
    close(fd_but);
	return 0;
}
