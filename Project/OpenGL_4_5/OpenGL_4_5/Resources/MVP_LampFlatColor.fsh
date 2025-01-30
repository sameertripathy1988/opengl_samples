#version 430 core
out vec4 fColor;

in vec2 textureCoord;
uniform vec3 flat_color;
in vec3 normal_modelspace;
in vec4 frag_pos;
void main()
{
    fColor = vec4(flat_color,1.0);
}
