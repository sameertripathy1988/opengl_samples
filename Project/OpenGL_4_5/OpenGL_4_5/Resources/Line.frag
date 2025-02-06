#version 330 core
out vec4 fColor;

uniform vec3 flat_color;

void main() {
    fColor = vec4(flat_color.xyz, 1.0); // White color
}