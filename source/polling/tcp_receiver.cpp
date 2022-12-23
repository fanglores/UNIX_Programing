#include <poll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h> 

#include "lib_dbg.c"

int main()
{
    //set up tcp
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[100];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    while (true)
    {
        while ((n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0)
        {
            recvBuff[n] = 0;
            if (fputs(recvBuff, stdout) == EOF)
            {
                printf("\n Error : Fputs error\n");
            }
        }

        sleep(2);
    }

    close(listenfd);
    close(connfd);
}
