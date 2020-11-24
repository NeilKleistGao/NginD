project(NginD)

aux_source_directory(. COMPONENTS_SRC_DIR)
add_library(components ${COMPONENTS_SRC_DIR})

target_link_libraries(components math)