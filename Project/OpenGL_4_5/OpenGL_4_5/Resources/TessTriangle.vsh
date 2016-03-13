#version 430 core
layout(location = 0) in vec4 vPosition;
out vec3 Pos_TCS;
void
main()
{
Pos_TCS = vPosition.xyz;
}