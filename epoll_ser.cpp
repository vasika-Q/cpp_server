#include<iostream>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/fcntl.h>
#include<error.h>
#include<cstring>
#define MYPORT 8888
#define MAX_EVENT 1024
#define MAX_BUFF 1024

int main(){
    int listen_sok = socket(AF_INET,SOCK_STREAM,0);
    fcntl(listen_sok,fcntl(listen_sok,F_GETFL)|O_NONBLOCK);
    struct sockaddr_in listen_addr;
    memset(&listen_addr,0,sizeof(listen_addr));
    listen_addr.sin_addr =  inet_addr("127.0.0.1");
    listen_addr.sin_addr = AF_INET;
    listen_addr.sin_port = htons(MYPORT);
    bind(listen_sok,(sockaddr*)&listen_addr,sizeof(listen_addr));
    listen(listen_sok,SOMAXCONN);
    int epfd = epoll_create1(0);
    epoll_event events[MAX_EVENT],en;
    memset(&en,0,sizeof(en));
    en.data.fd = listen_sok;
    epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sok,&en);
    while (1)
    {
        int mark = epoll_wait(epfd,events,MAX_EVENT,-1)
    }
    

}