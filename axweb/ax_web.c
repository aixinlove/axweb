#include "ax_web.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "ax_web_socket.h"
#include "ax_web_mem.h"
#include "ax_web_request.h"
#include "ax_web_log.h"
#include "ax_web_mem.h"
#define ax_web_max_num_of_event 1024
#define ax_web_event_timeout 10

/*
 * init the server context.
 */
ax_web_ctx_p ax_web_new(){
	ax_web_ctx_p ctx=(ax_web_ctx_p)ax_web_mem_alloc(sizeof(*ctx));
	ctx->runing=0;
	ctx->socket_fd=-1;
	ctx->req_handler=NULL;
	ctx->log_handler=NULL;
	ctx->event_ctx=ax_web_event_new(ctx);
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

int ax_web_handle_one_event(ax_web_ctx_p ctx,ax_web_event_p e){
	if(e->fd==ctx->socket_fd){//accept
		ax_web_request_p req=ax_web_request_new();
		if(ax_web_accept_client_socket(ctx,&(req->connection))!=0){
			ax_web_log_e(ctx,"accept client error");
			ax_web_request_close(req);
		}else{
			ax_web_log_i(ctx,"new client incomming");
			//add client to event loop
			ax_web_event_push(ctx->event_ctx,req->connection.socket_fd,ax_web_event_type_read,req);
			//ax_web_event_push(ctx->event_ctx,req->connection.socket_fd,ax_web_event_type_write,req);
		}
	}else{//client fd
		ax_web_log_i(ctx,"client event");	

		//read event ->read data to request's inbuffer
		//if read error then goto error
		//write event ->write out request's outbuffer
		//if write error then goto error
		//
		//error:
		//
		//after all complete ,clearn resource
		//1. remvoe client from event loop
		//2. close request

	}
	return 0;
}
/*
 * main event loop
 */
int ax_web_loop(ax_web_ctx_p ctx){
	struct ax_web_event_t events[ax_web_max_num_of_event];
	while(ctx->runing){
		int timeouttime=ax_web_event_timeout;
		if(ctx->idle_handler!=NULL){
			timeouttime=0;
		}
		int num_of_event=ax_web_event_wait(ctx->event_ctx,events,ax_web_max_num_of_event,timeouttime);
		if(num_of_event==0&&ctx->idle_handler!=NULL){
			ax_web_idle_handler_t handler=(ax_web_idle_handler_t)ctx->idle_handler;
			handler(ctx);
		}else{
			int i=0;
			for(i=0;i<num_of_event;i++){
				ax_web_event_p e=&(events[i]);
				ax_web_handle_one_event(ctx,e);
			}	
		}
	}
	return 0;
}
/*
 * start web server.
 */
int ax_web_start(ax_web_ctx_p ctx,char* addr,int port,char* document_path){
	//create socket
	memcpy(ctx->listen_addr,addr,strlen(addr));
	memcpy(ctx->document_path,document_path,strlen(document_path));
	ctx->listen_port=port;
	int socketfd=ax_web_socket_server(addr,port);
	if(socketfd<0){
		ax_web_log_e(ctx,"socket error");
		return -1;
	}
	ctx->socket_fd=socketfd;
	//add server to event loop
	ax_web_event_push(ctx->event_ctx,ctx->socket_fd,ax_web_event_type_read,NULL);
	ax_web_log_a(ctx,"server run at %s:%d",addr,port);
	//start run loop
	ctx->runing=1;
	ax_web_loop(ctx);
	return 0;
}
/*
 * stop server
 */
int ax_web_stop(ax_web_ctx_p ctx){
	//remove server from event loop
	ax_web_event_pop(ctx->event_ctx,ctx->socket_fd,ax_web_event_type_read);
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
	ax_web_event_close(ctx->event_ctx);
	//
	ax_web_mem_free(ctx,sizeof(*ctx));
	return 0;
}

