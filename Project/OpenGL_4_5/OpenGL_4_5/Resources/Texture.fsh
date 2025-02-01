#version 430 core
out vec4 fColor;

in vec2 textureCoord;

uniform sampler2D diffuse_map;


void main()
{
    vec4 tex_color = vec4(texture(diffuse_map,textureCoord).xyzw);
    fColor = vec4(tex_color);
}
