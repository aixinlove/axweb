#include "ax_web_buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
ax_web_buffer_p ax_web_buffer_new(char *data,int len){
	ax_web_buffer_p buff=(ax_web_buffer_p)alloc(sizeof(*buff));
	assert(data!=NULL,"data to construct buffer can not be null");
	buff->next=NULL;
	buff->data=(char *)alloc(len);
	memcpy(buff->data,data,len);
	buff->len=len;	
	return buff;
}
ax_web_buffer_p ax_web_buffer_append(ax_web_buffer_p buff,char *data,int len){
	assert(buff!=NULL,"buffer can not be null.");
	buff->data=(char *)realloc(buff->data,buff->len+len);
	memcpy(buff->data+buff->len,data,len);
	buff->len=buff->len+len;
	return buff;
}

ax_web_buffer_p ax_web_buffer_free(ax_web_buffer_p buff){
	assert(buff!=NULL,"buffer to free can not be null.");
	ax_web_buffer_p next=buff->next;
	free(buff->data);
	free(buff);
	buff=NULL;
	return next;
}
