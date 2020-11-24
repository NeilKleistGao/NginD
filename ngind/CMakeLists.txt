cmake_minimum_required(VERSION 3.15)
project(NginD)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-D PLATFORM_LINUX)

include_directories(..)
include_directories(kernel)
include_directories(../include)
include_directories(../include/opengl)
include_directories(../include/libpng)
include_directories(../resources)
include_directories(.)

include_directories(/usr/local/include/freetype2)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_BOOST_CMAKE ON)

set(PLATFORM_PREFIX "/../lib/linux")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../bin")

find_package(Boost COMPONENTS fiber REQUIRED)

aux_source_directory(. DIR_SRC_NGIND)
add_library(ngind ${DIR_SRC_NGIND})

add_executable(NginD ${DIR_SRC_NGIND})
add_subdirectory(kernel)

target_link_libraries(NginD ngind kernel)
target_link_libraries(NginD "${CMAKE_SOURCE_DIR}/${PLATFORM_PREFIX}/rttr/librttr_core.so")
target_link_libraries (NginD ${Boost_LIBRARIES})

add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory "../../resources" "${EXECUTABLE_OUTPUT_PATH}/resources"
        COMMENT "COPY RESOURCES FILES")

add_compile_options(-pthread)
add_compile_options(-lboost_fiber)
add_compile_options(-lboost_context)
add_compile_options(-finput-charset=GBK -fexec-charset=UTF-8)