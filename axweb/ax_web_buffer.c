#include "ax_web_buffer.h"
#include "ax_web_mem.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
ax_web_buffer_p ax_web_buffer_new(char *data,int len){
	assert(data!=NULL);
	ax_web_buffer_p buff=(ax_web_buffer_p)ax_web_mem_alloc(sizeof(*buff));
	buff->next=NULL;
	buff->data=(char *)ax_web_mem_alloc(len);
	memcpy(buff->data,data,len);
	buff->len=len;	
	return buff;
}
ax_web_buffer_p ax_web_buffer_append(ax_web_buffer_p buff,char *data,int len){
	assert(buff!=NULL);
	buff->data=(char *)ax_web_mem_realloc(buff->data,buff->len,buff->len+len);
	memcpy(buff->data+buff->len,data,len);
	buff->len=buff->len+len;
	return buff;
}

ax_web_buffer_p ax_web_buffer_free(ax_web_buffer_p buff){
	assert(buff!=NULL);
	ax_web_buffer_p next=buff->next;
	ax_web_mem_free(buff->data,buff->len);
	ax_web_mem_free(buff,sizeof(*buff));
	buff=NULL;
	return next;
}
