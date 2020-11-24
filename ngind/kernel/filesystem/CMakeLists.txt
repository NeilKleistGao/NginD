project(NginD)

aux_source_directory(. FILESYSTEM_SRC_DIR)
add_library(filesystem ${FILESYSTEM_SRC_DIR})

target_link_libraries(NginD filesystem)