project(NginD)

aux_source_directory(. TIMER_SRC_DIR)
add_library(timer ${TIMER_SRC_DIR})

target_link_libraries(NginD timer)