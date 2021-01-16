cmake_minimum_required(VERSION 3.15)
project(NginD)

set(CMAKE_CXX_STANDARD 17)

include(kernel/CMakeLists.txt)
include(extern/CMakeLists.txt)
include(plugin/CMakeLists.txt)

add_definitions(-D PLATFORM_LINUX)
add_definitions(-D RENDER_BACKEND_OPENGL)
add_definitions(-D MODE_DEBUG)

include_directories(.)
include_directories(kernel)
include_directories(include)
include_directories(include/opengl)
include_directories(resources)
include_directories(/usr/local/include/freetype2)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_BOOST_CMAKE ON)

set(PLATFORM_PREFIX "/lib/linux")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

find_package(Boost COMPONENTS fiber REQUIRED)

add_executable(NginD main.cc
        ${KERNEL_HEADER}
        ${KERNEL_SRC}
        ${EXTERN_HEADER}
        ${EXTERN_SRC}
        ${PLUGIN_HEADER}
        ${PLUGIN_SRC})

target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libGLEW.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libglfw.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libglfw3.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libglfw.so.3")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGL.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libX11.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXrand.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libXi.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libXi.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soil2/libsoil2.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soloud/libsoloud.a")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soil2/libsoil2.so")
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/lua/liblua52.so")
target_link_libraries(NginD "/usr/local/lib/libfreetype.so")
target_link_libraries(NginD "/usr/local/lib/libfreetype.a")
target_link_libraries (NginD ${Boost_LIBRARIES})

add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory "../resources" "${EXECUTABLE_OUTPUT_PATH}/resources"
        COMMENT "COPY RESOURCES FILES")

add_compile_options(-pthread)
add_compile_options(-lboost_fiber)
add_compile_options(-lboost_context)
add_compile_options(-finput-charset=GBK -fexec-charset=UTF-8)