#version 430 core
out vec4 fColor;

in vec2 textureCoord;
uniform sampler2D basic_texture;
uniform vec3 light_color;
uniform float ambient_strength;
void main()
{
    vec3 ambient_color = ambient_strength * light_color;
    vec3 final_color = ambient_color * vec3(texture(basic_texture,textureCoord).xyz);
    fColor = vec4(final_color,1);
}
