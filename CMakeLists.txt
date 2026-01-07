cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_FLAGS "-O2 -s")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "build/lib/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build/bin/")

#-----------------

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

#-----------------

project(Coverett_apps C)

add_executable(redstone apps/redstone.c)
target_link_libraries(redstone coverett)

add_executable(fimexu apps/fimexu.c)
target_link_libraries(fimexu coverett)

add_executable(seplay apps/seplay.c)
target_link_libraries(seplay coverett)

add_executable(ldevmet apps/ldevmet.c)
target_link_libraries(ldevmet coverett)

add_executable(lshldev apps/lshldev.c)
target_link_libraries(lshldev coverett)

#-----------------
