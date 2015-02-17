#ifndef __ax_web_request__
#define __ax_web_request__
#include "ax_web_types.h"

ax_web_request_p ax_web_request_new();
int ax_web_request_close(ax_web_request_p r);
/*
 * request calbacks & handlers
 */
int ax_web_set_req_handler(ax_web_ctx_p ctx,ax_web_req_handler_t handler); 
int ax_web_set_log_handler(ax_web_ctx_p ctx,ax_web_log_handler_t handler);
int ax_web_set_req_handler(ax_web_ctx_p ctx,ax_web_req_handler_t handler);
ax_web_req_handler_t ax_web_get_req_handler(ax_web_ctx_p ctx);
#endif

