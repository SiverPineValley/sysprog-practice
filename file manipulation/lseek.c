#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int fd;
	int i, buf;

	// 파일 열기.
	fd = open("num.dat", O_RDWR | O_CREAT, 0777);
	if( fd < 0 )
	{
		perror("error: ");
		exit(1);
	}

	// 1000에서 1009까지 10개의 문자 쓰기
	for(i = 1000; i < 1010; i++)
		write(fd, (void *)&i, sizeof(i));

	// 파일 시작점에서 0만큼 포인터 이동 후 읽기
	lseek(fd, 0, SEEK_SET);
	read(fd, (void *)&buf, sizeof(i));
	printf("%d\n",buf);

	// 파일 시작점에서 7만큼 포인터 이동 후 읽기
	lseek(fd, 7*sizeof(i), SEEK_SET);
	read(fd, (void *)&buf, sizeof(i));
	printf("%d\n", buf);
	return 0;
}
