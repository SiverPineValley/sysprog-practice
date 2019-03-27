#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd = 0;		// 파일 디스크립터 변수
	if(argc != 3)	// 0번은 현재 실행중인 파일 이름, 1번은 open할 파일 경로, 2번은 파일 모드 (octet)
	{
		fprintf(stderr,"usage: %s <file name> <acess mode>\n",argv[0]);
		fprintf(stderr,"access mode is octet number, ex:0755\n");
		return 1;
	}
	
	mode_t mode = 0;
	sscanf(argv[2],"0%o",&mode);	// string을 읽을 buffer, 스트링 형식, 저장할 변수
	fd = open(argv[1],O_WRONLY | O_CREAT | O_EXCL, mode);
	if(fd == -1)					// 이미 있는 파일은 오류 출력
	{
		perror("failed open ");
		return 1;
	}
	
	printf("success open %s\n",argv[1]);
	close(fd);

	return 0;
}
