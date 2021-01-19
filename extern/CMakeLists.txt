project(NginD)

add_definitions(-D ENABLE_I18N)
option(enable_i18n "" ON)

if (enable_i18n)
    include(extern/i18n/CMakeLists.txt)
else()
    set(I18N_HEADER )
    set(I18N_SRC )
endif()

set(EXTERN_HEADER extern/config.h
        ${I18N_HEADER})
set(EXTERN_SRC
        ${I18N_SRC})