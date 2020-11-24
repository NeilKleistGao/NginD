project(NginD)

aux_source_directory(. OBJECTS_SRC_DIR)
add_library(objects ${OBJECTS_SRC_DIR})

target_link_libraries(NginD objects)