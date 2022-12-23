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
    int connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[100];
    time_t ticks;

    connfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    //set up polling
    pfds = calloc(1, sizeof(struct pollfd));

    pfds[0].fd = open(ap, O_RDONLY);
    printf("Opened fd %d\n", ap);

    pfds[0].events = POLLIN;

    //polling
    int num_open_fds = 1;
    while (num_open_fds > 0)
    {
        int ready;

        printf("About to poll()\n");
        ready = poll(pfds, 1, -1);
        printf("Ready: %d\n", ready);

        // Process received data
        if (pfds[0].revents != 0)
        {
            if (pfds[0].revents & POLLIN)
            {
                ssize_t s = read(pfds[0].fd, sendBuf, sizeof(sendBuf));

                write(connfd, sendBuf, strlen(sendBuf));
            }
            else
            {
                if (close(pfds[j].fd) == -1)
                    return 1;
                num_open_fds--;
            }
        }
    }

    close(connfd);
}
