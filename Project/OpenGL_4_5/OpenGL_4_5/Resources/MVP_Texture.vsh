#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 uvPos;
out vec2 textureCoord;
uniform mat4 M,V,P;
void main()
{
    textureCoord = uvPos;
    gl_Position =  P * V * M * vec4(vPosition.xyz,1);
}