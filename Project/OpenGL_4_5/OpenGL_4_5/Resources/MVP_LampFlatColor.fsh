#version 430 core
out vec4 fColor;

in vec2 textureCoord;
uniform vec3 flat_color;
void main()
{
fColor = vec4(flat_color,1.0);
}
