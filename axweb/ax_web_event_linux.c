#include "ax_web_event.h"
#include "ax_web_mem.h"
#include <unistd.h>
ax_web_event_ctx_p ax_web_event_new(){
	ax_web_event_ctx_p ep=(ax_web_event_ctx_p)ax_web_mem_alloc(sizeof(*ep));
	return ep;
}
int ax_web_event_push(ax_web_event_ctx_p ctx,int fd,enum ax_web_event_type type,void* ud){

	return 0;
}
int ax_web_event_pop(ax_web_event_ctx_p ctx,int fd,enum ax_web_event_type type){
	return 0;
}
int ax_web_event_wait(ax_web_event_ctx_p ctx,ax_web_event_p event,int max_event,int timeout){
	sleep(10);
	return 0;
}
int ax_web_event_close(ax_web_event_ctx_p ctx){
	ax_web_mem_free(ctx,sizeof(*ctx));
	return 0;
}
