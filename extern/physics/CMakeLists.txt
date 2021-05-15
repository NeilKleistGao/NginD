option(ENABLE_PHYSICS "" ON)

set(PHYSICS_PATH_PREFIX extern/physics)

if (ENABLE_PHYSICS)
    set(PHYSICS_HEADER
            ${PHYSICS_PATH_PREFIX}/physics_world.h
            ${PHYSICS_PATH_PREFIX}/rigid_body.h
            ${PHYSICS_PATH_PREFIX}/physics_shape.h
            ${PHYSICS_PATH_PREFIX}/physics_listener.h
            ${PHYSICS_PATH_PREFIX}/physics_joint.h)
    set(PHYSICS_SRC
            ${PHYSICS_PATH_PREFIX}/physics_world.cc
            ${PHYSICS_PATH_PREFIX}/rigid_body.cc
            ${PHYSICS_PATH_PREFIX}/physics_shape.cc
            ${PHYSICS_PATH_PREFIX}/physics_listener.cc
            ${PHYSICS_PATH_PREFIX}/physics_joint.cc)

    add_definitions(-D ENABLE_PHYSICS)
else()
    set(PHYSICS_HEADER )
    set(PHYSICS_SRC )
endif ()