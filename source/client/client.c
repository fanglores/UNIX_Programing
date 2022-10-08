#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd;
	fd = open("/dev/foo_chrdev", O_RDWR);
	if(fd < 0)
	{
		printf("Error while opening! %d\n", fd);
		return 0;
	}	
	printf("got fd: %d\n\nOutput:\n", fd);	

	int cnt;
	while (1)
	{
		read(fd, &cnt, sizeof(int));
		printf("Got: %d\n", cnt);
		sleep(1);
	}
	
	close(fd);
	return 0;
}
