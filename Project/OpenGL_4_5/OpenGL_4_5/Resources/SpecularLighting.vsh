#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 uvPos;
layout(location = 2) in vec3 normal;

out vec2 textureCoord;
out vec3 normal_modelspace;
out vec4 frag_pos;

uniform mat4 M,V,P;
void
main()
{
normal_modelspace = mat3(transpose(inverse(M))) * normal;
frag_pos = M * vPosition;
textureCoord = uvPos;
gl_Position =  P * V * M * vec4(vPosition.xyz,1);
}