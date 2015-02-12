/*
 * socket library for axweb
 */
#ifndef __ax_web_socket__
#define __ax_web_socket__

int ax_web_socket_server(char* addr,int port);
int ax_web_socket_accept(int socket_fd);
int ax_web_socket_write(int socket_fd,char* data,int len);
int ax_web_socket_close(int socket_fd);
#endif //(__ax_web_socket__)
