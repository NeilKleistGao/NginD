include(extern/i18n/CMakeLists.txt)
include(extern/physics/CMakeLists.txt)
include(extern/rl/CMakeLists.txt)

set(EXTERN_HEADER
        ${I18N_HEADER}
        ${PHYSICS_HEADER}
        ${RL_HEADER})
set(EXTERN_SRC
        ${I18N_SRC}
        ${PHYSICS_SRC}
        ${RL_SRC})