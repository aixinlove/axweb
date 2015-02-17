#include "ax_web_request.h"
#include "ax_web_log.h"
#include "ax_web_mem.h"
/*
 * helpers for request
 */
ax_web_request_p ax_web_request_new(){
	ax_web_request_p r=(ax_web_request_p)ax_web_mem_alloc(sizeof(*r));
	return r;
}
int ax_web_request_close(ax_web_request_p r){
	ax_web_mem_free(r,sizeof(*r));
	return 0;
}

/*
 * a very simple request handler.
 */
int ax_web_default_req_handler(ax_web_ctx_p ctx,ax_web_request_p req){	
	ax_web_log_a(ctx,"request","%s %s",req->method,req->path);
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
