option(ENABLE_I18N "" ON)

set(I18N_PATH_PREFIX extern/i18n)

if (ENABLE_I18N)
    set(I18N_HEADER
            ${I18N_PATH_PREFIX}/i18n.h
            ${I18N_PATH_PREFIX}/lang_code.h)
    set(I18N_SRC
            ${I18N_PATH_PREFIX}/i18n.cc)
else()
    set(I18N_HEADER )
    set(I18N_SRC )
endif ()
