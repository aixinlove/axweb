cmake_minimum_required(VERSION 2.8)
SET(SRC_LIST
	ax_web_socket.c
	ax_web_event.c
	ax_web_buffer.c
	ax_web.c
	l_ax_web.c
		)
ADD_LIBRARY(axweb_static STATIC ${SRC_LIST})
SET_TARGET_PROPERTIES(axweb_static PROPERTIES OUTPUT_NAME "axweb")
