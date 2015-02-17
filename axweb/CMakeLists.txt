cmake_minimum_required(VERSION 2.8)
SET(SRC_LIST
	ax_web_mem.c
	ax_web_os_linux.c
	ax_web_scheduler.c
	ax_web_zip.c
	ax_web_encript.c
	ax_web_socket_unix.c
	ax_web_event_linux.c
	ax_web_buffer.c
	ax_web.c
	ax_web_mime.c
	ax_web_log.c
	ax_web_request.c
	ax_web_response.c
)
ADD_LIBRARY(axweb_static STATIC ${SRC_LIST})
SET_TARGET_PROPERTIES(axweb_static PROPERTIES OUTPUT_NAME "axweb")
