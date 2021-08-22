set(RENDER_PATH_PREFIX kernel/rendering)

set(RENDER_HEADER
        ${RENDER_PATH_PREFIX}/font_factory.h
        ${RENDER_PATH_PREFIX}/camera.h
        ${RENDER_PATH_PREFIX}/program.h
        ${RENDER_PATH_PREFIX}/quad.h
        ${RENDER_PATH_PREFIX}/renderer.h
        ${RENDER_PATH_PREFIX}/rendering_queue.h
        ${RENDER_PATH_PREFIX}/rendering_command.h
        ${RENDER_PATH_PREFIX}/color.h
        ${RENDER_PATH_PREFIX}/shader.h
        ${RENDER_PATH_PREFIX}/texture.h
        ${RENDER_PATH_PREFIX}/true_type_font.h
        ${RENDER_PATH_PREFIX}/window.h
        ${RENDER_PATH_PREFIX}/character.h
        ${RENDER_PATH_PREFIX}/quad_rendering_command.h
        ${RENDER_PATH_PREFIX}/batch_quad_rendering_command.h
        ${RENDER_PATH_PREFIX}/adaptor.h)

set(RENDER_SRC
        ${RENDER_PATH_PREFIX}/font_factory.cc
        ${RENDER_PATH_PREFIX}/camera.cc
        ${RENDER_PATH_PREFIX}/program.cc
        ${RENDER_PATH_PREFIX}/quad.cc
        ${RENDER_PATH_PREFIX}/renderer.cc
        ${RENDER_PATH_PREFIX}/rendering_queue.cc
        ${RENDER_PATH_PREFIX}/shader.cc
        ${RENDER_PATH_PREFIX}/texture.cc
        ${RENDER_PATH_PREFIX}/true_type_font.cc
        ${RENDER_PATH_PREFIX}/window.cc
        ${RENDER_PATH_PREFIX}/quad_rendering_command.cc
        ${RENDER_PATH_PREFIX}/batch_quad_rendering_command.cc
        ${RENDER_PATH_PREFIX}/adaptor.cc)