cmake_minimum_required(VERSION 2.8.12)
project (Lagscope C)
file(GLOB CSources *.c)
add_executable(lagscope ${CSources})
if(WIN32)
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
	target_compile_options(lagscope PUBLIC /MT)
	target_link_options(lagscope PUBLIC /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()
if(UNIX)
	set(CMAKE_C_FLAGS "-Wall -W -O2 -fno-strict-aliasing")
	target_link_libraries(lagscope pthread rt)
endif()
install(TARGETS lagscope DESTINATION bin)
