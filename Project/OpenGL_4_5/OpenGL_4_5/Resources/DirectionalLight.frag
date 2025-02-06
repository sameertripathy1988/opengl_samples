#version 430 core
out vec4 fColor;

in vec2 uv_fs;
in vec3 normal_modelspace;
in vec4 frag_pos;

//Already in world space
uniform vec3 light_dir;
uniform vec3 view_pos;

uniform sampler2D diffuse_map;

void main()
{
    vec4 tex_color = texture(diffuse_map, uv_fs);

    vec3 norm = normalize(normal_modelspace);

    vec3 light =  normalize(-light_dir);
    float diff = max(dot(light, norm),0);

    vec3 diffuse_color = diff * tex_color.rgb;

    //Specular
    vec3 viewDir = normalize(view_pos - frag_pos.xyz);
    vec3 reflectDir = reflect(-light, norm);

    float specular_intensity = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 specular_color = 0.5 * specular_intensity * tex_color.rgb;

    vec3 final = vec3(0.2)* tex_color.rgb + diffuse_color + specular_color;
    fColor = vec4(final,1.0);
}
