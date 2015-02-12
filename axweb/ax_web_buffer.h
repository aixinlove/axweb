
/*
 * buffer object
 */
#ifndef __ax_web_buffer__
#define __ax_web_buffer__
struct ax_web_buffer_t{
	char* data;
	int len;
	struct ax_web_buffer_t* next;
};
typedef struct ax_web_buffer_t* ax_web_buffer_p;

ax_web_buffer_p ax_web_buffer_new(char *data,int len);
ax_web_buffer_p ax_web_buffer_append(ax_web_buffer_p buff,char *data,int len);
ax_web_buffer_p ax_web_buffer_free(ax_web_buffer_p buff);
#endif //(__ax_web_buffer__)
