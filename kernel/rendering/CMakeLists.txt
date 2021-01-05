include(kernel/rendering/adapter/CMakeLists.txt)

set(RENDER_HEADER
        kernel/rendering/font_factory.h
        kernel/rendering/perspective.h
        kernel/rendering/program.h
        kernel/rendering/quad.h
        kernel/rendering/renderer.h
        kernel/rendering/rendering_queue.h
        kernel/rendering/render_command.h
        kernel/rendering/rgba.h
        kernel/rendering/shader.h
        kernel/rendering/texture.h
        kernel/rendering/true_type_font.h
        kernel/rendering/window.h
        kernel/rendering/character.h)

set(RENDER_SRC
        kernel/rendering/font_factory.cc
        kernel/rendering/perspective.cc
        kernel/rendering/program.cc
        kernel/rendering/quad.cc
        kernel/rendering/renderer.cc
        kernel/rendering/rendering_queue.cc
        kernel/rendering/shader.cc
        kernel/rendering/texture.cc
        kernel/rendering/true_type_font.cc
        kernel/rendering/window.cc)