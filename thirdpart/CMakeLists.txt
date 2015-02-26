SET(LUA_ROOT lua5_3)
SET(LUA_SRC 
		${LUA_ROOT}/src/lapi.c
		${LUA_ROOT}/src/lauxlib.c
		${LUA_ROOT}/src/lbaselib.c
		${LUA_ROOT}/src/lbitlib.c
		${LUA_ROOT}/src/lcode.c
		${LUA_ROOT}/src/lcorolib.c
		${LUA_ROOT}/src/lctype.c
		${LUA_ROOT}/src/ldblib.c
		${LUA_ROOT}/src/ldebug.c
		${LUA_ROOT}/src/ldo.c
		${LUA_ROOT}/src/ldump.c
		${LUA_ROOT}/src/lfunc.c
		${LUA_ROOT}/src/lgc.c
		${LUA_ROOT}/src/linit.c
		${LUA_ROOT}/src/liolib.c
		${LUA_ROOT}/src/llex.c
		${LUA_ROOT}/src/lmathlib.c
		${LUA_ROOT}/src/lmem.c
		${LUA_ROOT}/src/loadlib.c
		${LUA_ROOT}/src/lobject.c
		${LUA_ROOT}/src/lopcodes.c
		${LUA_ROOT}/src/loslib.c
		${LUA_ROOT}/src/lparser.c
		${LUA_ROOT}/src/lstate.c
		${LUA_ROOT}/src/lstring.c
		${LUA_ROOT}/src/lstrlib.c
		${LUA_ROOT}/src/ltable.c
		${LUA_ROOT}/src/ltablib.c
		${LUA_ROOT}/src/ltm.c
		${LUA_ROOT}/src/lundump.c
		${LUA_ROOT}/src/lutf8lib.c
		${LUA_ROOT}/src/lvm.c
		${LUA_ROOT}/src/lzio.c
)
ADD_LIBRARY(lua_static STATIC ${LUA_SRC})
SET_TARGET_PROPERTIES(lua_static PROPERTIES OUTPUT_NAME "lua")
