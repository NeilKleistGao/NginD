cmake_minimum_required(VERSION 3.15)
project(NginD)

set(CMAKE_CXX_STANDARD 17)

execute_process(COMMAND /bin/bash ./inject.sh
        ERROR_QUIET
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/exec
        )

include_directories(.)
include_directories(./kernel/utils)
include_directories(./kernel/basic)
include_directories(./include/opengl)
include_directories(./settings)

add_executable(NginD main.cc kernel/utils/class_info.cc kernel/utils/class_info.h kernel/basic/object.cc kernel/basic/object.h kernel/utils/serialization.h test/kernel/utils/serialization_test.cc test/kernel/utils/class_info_test.cc kernel/basic/render/render.h kernel/basic/render/render.cc settings/display_settings.h kernel/basic/render/window.h kernel/basic/render/window.cc kernel/audio/audio.h kernel/audio/audio.cc kernel/controller/controller.h kernel/controller/controller.cc kernel/model/model.h kernel/model/model.cc kernel/view/view.h kernel/view/view.cc kernel/basic/game.h kernel/basic/game.cc test/kernel/basic/render/render_window_test.cc)

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

