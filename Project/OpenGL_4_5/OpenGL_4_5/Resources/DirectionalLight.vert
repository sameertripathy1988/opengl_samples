#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 uvPos;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

//Send to FS
out vec2 uv_fs;
out vec3 normal_modelspace;
out vec4 frag_pos;

uniform mat4 M,V,P;

void main()
{
    normal_modelspace = mat3(transpose(inverse(M))) * normal;
    frag_pos = M * vPosition;
    uv_fs = uvPos;
    gl_Position =  P * V * M * vec4(vPosition.xyz,1);
}