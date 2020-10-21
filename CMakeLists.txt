cmake_minimum_required(VERSION 3.15)
project(NginD)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-D PLATFORM_LINUX)

include_directories(.)
include_directories(kernel)
include_directories(./include)
include_directories(./include/opengl)
include_directories(./include/libpng)
include_directories(./resources)

include_directories(/usr/local/include/freetype2)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_BOOST_CMAKE ON)

find_package(Boost COMPONENTS fiber REQUIRED)

add_executable(NginD main.cc
        kernel/objects/object.cc
        kernel/objects/object.h
        kernel/utils/serialization.h
        test/kernel/utils/serialization_test.cc
        kernel/render/render.h
        kernel/render/render.cc
        kernel/render/window.h
        kernel/render/window.cc
        kernel/game.h
        kernel/game.cc
        kernel/input/keyboard_input.h
        kernel/input/input.h
        kernel/input/keyboard_input.cc
        kernel/input/input.cc
        test/kernel/input/keyboard_input_test.cc
        kernel/render/png_image.h
        kernel/render/png_image.cc
        include/opengl/glad.c
        kernel/utils/convert_utils.h
        test/kernel/render/window_test.cc
        kernel/math/vector.h
        kernel/math/random.h
        kernel/math/vector.cc
        kernel/math/random.cc
        kernel/coroutine/coroutine.h
        kernel/memory/auto_collection_object.h
        kernel/memory/auto_collection_object.cc
        kernel/memory/memory_pool.h
        kernel/memory/memory_pool.cc
        kernel/log/logger.h
        kernel/log/logger.cc
        kernel/log/logger_factory.h
        kernel/log/logger_factory.cc
        kernel/log/log_level.h
        kernel/filesystem/file.h
        kernel/filesystem/file.cc
        kernel/filesystem/file.cc
        kernel/resources/resources_manager.h
        kernel/resources/resources_manager.cc
        kernel/resources/resource.h
        kernel/filesystem/output_stream.h
        kernel/filesystem/output_stream.cc
        kernel/resources/image_resource.h
        kernel/resources/config_resource.h
        kernel/resources/image_resource.cc
        kernel/resources/config_resource.cc
        kernel/timer/timer.h
        kernel/timer/timer.cc
        kernel/platforms/linux.h
        kernel/platforms/platforms.h
        kernel/platforms/windows.h
        kernel/objects/world.h
        kernel/objects/world.cc
        kernel/render/true_type_font.h
        kernel/render/true_type_font.cpp
        kernel/resources/font_resource.h
        kernel/resources/font_resource.cc
        kernel/render/font_factory.h
        kernel/render/font_factory.cc kernel/render/render_queue.h kernel/render/render_queue.cc kernel/render/render_command.h kernel/render/render_command.cc kernel/components/component.h kernel/components/component.cc kernel/objects/updatable_object.h kernel/input/mouse_input.h kernel/input/mouse_input.cc kernel/input/text_input.h kernel/input/text_input.cc)

set(PLATFORM_PREFIX "/lib/linux")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGLU.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGLU.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libglfw.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libglfw3.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libglfw.so.3")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGL.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libX11.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXrand.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXinerama.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXxf86vm.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXcursor.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libdl.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libdl.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/rttr/librttr_core.so")
target_link_libraries (NginD ${Boost_LIBRARIES})
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/libpng/libpng16.so.16")

target_link_libraries(NginD "/usr/local/lib/libfreetype.so")
target_link_libraries(NginD "/usr/local/lib/libfreetype.a")

add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory "${PROJECT_SOURCE_DIR}/resources" "${EXECUTABLE_OUTPUT_PATH}/resources"
        COMMENT "COPY RESOURCES FILES")

add_compile_options(-pthread)
add_compile_options(-lboost_fiber)
add_compile_options(-lboost_context)
#add_compile_options(-lfreetype)
add_compile_options(-finput-charset=GBK -fexec-charset=UTF-8)