#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D image;
uniform vec4 my_color;
uniform float opaque;

void main() {
    color = opaque * my_color * texture(image, TexCoord);
}