#include "ax_web_socket.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
/*
 * private functions
 */
int ax_web_socket_set_nonblock(int socket_fd){
	int oldflags=fcntl(socket_fd,F_GETFL,0);
	if(fcntl(socket_fd,F_SETFL,oldflags|O_NONBLOCK)!=-1){
		return 0;
	}else{
		return -1;
	}	
}
int get_ip_by_hostname(char* ip,char *hostname){
	struct addrinfo *answer,hint;
	memset(&hint,0x0,sizeof(hint));
	hint.ai_family=AF_INET;
	hint.ai_socktype=SOCK_STREAM;
	if(getaddrinfo("baidu.com",NULL,&hint,&answer)!=0){
		return -1;
	}else{
		char addr[32];
		memset(addr,0x0,sizeof(addr));
		inet_ntop(AF_INET,&(((struct sockaddr_in *)answer->ai_addr)->sin_addr),addr,sizeof(addr));
		freeaddrinfo(answer);
		memcpy(ip,addr,strlen(addr));
		return 0;
	}		
}
/*
 * public functions
 */

int ax_web_socket_server(char* ipaddr,int port){
	//create socket
	int socketfd=socket(AF_INET,SOCK_STREAM,0);
	if(socketfd<=0){
		return -1;
	}
	//bind to given addr and port
	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(port);
	serveraddr.sin_addr.s_addr=inet_addr(ipaddr);	
	if(bind(socketfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))!=0){
			return -2;
	}
	//set to none block
	if(ax_web_socket_set_nonblock(socketfd)!=0){
		return -3;
	}	
	//listen
	if(listen(socketfd,1024)!=0){
		return -4;
	}
	return socketfd;
}
int ax_web_socket_accept(int socket_fd,char *remote_ip){
	int client_fd=-1;
	struct sockaddr_in clientaddr;
	socklen_t clientaddr_len=sizeof(clientaddr);
	client_fd=accept(socket_fd,(struct sockaddr *)&clientaddr,&clientaddr_len);
	if(client_fd<=0){
		return -1;
	}
	return client_fd;
}
int ax_web_socket_write(int socket_fd,char* data,int len){
	return write(socket_fd,data,len);
}
int ax_web_socket_read(int socket_fd,char* buffer,int expectlen){
	return read(socket_fd,buffer,expectlen);
}
int ax_web_socket_close(int socket_fd){
	return close(socket_fd);
}
