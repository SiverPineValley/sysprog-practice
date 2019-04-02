#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IOCTL_MAGIC_NUMBER			'j'

#define IOCTL_CMD_SUM				_IOWR( IOCTL_MAGIC_NUMBER, 0, int )
#define IOCTL_CMD_READ				_IOR( IOCTL_MAGIC_NUMBER, 1, int )
#define IOCTL_CMD_WRITE				_IOW( IOCTL_MAGIC_NUMBER, 2, int )

int main(void)
{
	int num = 0, fd;
	int breakLoop = 0;
	char input[8];

	fd = open("/dev/ioctl_dev", O_RDWR);
	if(fd < 0)
		perror("failed to open the device...");

	while(!breakLoop)
	{
		printf("Please enter the operations(w/r/q) : ");
		scanf("%s", input);
		switch(input[0])
		{
			case 'q' :
				breakLoop = 1;
				break;

			case 'w' :
				printf("Enter the data to write: ");
				scanf("%d", &num);
				ioctl(fd, IOCTL_CMD_WRITE, &num);
				break;

			case 'r' :
				ioctl(fd, IOCTL_CMD_READ, &num);
				printf("The data in device is %d\n", num);
				break;
		}
	}

	close(fd);
	return 0;
}
