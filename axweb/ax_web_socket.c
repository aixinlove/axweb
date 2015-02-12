#include "ax_web_socket.h"
int ax_web_socket_server(char* addr,int port){
	return -1;
}
int ax_web_socket_accept(int socket_fd){
	return -1;
}
int ax_web_socket_write(int socket_fd,char* data,int len){
	return -1;
}

int ax_web_socket_close(int socket_fd){
	return close(socket_fd);
}
