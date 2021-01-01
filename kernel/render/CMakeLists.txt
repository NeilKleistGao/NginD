include(kernel/render/adapter/CMakeLists.txt)

set(RENDER_HEADER
        kernel/render/font_factory.h
        kernel/render/perspective.h
        kernel/render/program.h
        kernel/render/quad.h
        kernel/render/render.h
        kernel/render/render_queue.h
        kernel/render/render_command.h
        kernel/render/rgba.h
        kernel/render/shader.h
        kernel/render/texture.h
        kernel/render/true_type_font.h
        kernel/render/window.h)

set(RENDER_SRC
        kernel/render/font_factory.cc
        kernel/render/perspective.cc
        kernel/render/program.cc
        kernel/render/quad.cc
        kernel/render/render.cc
        kernel/render/render_queue.cc
        kernel/render/shader.cc
        kernel/render/texture.cc
        kernel/render/true_type_font.cc
        kernel/render/window.cc)