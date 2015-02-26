#include "ax_web_event.h"
#include "ax_web_mem.h"
#include <unistd.h>
#include <sys/epoll.h>
ax_web_event_ctx_p ax_web_event_new(void* ud){
	ax_web_event_ctx_p ep=(ax_web_event_ctx_p)ax_web_mem_alloc(sizeof(*ep));
	ep->fd=epoll_create(1);
	if(ep->fd==-1){
		return NULL;
	}
	ep->ud=ud;
	return ep;
}
int ax_web_event_push(ax_web_event_ctx_p ctx,int fd,enum ax_web_event_type type,void* ud){
	struct epoll_event ev;
	if(ax_web_event_type_read==type){
		ev.events=EPOLLIN;
	}else if(ax_web_event_type_write==type){
		ev.events=EPOLLOUT;
	}
	ev.data.fd=fd;
	if(epoll_ctl(ctx->fd,EPOLL_CTL_ADD,fd,&ev)==-1){
		return -1;
	}
	return 0;
}
int ax_web_event_pop(ax_web_event_ctx_p ctx,int fd,enum ax_web_event_type type){
	return 0;
}
int ax_web_event_wait(ax_web_event_ctx_p ctx,ax_web_event_p event,int max_event,int timeout){
	struct epoll_event evs[max_event];
	int nfds=epoll_wait(ctx->fd,evs,max_event,timeout);

	return nfds;
}
int ax_web_event_close(ax_web_event_ctx_p ctx){
	ax_web_mem_free(ctx,sizeof(*ctx));
	return 0;
}
