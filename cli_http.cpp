#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>
int main(){
    int myscok = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(8888);
    connect(myscok,(sockaddr*)&serveraddr,sizeof(serveraddr));
	std::cout<<"cli_stret"<<std::endl;
	while(true){
		char buf[1024];
		memset(&buf,0,sizeof(buf));
		std::cout<<"please input your message"<<std::endl;
		std::cin>>buf;
		write(myscok,buf,sizeof(buf));
		memset(&buf,0,sizeof(buf));
		read(myscok,buf,sizeof(buf));
		std::cout<<buf<<std::endl;
	}
}
