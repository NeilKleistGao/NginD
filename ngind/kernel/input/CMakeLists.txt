project(NginD)

aux_source_directory(. INPUT_SRC_DIR)
add_library(input ${INPUT_SRC_DIR})

target_link_libraries(NginD input)