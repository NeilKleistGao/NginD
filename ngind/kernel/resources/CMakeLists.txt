project(NginD)

aux_source_directory(. RESOURCES_SRC_DIR)
add_library(resources ${RESOURCES_SRC_DIR})

target_link_libraries(resources filesystem)