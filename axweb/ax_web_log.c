#include "ax_web_log.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
/*
 * log helper functions
 */
int ax_web_log0(ax_web_ctx_p ctx,enum ax_web_log_level level,char *category,char *filename,int line,char *fmt,...){
	va_list arg_ptr;
	va_start(arg_ptr,fmt);
	char msg[2*1024];
	vsprintf(msg,fmt,arg_ptr);
	va_end(arg_ptr);	
	ax_web_log_handler_t handler=ax_web_get_log_handler(ctx);
	handler(ctx,level,category,filename,line,msg);
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
