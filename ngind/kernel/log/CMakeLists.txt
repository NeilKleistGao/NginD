project(NginD)

aux_source_directory(. LOG_SRC_DIR)
add_library(log ${LOG_SRC_DIR})

target_link_libraries(NginD log)