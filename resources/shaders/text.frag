#version 330 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 my_color;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
    color = my_color * sampled;
}
