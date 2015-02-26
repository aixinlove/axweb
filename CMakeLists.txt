PROJECT(axweb)
ADD_SUBDIRECTORY(axweb output)
ADD_SUBDIRECTORY(axwebl output)
ADD_SUBDIRECTORY(thirdpart output)

ADD_EXECUTABLE(axwebc axwebc.c)
ADD_EXECUTABLE(axwebl axwebl.c)
TARGET_LINK_LIBRARIES(axwebc axweb_static)
TARGET_LINK_LIBRARIES(axwebl lua_static axweb_static axwebl_static)
