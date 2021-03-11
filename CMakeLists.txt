cmake_minimum_required(VERSION 3.15)
project(NginD)

set(CMAKE_CXX_STANDARD 17)

option(target_linux "target platform: linux" OFF)
option(target_windows "target platform: windows" ON)

include(kernel/CMakeLists.txt)
include(extern/CMakeLists.txt)
include(plugin/CMakeLists.txt)

if (target_linux)
    add_definitions(-D PLATFORM_LINUX)
elseif (target_windows)
    add_definitions(-D PLATFORM_WINDOWS)
endif()

add_definitions(-D MODE_DEBUG)

include_directories(.)
include_directories(kernel)
include_directories(include)
include_directories(include/opengl)
include_directories(resources)

if (target_linux)
    include_directories(/usr/local/include/freetype2)
elseif (target_windows)
    include_directories(include/freetype2)
endif()


#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_NO_BOOST_CMAKE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

if (target_linux)
    set(PLATFORM_PREFIX "/lib/linux")
elseif (target_windows)
    set(PLATFORM_PREFIX "/lib/windows")
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

#find_package(Boost COMPONENTS fiber REQUIRED)

add_executable(NginD main.cc
        ${KERNEL_HEADER}
        ${KERNEL_SRC}
        ${EXTERN_HEADER}
        ${EXTERN_SRC}
        ${PLUGIN_HEADER}
        ${PLUGIN_SRC})

if (target_linux)
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libGLEW.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libglfw.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libglfw3.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libglfw.so.3")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libGL.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libX11.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libXrand.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libXi.so")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/libXi.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soil2/libsoil2.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soloud/libSDL2.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soloud/libSDL2main.a")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soloud/libsoloud_static_x64.a" -lasound -ldl -lpthread)
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/lua/liblua52.so")
    target_link_libraries(NginD "/usr/local/lib/libfreetype.so")
    target_link_libraries(NginD "/usr/local/lib/libfreetype.a")
elseif (target_windows)
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/glew32.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/glew32s.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/glfw3.dll")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/glfw3.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/glfw3_mt.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/opengl/glfw3dll.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soloud/SDL2.dll")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soloud/soloud_x64.dll")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/freetype/freetype.dll")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/freetype/freetype.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/soil2/soil2.lib")
    target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/lua/lua54.dll")
endif()


# target_link_libraries (NginD ${Boost_LIBRARIES})

add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory "../resources" "${EXECUTABLE_OUTPUT_PATH}/resources"
        COMMENT "COPY RESOURCES FILES")

if (target_linux)
    add_compile_options(-ldl)
    add_compile_options(-pthread)
elseif (target_windows)
    
endif()

#add_compile_options(-lboost_fiber)
#add_compile_options(-lboost_context)
add_compile_options(-finput-charset=GBK -fexec-charset=UTF-8)