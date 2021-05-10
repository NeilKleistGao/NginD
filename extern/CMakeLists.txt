project(NginD)

include(extern/i18n/CMakeLists.txt)
include(extern/physics/CMakeLists.txt)

set(EXTERN_HEADER
        ${I18N_HEADER}
        ${PHYSICS_HEADER})
set(EXTERN_SRC
        ${I18N_SRC}
        ${PHYSICS_SRC})