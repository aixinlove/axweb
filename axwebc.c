#include <stdio.h>
#include "axweb/ax_web.h"
FILE *logfile;
void on_idle(ax_web_ctx_p ctx){
	ax_web_log_i(ctx,"hello idel event");

}
int on_log(ax_web_ctx_p ctx,enum ax_web_log_level level,char *category,char *filename,int line,char *msg){
	fprintf(logfile,"%s %s[%d] %s\n",ax_web_log_level_str[level],filename,line,msg);
	fflush(logfile);
	return 0;
}
int on_request(ax_web_ctx_p ctx,ax_web_request_p req){	
	ax_web_log_i(ctx,"request","%s %s",req->method,req->path);
	return 0;
}

int main(){
	//open logfile
	logfile=fopen("ax.log","ab");
	if(logfile==NULL){
		fprintf(stderr,"can not open logfile.\n");
		return -1;
	}
	int axret=0;
	ax_web_ctx_p ctx=ax_web_new();
	//ctx->idle_handler=on_idle;
	ctx->log_handler=on_log;
	ctx->req_handler=on_request;
	if((axret=ax_web_start(ctx,"127.0.0.1",8888,"."))!=0){
ax_web_log_e(ctx,"fail to start server");
		return -2;
	}		
	ax_web_close(ctx);
	fclose(logfile);
	return 0;
}
