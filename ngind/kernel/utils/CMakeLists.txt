project(NginD)

aux_source_directory(. UTILS_SRC_DIR)
add_library(utils ${UTILS_SRC_DIR})

target_link_libraries(NginD utils)