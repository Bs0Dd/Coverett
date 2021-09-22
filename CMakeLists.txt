cmake_minimum_required(VERSION 3.5)

set (CMAKE_C_FLAGS "-O2 -s")

project(Coverett C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB DEVICES_SRC
	"devices/*.h"
	"devices/*.c"
)

add_library(coverett SHARED
	cJSON/cJSON.h
	cJSON/cJSON.c
	coverett.h
	coverett.c
	coverett-private.h
	coverett-private.c
	${DEVICES_SRC}
	)



project(Coverett_apps C)

add_executable(redstone redstone.c)

add_executable(fimexu fimexu.c)

add_executable(seplay seplay.c)

add_executable(lshldev lshldev.c)

target_link_libraries(redstone coverett)

target_link_libraries(fimexu coverett)

target_link_libraries(seplay coverett)

target_link_libraries(lshldev coverett)

