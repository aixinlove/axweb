#include <stdio.h>
#include "axweb/ax_web.h"

int main(){
	int axret=0;
	struct ax_web_ctx_t ctx;
	ax_web_init(&ctx);
	if((axret=ax_web_start(&ctx,"127.0.0.1",8888))!=0){
		if(axret==-1){
ax_web_log_e(&ctx,"%s","create server socket error");
		}
		return -1;
	}		
	ax_web_close(&ctx);
	return 0;
}
