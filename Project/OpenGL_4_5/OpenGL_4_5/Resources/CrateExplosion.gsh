#version 430 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;
uniform float counterX;
out vec2 textureCoordinates;
in vec2 textureCoord[];
vec3 GetNormal()
{
vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
return normalize(cross(a,b));
}

vec4 Explode(vec4 position, vec3 normal)
{
float magnitude = 5.0;
vec4 direction=vec4(normal * ((sin(counterX)+1)/2) * magnitude,0);
return position+direction;
}
void main() {
vec3 normal= GetNormal();
gl_Position = Explode(gl_in[0].gl_Position,normal);
textureCoordinates=textureCoord[0];
EmitVertex();
gl_Position = Explode(gl_in[1].gl_Position,normal);
textureCoordinates=textureCoord[1];
EmitVertex();
gl_Position = Explode(gl_in[2].gl_Position,normal);
textureCoordinates=textureCoord[2];
EmitVertex();
EndPrimitive();
}