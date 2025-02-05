#version 430 core
out vec4 fColor;

in vec2 textureCoord;
uniform sampler2D diffuse_map;

void main()
{
	fColor = texture(diffuse_map,textureCoord);
}
