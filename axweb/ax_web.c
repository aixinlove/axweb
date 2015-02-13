#include "ax_web.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "ax_web_socket.h"
#include "ax_web_mem.h"
/*
 * log helper functions
 */
int ax_web_log0(ax_web_ctx_p ctx,enum ax_web_log_level level,char *category,char *filename,int line,char *fmt,...){
	va_list arg_ptr;
	va_start(arg_ptr,fmt);
	char msg[2*1024];
	memset(msg,0x0,sizeof(msg));
	vsprintf(msg,fmt,arg_ptr);
	va_end(arg_ptr);	
	char logline[2*1024];
	memset(logline,0x0,sizeof(logline));
	sprintf(logline,"%ld %s %s(%d) %s",time(NULL),category,filename,line,msg);
	ax_web_get_log_handler(ctx)(ctx,level,category,filename,line,logline);
	return 0;
}
/*
 * default handlers
 */

int ax_web_default_log_handler(ax_web_ctx_p ctx,enum ax_web_log_level level,char *category,char *filename,int line,char *msg){
	fprintf(stderr,"%s\n",msg);
	return 0;
}
/*
 * a very simple request handler.
 */
int ax_web_default_req_handler(ax_web_ctx_p ctx,ax_web_request_p req){	
	ax_web_log1(ctx,ax_web_log_level_debug,"request","%s %s",req->method,req->path);
	return 0;
}
/*
 * init the server context.
 */
ax_web_ctx_p ax_web_new(){
	ax_web_ctx_p ctx=(ax_web_ctx_p)ax_web_mem_alloc(sizeof(*ctx));
	memset(ctx,0x0,sizeof(*ctx));
	ctx->runing=0;
	ctx->socket_fd=-1;
	ctx->req_handler=NULL;
	ctx->log_handler=NULL;
	return ctx;
}
/*
 * accept client connection
 */
int ax_web_accept_client_socket(ax_web_ctx_p ctx,struct ax_web_connection *conn){
		
	int socket_fd=ax_web_socket_accept(ctx->socket_fd,conn->ipaddr);
	if(socket_fd<=0){
		return -1;
	}
	conn->socket_fd=socket_fd;
	conn->connect_time=time(NULL);
	return 0;
}
/*
 * main event loop
 */
int ax_web_loop(ax_web_ctx_p ctx){
	while(ctx->runing){
		struct ax_web_connection conn;
		if(ax_web_accept_client_socket(ctx,&conn)!=0){
			ax_web_log_e(ctx,"accept client error");
		}else{
			ax_web_log_i(ctx,"new client incomming");
		}
	}
	return 0;
}
/*
 * start web server.
 */
int ax_web_start(ax_web_ctx_p ctx,char* addr,int port){
	//create socket
	memcpy(ctx->listen_addr,addr,strlen(addr));
	ctx->listen_port=port;
	int socketfd=ax_web_socket_server(addr,port);
	if(socketfd<0){
		ax_web_log_e(ctx,"socket error");
		return -1;
	}
	ctx->socket_fd=socketfd;
	ax_web_log_i(ctx,"server run at %s:%d",addr,port);
	//start run loop
	ctx->runing=1;
	ax_web_loop(ctx);
	return 0;
}
/*
 * stop server
 */
int ax_web_stop(ax_web_ctx_p ctx){
	//close server socket
	if(ctx->socket_fd!=-1){
		ax_web_socket_close(ctx->socket_fd);
		ctx->socket_fd=-1;
	}
	//close all client socket
	return 0;
}
/*
 * close server
 */
int ax_web_close(ax_web_ctx_p ctx){
	//clean
	//
	ax_web_mem_free(ctx,sizeof(*ctx));
	return 0;
}
/*
 * set request haqndler
 */
int ax_web_set_req_handler(ax_web_ctx_p ctx,ax_web_req_handler_t handler){
	ctx->req_handler=handler;
	return 0;
}	
/*
 * get request handler
 */
ax_web_req_handler_t ax_web_get_req_handler(ax_web_ctx_p ctx){
	if(ctx->req_handler!=NULL){
		return (ax_web_req_handler_t)ctx->req_handler;
	}else{
		return ax_web_default_req_handler;
	}
}
/*
 * set loghandler
 */
int ax_web_set_log_handler(ax_web_ctx_p ctx,ax_web_log_handler_t handler){
	ctx->log_handler=handler;
	return 0;
}
/*
 * get log handler
 */
ax_web_log_handler_t ax_web_get_log_handler(ax_web_ctx_p ctx){
	if(ctx->log_handler!=NULL){
		return (ax_web_log_handler_t)ctx->log_handler;
	}else{
		return ax_web_default_log_handler;
	}
}
/*
 * response functions
 */
int ax_web_write(ax_web_ctx_p ctx,ax_web_request_p req,char *data,int len){
	return 0;
}

