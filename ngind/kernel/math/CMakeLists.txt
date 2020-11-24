project(NginD)

aux_source_directory(. MATH_SRC_DIR)
add_library(math ${MATH_SRC_DIR})

target_link_libraries(NginD math)