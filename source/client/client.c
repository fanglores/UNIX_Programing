#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd;
	fd = open("/dev/foo_chrdev", O_RDWR);
	
	int cnt;
	while (1)
	{
		read(fd, &cnt, sizeof(int));
		printf("Got: %d\n", cnt);
		sleep(1);
	}
	
	return 0;
}
