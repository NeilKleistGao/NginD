project(NginD)

aux_source_directory(. MEMORY_SRC_DIR)
add_library(memory ${MEMORY_SRC_DIR})

target_link_libraries(NginD memory)