#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 iColor;
out vec4 oColor;
void
main()
{
oColor = iColor;
gl_Position = vPosition;
}