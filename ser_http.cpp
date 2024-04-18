#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>

#define SERVER_PORT 8888
int main(){
	int mysock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(SERVER_PORT);

	bind(mysock,(sockaddr*)&serv_addr,sizeof(serv_addr));
	listen(mysock,128);

	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_len = sizeof(clnt_addr);
	int clntsock = socket(AF_INET,SOCK_STREAM,0);
	memset(&clnt_addr,0,clnt_addr_len);

	clntsock = accept(mysock,(sockaddr*)&clnt_addr,&clnt_addr_len);
	std::cout<<
		"new client fd "<<clntsock<<
		"! IP: "<<inet_ntoa(clnt_addr.sin_addr)<<
		"  Port: "<<ntohs(clnt_addr.sin_port)<<"\n";

	while(true){
		char buf[1024];
		memset(&buf,0,sizeof(buf));
		size_t redsize = read(clntsock,buf,sizeof(buf));
		if(redsize >0){
		std::cout<<"get massage from "<<clntsock<<std::endl<<buf<<std::endl;
		write(clntsock,buf,sizeof(buf));
		}
		else if(redsize == 0){
			std::cout<<"massage end"<<std::endl;
			close(clntsock);
			break;
		}
		else if(redsize == -1){
			std::cout<<"bad read"<<std::endl;
			break;
		}
	}

}



