#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IOCTL_MAGIC_NUMBER		'j'

// 디바이스와 애플리케이션 사이에서 정의된 식별자 (identifier)
// _IO(type,number): arg를 사용하지 않는 cmd 제작
// _IOR(type,number,size): 데이터를 읽어오는 cmd제작
// _IOW(type,number,size): 데이터를 쓰는 cmd 제작
// _IOWR(type,number,size): 데이터를 읽고 쓰는 cmd 제작
// 다른 디바이스 드라이버의 ioctl 명령과 구분하기 위해 사용 ,커맨드끼리의 식별 번호, 자료형
#define IOCTL_CMD_SUM			_IOWR( IOCTL_MAGIC_NUMBER, 0, int )
#define IOCTL_CMD_READ			_IOR( IOCTL_MAGIC_NUMBER, 1, int )
#define IOCTL_CMD_WRITE			_IOW( IOCTL_MAGIC_NUMBER, 2, int )

int main(void)
{
	int fd, num = 0;
	fd = open("/dev/ioctl_dev", O_RDWR);
	if(fd < 0){
		perror("Failed to open the device...");
	}

	while(1)
	{
		scanf("%d", &num);
		ioctl(fd, IOCTL_CMD_SUM, &num);
		printf("Result from kernel: %d\n", num);
	}

	close(fd);
	return 0;
}
