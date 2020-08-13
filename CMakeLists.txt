cmake_minimum_required(VERSION 3.15)
project(NginD)

set(CMAKE_CXX_STANDARD 17)

include_directories(./kernel/utils)
include_directories(./kernel/basic)

add_executable(NginD main.cc kernel/utils/class_info.cc kernel/utils/class_info.h kernel/basic/object.cc kernel/basic/object.h kernel/utils/serialization.h test/kernel/utils/serialization_test.cc)

set(PLATFORM_PREFIX "/lib/linux")

target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGLU.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libglfw.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGL.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libX11.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXrand.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXinerama.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXxf86vm.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXcursor.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libpthread.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libdl.so")

