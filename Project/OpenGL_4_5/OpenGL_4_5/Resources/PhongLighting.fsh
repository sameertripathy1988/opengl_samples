#version 430 core
out vec4 fColor;

in vec2 textureCoord;
in vec3 normal_modelspace;
in vec4 frag_pos;

uniform sampler2D diffuse_map;
uniform vec3 light_pos;

void main()
{
    vec3 light_dir = normalize(light_pos-frag_pos.xyz);
    float diffuse_intensity = max( dot(light_dir,normalize(normal_modelspace)), 0 );
    vec3 tex_color = vec3(texture(diffuse_map,textureCoord).xyz);
    vec3 final_color = (diffuse_intensity) * tex_color;
    fColor = vec4(final_color,1);
}