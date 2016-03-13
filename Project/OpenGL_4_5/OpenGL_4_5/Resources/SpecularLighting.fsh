#version 430 core
out vec4 fColor;

in vec2 textureCoord;
uniform sampler2D basic_texture;
uniform vec3 light_color;
uniform float ambient_strength;
uniform float diffuse_strength;
in vec3 normal_modelspace;
in vec4 frag_pos;
uniform vec3 light_pos;
uniform vec3 camera_pos;
uniform float shineness;
void main()
{
vec3 light_dir = normalize(light_pos-frag_pos.xyz);
float diffuse_intensity = diffuse_strength * max( dot(light_dir,normalize(normal_modelspace)), 0 );
vec3 diffuse_color = diffuse_intensity * light_color;
vec3 ambient_color = ambient_strength * light_color;
vec3 view_dir = normalize(camera_pos - frag_pos.xyz);
vec3 reflect_dir = reflect(-light_dir,normalize(normal_modelspace));
float specular_intensity = pow(max(dot(view_dir,normalize(reflect_dir)), 0),shineness);
vec3 specular_color = specular_intensity * light_color;
vec3 final_color = (specular_color+diffuse_color + ambient_color) * vec3(texture(basic_texture,textureCoord).xyz);
fColor = vec4(final_color,1);
}
