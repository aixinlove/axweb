/*
 * @author pengyunchou
 * @createtime 2015/2/15
 * @copyright tianjiang
 * @a very simple http server in c
 */

#ifndef __ax_web___
#define __ax_web___
#include "ax_web_types.h"
#include "ax_web_log.h"
ax_web_ctx_p ax_web_new();
int ax_web_start(ax_web_ctx_p ctx,char* addr,int port,char *document_path);
int ax_web_stop(ax_web_ctx_p ctx);
int ax_web_close(ax_web_ctx_p ctx);
#endif //(__ax_web___)
