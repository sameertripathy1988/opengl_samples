#version 430 core
out vec4 fColor;

in vec2 textureCoordinates;
uniform sampler2D basic_texture;

void main()
{
fColor = texture(basic_texture,textureCoordinates);
}
