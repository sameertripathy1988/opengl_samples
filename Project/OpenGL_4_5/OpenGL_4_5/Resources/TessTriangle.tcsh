#version 430 core
layout (vertices = 3) out;
in vec3 Pos_TCS[];

out vec3 Pos_TES[];
void main()
{
Pos_TES[gl_InvocationID] = Pos_TCS[gl_InvocationID];
gl_TessLevelOuter[0] = 5;
gl_TessLevelOuter[1]=5;
gl_TessLevelOuter[2]=5;
gl_TessLevelInner[0] = 5;
}