cmake_minimum_required(VERSION 3.15)
project(NginD)

set(CMAKE_CXX_STANDARD 17)

add_executable(NginD main.cc)

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