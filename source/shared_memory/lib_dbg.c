#include "lib_dbg.h"

#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define KEY ((key_t)(1234))
#define SEGSIZE 1000
char* ap;
int msg_cnt = 0;

int dbg_open()
{
	int id = shmget(KEY, SEGSIZE, IPC_CREAT | 0666);
	if (id < 0) return 1;

	ap = (char*) shmat(id, 0, 0);
	return 0;
}


void dbg_write(const char* buf)
{
	time_t mytime = time(NULL);
	char* time_str = ctime(&mytime);
	time_str[strlen(time_str) - 1] = '\t';
	
	char* msg = (char*)malloc(100);
	strcpy(msg, time_str);

	printf("Temp value is [%s].\n", msg);

	strcat(msg, buf);

	printf("Sending value [%s]...\n", msg);
	
	if (msg_cnt > 0)
		sprintf((char*)(ap + msg_cnt * 100), "%s", msg);
	else
		sprintf(ap, "%s", msg);
	printf("Sent!\n");

	msg_cnt++;
	if(msg_cnt == 10) msg_cnt = 0;
}


void dbg_close()
{
	shmdt (ap);
}