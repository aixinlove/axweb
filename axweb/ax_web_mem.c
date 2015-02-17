#include "ax_web_mem.h"
#include <stdlib.h>
#include <string.h>
static int __ax_web_mem_used__=0;
void* ax_web_mem_alloc(int size){
	__ax_web_mem_used__+=size;
	void *m=malloc(size);
	memset(m,0x0,size);
	return m;
}
void* ax_web_mem_realloc(void* p,int oldsize,int size){
	__ax_web_mem_used__+=(size-oldsize);
	return realloc(p,size);
}
void ax_web_mem_free(void *p,int size){
	__ax_web_mem_used__-=(size);
	free(p);
}

int ax_web_mem_used(){
	return __ax_web_mem_used__;
}
