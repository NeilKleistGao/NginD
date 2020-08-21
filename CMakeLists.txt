cmake_minimum_required(VERSION 3.15)
project(NginD)

set(CMAKE_CXX_STANDARD 17)

execute_process(COMMAND /bin/bash ./inject.sh
        ERROR_QUIET
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/exec)

include_directories(.)
include_directories(./kernel/utils)
include_directories(./kernel/basic)
include_directories(./include/opengl)
include_directories(./include/libpng)
include_directories(./settings)
include_directories(./resources)

add_executable(NginD main.cc
        kernel/utils/class_info.cc
        kernel/utils/class_info.h
        kernel/basic/object.cc
        kernel/basic/object.h
        kernel/utils/serialization.h
        test/kernel/utils/serialization_test.cc
        test/kernel/utils/class_info_test.cc
        kernel/basic/render/render.h
        kernel/basic/render/render.cc
        settings/display_settings.h
        kernel/basic/render/window.h
        kernel/basic/render/window.cc
        kernel/basic/game.h
        kernel/basic/game.cc
        kernel/basic/input/keyboard_input.h
        kernel/basic/input/input.h
        kernel/basic/input/keyboard_input.cc
        kernel/basic/input/input.cc
        test/kernel/basic/input/keyboard_input_test.cc kernel/basic/render/png_image.h kernel/basic/render/png_image.cc
        include/opengl/glad.c settings/resources_settings.h kernel/utils/file_utils.h kernel/utils/file_utils.cc kernel/utils/ini_config.h kernel/utils/ini_config.cc kernel/utils/convert_utils.h test/kernel/basic/render/window_test.cc test/kernel/utils/ini_config_test.cc)

set(PLATFORM_PREFIX "/lib/linux")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGLU.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGLU.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libglfw.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libglfw3.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGL.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libX11.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXrand.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXinerama.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXxf86vm.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXcursor.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libpthread.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libpthread.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libdl.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libdl.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/libpng/libpng16.so")

add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory "${PROJECT_SOURCE_DIR}/resources" "${EXECUTABLE_OUTPUT_PATH}/resources"
        COMMENT "COPY RESOURCES FILES")