#include "ax_web_mem.h"
#include <stdlib.h>

static int __ax_web_mem_total_used__;
void* ax_web_mem_alloc(int size){
	__ax_web_mem_total_used__+=size;
	return malloc(size);
}
void* ax_web_mem_realloc(void* p,int oldsize,int size){
	__ax_web_mem_total_used__+=(size-oldsize);
	return realloc(p,size);
}
void ax_web_mem_free(void *p,int size){
	__ax_web_mem_total_used__-=(size);
	free(p);
}

int ax_web_mem_used(){
	return __ax_web_mem_total_used__;
}
