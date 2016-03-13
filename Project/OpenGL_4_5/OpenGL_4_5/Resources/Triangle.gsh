#version 430 core
layout(triangles, invocations=2) in;
layout(triangle_strip, max_vertices = 3) out;
out vec4 vColor;
void main() {
vec4 offset = vec4(-0.5,0,0,0);
if(gl_InvocationID == 1)
offset = vec4(0.5,0,0,0);

gl_Position = gl_in[0].gl_Position + offset;
vColor = vec4(1,0,0,1.0);
EmitVertex();
gl_Position = gl_in[1].gl_Position + offset;
vColor = vec4(0,1,0,1.0);
EmitVertex();
gl_Position = gl_in[2].gl_Position + offset;
vColor = vec4(0,0,1.0,1.0);
EmitVertex();
EndPrimitive();
}