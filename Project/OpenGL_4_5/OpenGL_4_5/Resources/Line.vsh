#version 430 core
layout(location = 0) in vec4 vPosition;

uniform mat4 M,V,P;
void main()
{
    gl_Position =  P * V * M * vec4(vPosition.xyz,1);
}