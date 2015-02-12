#include "ax_web.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "ax_web_socket.h"
/*
 * helper functions
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
int ax_web_default_req_handler(ax_web_ctx_p ctx,ax_web_request_p req){	
	ax_web_log1(ctx,ax_web_log_level_debug,"request","%s %s",req->method,req->path);
	return 0;
}

int ax_web_init(ax_web_ctx_p ctx){
	memset(ctx,0x0,sizeof(*ctx));
	ctx->runing=0;
	ctx->socket_fd=-1;
	ctx->req_handler=NULL;
	ctx->log_handler=NULL;
	return 0;
}
int ax_web_start(ax_web_ctx_p ctx,char* addr,int port){
	//create socket
	memcpy(ctx->listen_addr,addr,strlen(addr));
	ctx->listen_port=port;
	ctx->socket_fd=ax_web_socket_server(addr,port);
	if(ctx->socket_fd<0){
		return -1;
	}
	ax_web_log1(ctx,ax_web_log_level_info,"axweb","server run at %s:%d",addr,port);
	return 0;
}
int ax_web_close(ax_web_ctx_p ctx){
	if(ctx->socket_fd!=-1){
		ax_web_socket_close(ctx->socket_fd);
		ctx->socket_fd=-1;
	}
	return 0;
}
int ax_web_set_req_handler(ax_web_ctx_p ctx,ax_web_req_handler_t handler){
	ctx->req_handler=handler;
	return 0;
}	
ax_web_req_handler_t ax_web_get_req_handler(ax_web_ctx_p ctx){
	if(ctx->req_handler!=NULL){
		return (ax_web_req_handler_t)ctx->req_handler;
	}else{
		return ax_web_default_req_handler;
	}
}
int ax_web_set_log_handler(ax_web_ctx_p ctx,ax_web_log_handler_t handler){
	ctx->log_handler=handler;
	return 0;
}

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

