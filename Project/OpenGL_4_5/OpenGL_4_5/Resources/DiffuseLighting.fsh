#version 430 core
out vec4 fColor;

in vec2 textureCoord;
uniform sampler2D basic_texture;
uniform vec3 light_color;
uniform float ambient_strength;

in vec3 normal_modelspace;
in vec4 frag_pos;
uniform vec3 light_pos;
void main()
{
vec3 light_dir = normalize(light_pos-frag_pos.xyz);
float diffuse_intensity = max( dot(light_dir,normalize(normal_modelspace)), 0 );
vec3 diffuse_color = diffuse_intensity * light_color;
vec3 ambient_color = ambient_strength * light_color;
vec3 final_color = (diffuse_color + ambient_color) * vec3(texture(basic_texture,textureCoord).xyz);
fColor = vec4(final_color,1);
}
