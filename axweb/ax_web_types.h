#include "ax_web_buffer.h"
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
};

/*
 * request env
 */
struct ax_web_request_t{
	int socket_fd;			//raw socket fd for http request
	char *query;			//http query string,need to free after used.
	char *header;			//http header as string,need to free after used.
	char *path;				//http request path,need to free after used.
	char *method;			//http method,need to free after used.
	char *version;			//http protocol version,need to free after used.
	char remote_ip[32]; 	//client ip
	ax_web_buffer_p out_buff;	//buffer data to send to client,need free after send out.
	ax_web_buffer_p in_buff;	//buffer data that read from client,need to free after processed.
};

enum ax_web_log_level{
	ax_web_log_level_info,
	ax_web_log_level_debug,
	ax_web_log_level_error
};
//alias types
typedef struct ax_web_ctx_t* ax_web_ctx_p;
typedef struct ax_web_request_t* ax_web_request_p;
//call back types
typedef int (*ax_web_req_handler_t)(ax_web_ctx_p ctx,ax_web_request_p req);
typedef int (*ax_web_log_handler_t)(ax_web_ctx_p ctx,enum ax_web_log_level level,char *category,char *filename,int line,char *msg);

