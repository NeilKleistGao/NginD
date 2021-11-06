cmake_minimum_required(VERSION 3.15)
project(NginD)

set(CMAKE_CXX_STANDARD 17)

if (0)
    set(OUT_PATH build)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
else()
    set(OUT_PATH bin)
endif()

option(PLATFORM_LINUX "target platform: linux" ON)
option(PLATFORM_WINDOWS "target platform: windows" OFF)

include(kernel/CMakeLists.txt)
include(extern/CMakeLists.txt)
include(plugin/CMakeLists.txt)

include_directories(.)
include_directories(kernel)
include_directories(include)
include_directories(include/opengl)
include_directories(resources)
include_directories(include/freetype2)

if (PLATFORM_LINUX)
    add_definitions(-D PLATFORM_LINUX)
    include_directories(/usr/local/include/freetype2)
elseif (PLATFORM_WINDOWS)
    add_definitions(-D PLATFORM_WINDOWS)
    include_directories(include/freetype2)
endif()

if (PLATFORM_LINUX)
    set(PLATFORM_PREFIX "/lib/linux")
elseif (PLATFORM_WINDOWS)
    set(PLATFORM_PREFIX "/lib/windows")
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/${OUT_PATH}")

add_executable(NginD main.cc
        ${KERNEL_HEADER}
        ${KERNEL_SRC}
        ${EXTERN_HEADER}
        ${EXTERN_SRC}
        ${PLUGIN_HEADER}
        ${PLUGIN_SRC})

if (PLATFORM_LINUX)
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGLEW.so.2.1")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGLEW.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libglfw.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libglfw3.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libglfw.so.3")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libGL.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libX11.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXrand.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXi.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/libXi.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/soil2/libsoil2.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/soloud/libSDL2.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/soloud/libSDL2main.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/soloud/libsoloud_static_x64.a" "libasound.so" -ldl -lpthread)
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/lua/liblua52.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/freetype/libfreetype.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/freetype/libfreetype.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/snappy/libsnappy.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/box2d/libbox2d.a")
elseif (PLATFORM_WINDOWS)
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/glew32.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/glew32s.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/glfw3.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/glfw3_mt.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/opengl/glfw3dll.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/soloud/soloud_static_x64.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/freetype/freetype.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/soil2/soil2.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/box2d/box2d.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/snappy/snappy.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/lua/lua52.lib")
    target_link_libraries(NginD "opengl32.lib")
endif()

if (PLATFORM_LINUX)
    add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory "${CMAKE_SOURCE_DIR}/resources" "${EXECUTABLE_OUTPUT_PATH}/resources"
        COMMENT "COPY RESOURCES FILES")

    add_compile_options(-ldl)
    add_compile_options(-pthread)
elseif (PLATFORM_WINDOWS)
    add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory "../resources" "${EXECUTABLE_OUTPUT_PATH}/Debug/resources"
        COMMENT "COPY RESOURCES FILES")

    add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory "../resources" "../win32/resources"
        COMMENT "COPY RESOURCES FILES")
    file(COPY "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/freetype/freetype.dll" DESTINATION "${EXECUTABLE_OUTPUT_PATH}/Debug")
    file(COPY "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/lua/lua52.dll" DESTINATION "${EXECUTABLE_OUTPUT_PATH}/Debug")
    file(COPY "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/glfw3.dll" DESTINATION "${EXECUTABLE_OUTPUT_PATH}/Debug")
    file(COPY "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/glew32.dll" DESTINATION "${EXECUTABLE_OUTPUT_PATH}/Debug")
endif()

add_compile_options(-finput-charset=GBK -fexec-charset=UTF-8)

add_executable(crypto kernel/crypto/main.cc
        kernel/crypto/aes.h kernel/crypto/aes.cc
        kernel/math/galois_field.h kernel/math/galois_field.cc)

add_executable(compress kernel/compress/main.cc)

if (PLATFORM_LINUX)
    target_link_libraries(compress "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/snappy/libsnappy.a")
elseif (PLATFORM_WINDOWS)
    target_link_libraries(compress "${CMAKE_SOURCE_DIR}${PLATFORM_PREFIX}/snappy/snappy.lib")
endif()