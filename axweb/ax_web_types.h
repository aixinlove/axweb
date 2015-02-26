#ifndef __ax_web_types__
#define __ax_web_types__
#include "ax_web_buffer.h"
#include "ax_web_event.h"
#include <stdlib.h>
#include <stdint.h>
/*
 * client socket connection
 */
struct ax_web_connection{
	int socket_fd;
	char ipaddr[64];
	int32_t connect_time;
};
/*
 * request env
 */
struct ax_web_request_t{
	struct ax_web_connection connection;
	char *query;			//http query string,need to free after used.
	char *header;			//http header as string,need to free after used.
	char *path;				//http request path,need to free after used.
	char *method;			//http method,need to free after used.
	char *version;			//http protocol version,need to free after used.
	ax_web_buffer_p in_buff;
	ax_web_buffer_p out_buff;
};
/*
 * server context
 */
struct ax_web_ctx_t{
	int socket_fd;			//raw server socket
	int runing;
	char listen_addr[32];
	int listen_port;
	void* req_handler;		//request handler
	void* log_handler;		//log hanbdler
	void* idle_handler;  	//idle callback
	char document_path[128];
	ax_web_event_ctx_p event_ctx;

};

enum ax_web_log_level{
	ax_web_log_level_info,
	ax_web_log_level_debug,
	ax_web_log_level_error,
	ax_web_log_level_always
};
static char *ax_web_log_level_str[]={
	"INFO",
	"DEBUG",
	"ERROR",
	"ALWAYS"
};
//alias types
typedef struct ax_web_ctx_t* ax_web_ctx_p;
typedef struct ax_web_request_t* ax_web_request_p;
//call back types
typedef int (*ax_web_req_handler_t)(ax_web_ctx_p ctx,ax_web_request_p req);
typedef int (*ax_web_log_handler_t)(ax_web_ctx_p ctx,enum ax_web_log_level level,char *category,char *filename,int line,char *msg);
typedef void (*ax_web_idle_handler_t)(ax_web_ctx_p ctx);

#endif //__ax_web_types__
