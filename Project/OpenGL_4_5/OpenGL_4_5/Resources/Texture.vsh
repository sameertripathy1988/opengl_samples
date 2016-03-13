#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 uvPos;
out vec2 textureCoord;
void
main()
{
textureCoord = uvPos;
gl_Position = vPosition;
}