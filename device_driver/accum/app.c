#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int dev;
	// int accum = 0;
	char buff[1024];

	printf("Device driver test.\n");

	dev = open("/dev/sysprog_device",O_RDWR);
	if(dev == -1)
	{
		perror("failed open because ");
		return 1;
	}
	printf("dev = %d\n", dev);
	
	int a = 0;
	while(a != -1)
	{
		printf("Input the number: ");
		scanf("%d",&a);
		if(a == -1) break;
		// accum += a;
		sprintf(buff, "%d", a);
		printf("Write the number %s to kernel\n",buff);
		write(dev, buff, strlen(buff));
		read(dev, buff, strlen(buff));
		printf("Read from device: %s\n\n", buff);
	}
	close(dev);

	exit(EXIT_SUCCESS);
}
