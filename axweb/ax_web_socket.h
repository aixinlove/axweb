/*
 * socket library for axweb
 */
#ifndef __ax_web_socket__
#define __ax_web_socket__
int ax_web_socket_set_nonblock(int socketfd);
int get_ip_by_hostname(char* ip,char *hostname);
int ax_web_socket_server(char* ipaddr,int port);
int ax_web_socket_accept(int socket_fd,char* remote_ip);
int ax_web_socket_write(int socket_fd,char* data,int len);
int ax_web_socket_read(int socket_fd,char* buffer,int expectlen);
int ax_web_socket_close(int socket_fd);
#endif //(__ax_web_socket__)
