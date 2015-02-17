#ifndef __ax_web_log__
#define __ax_web_log__
#include "ax_web_types.h"

/*
 * log functions
 */
int ax_web_log0(ax_web_ctx_p ctx,enum ax_web_log_level level,char *category,char *filename,int line,char *fmt,...);
#define ax_web_log1(ctx,level,category,fmt,...) do{ax_web_log0(ctx,level,category,__FILE__,__LINE__,fmt,##__VA_ARGS__);}while(0)
#define ax_web_log_i(ctx,fmt,...) do{ax_web_log0(ctx,ax_web_log_level_info,"axweb",__FILE__,__LINE__,fmt,##__VA_ARGS__);}while(0)
#define ax_web_log_d(ctx,fmt,...) do{ax_web_log0(ctx,ax_web_log_level_debug,"axweb",__FILE__,__LINE__,fmt,##__VA_ARGS__);}while(0)
#define ax_web_log_e(ctx,fmt,...) do{ax_web_log0(ctx,ax_web_log_level_error,"axweb",__FILE__,__LINE__,fmt,##__VA_ARGS__);}while(0)
#define ax_web_log_a(ctx,fmt,...) do{ax_web_log0(ctx,ax_web_log_level_always,"axweb",__FILE__,__LINE__,fmt,##__VA_ARGS__);}while(0)
int ax_web_set_log_handler(ax_web_ctx_p ctx,ax_web_log_handler_t handler);
int ax_web_default_log_handler(ax_web_ctx_p ctx,enum ax_web_log_level level,char *category,char *filename,int line,char *msg);
ax_web_log_handler_t ax_web_get_log_handler(ax_web_ctx_p ctx);
#endif //__ax_web_log__
