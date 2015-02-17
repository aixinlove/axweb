#ifndef __ax_web_mem__
#define __ax_web_mem__
void* ax_web_mem_alloc(int size);
void* ax_web_mem_realloc(void* p,int oldsize,int size);
void ax_web_mem_free(void *p,int size);
int ax_web_mem_used();
#endif //(__ax_web_mem__)
