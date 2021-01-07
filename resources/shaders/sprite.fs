#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D image;
uniform vec4 my_color;

void main() {
    color = my_color * texture(image, TexCoord);
}
