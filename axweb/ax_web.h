/*
 * @author pengyunchou
 * @createtime 2015/2/15
 * @copyright tianjiang
 * @a very simple http server in c
 */

#ifndef __ax_web___
#define __ax_web___
#include "ax_web_types.h"
#include "ax_web_buffer.h"
int ax_web_init(ax_web_ctx_p ctx);
int ax_web_start(ax_web_ctx_p ctx,char* addr,int port);
int ax_web_close(ax_web_ctx_p ctx);
/*
 * calbacks & handlers
 */
int ax_web_set_req_handler(ax_web_ctx_p ctx,ax_web_req_handler_t handler); 
ax_web_req_handler_t ax_web_get_req_handler(ax_web_ctx_p ctx);
int ax_web_set_log_handler(ax_web_ctx_p ctx,ax_web_log_handler_t handler);
ax_web_log_handler_t ax_web_get_log_handler(ax_web_ctx_p ctx);
/*
 * response functions
 */
int ax_web_write(ax_web_ctx_p ctx,ax_web_request_p req,char *data,int len);

/*
 * log functions
 */
int ax_web_log0(ax_web_ctx_p ctx,enum ax_web_log_level level,char *category,char *filename,int line,char *fmt,...);
#define ax_web_log1(ctx,level,category,fmt,...) do{ax_web_log0(ctx,level,category,__FILE__,__LINE__,fmt,##__VA_ARGS__);}while(0)
#define ax_web_log_i(ctx,fmt,...) do{ax_web_log0(ctx,ax_web_log_level_info,"axweb",__FILE__,__LINE__,fmt,##__VA_ARGS__);}while(0)
#define ax_web_log_d(ctx,fmt,...) do{ax_web_log0(ctx,ax_web_log_level_debug,"axweb",__FILE__,__LINE__,fmt,##__VA_ARGS__);}while(0)
#define ax_web_log_e(ctx,fmt,...) do{ax_web_log0(ctx,ax_web_log_level_error,"axweb",__FILE__,__LINE__,fmt,##__VA_ARGS__);}while(0)

#endif //(__ax_web___)
