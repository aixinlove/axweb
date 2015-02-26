#include <stdint.h>
/*
 * data types
 */
enum ax_web_event_type{
	ax_web_event_type_read,
	ax_web_event_type_write	
};

struct ax_web_event_t{
	int fd;
	enum ax_web_event_type type;
	void *ud;
};
struct ax_web_event_ctx_t{
	int fd;
	void *ud;
};
typedef struct ax_web_event_ctx_t* ax_web_event_ctx_p;
typedef struct ax_web_event_t* ax_web_event_p;
/*
 * public functions
 */
ax_web_event_ctx_p ax_web_event_new(void* ud);
int ax_web_event_push(ax_web_event_ctx_p ctx,int fd,enum ax_web_event_type type,void* ud);
int ax_web_event_pop(ax_web_event_ctx_p ctx,int fd,enum ax_web_event_type type);
int ax_web_event_wait(ax_web_event_ctx_p ctx,ax_web_event_p event,int max_event,int timeout);
int ax_web_event_close(ax_web_event_ctx_p ctx);
