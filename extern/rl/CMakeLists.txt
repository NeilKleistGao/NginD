option(ENABLE_RL "" ON)

if (ENABLE_RL)
    LIST_HEADER(${CMAKE_CURRENT_LIST_DIR} RL_HEADER)
    LIST_SRC(${CMAKE_CURRENT_LIST_DIR} RL_SRC)

    add_definitions(-D ENABLE_RL)
else()
    set(RL_HEADER )
    set(RL_SRC )
endif ()