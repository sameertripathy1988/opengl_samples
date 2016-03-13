#version 430 core
layout(points) in;
layout(triangle_strip, max_vertices = 108) out;
out vec4 vColor;
const float SIDES = 36;
const float PI = 3.1415926;
const float RADIUS=0.25;
const float ASPECT_RATIO=1.33;
float angle=0;
void main() {
vec4 offset = vec4(0.1,0,0,0);
vColor = vec4(1,0,0,1.0);
vec4 firstVertex;
vec4 secondVertex;
for(int i = 0; i < SIDES; i++)
{
angle=i*(PI/180.0)*360/SIDES;
vec4 firstVertex = gl_in[0].gl_Position + vec4(RADIUS*cos(angle),RADIUS*sin(angle),0,0);
gl_Position = firstVertex*vec4(1/ASPECT_RATIO,1,1,1);
EmitVertex();
angle=(i+1)*(PI/180.0)*360/SIDES;
vec4 secondVertex = gl_in[0].gl_Position + vec4(RADIUS*cos(angle),RADIUS*sin(angle),0,0);
gl_Position = secondVertex*vec4(1/ASPECT_RATIO,1,1,1);
EmitVertex();
gl_Position = gl_in[0].gl_Position;
EmitVertex();
}
EndPrimitive();
}