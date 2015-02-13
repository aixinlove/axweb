#include <stdio.h>
#include "axweb/ax_web.h"

int main(){
	int axret=0;
	ax_web_ctx_p ctx=ax_web_new();
	if((axret=ax_web_start(ctx,"127.0.0.1",8888))!=0){
ax_web_log_e(ctx,"fail to start server");
		return -1;
	}		
	ax_web_close(ctx);
	return 0;
}
