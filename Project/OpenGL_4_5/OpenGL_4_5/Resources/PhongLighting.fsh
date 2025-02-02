#version 430 core
out vec4 fColor;

in vec2 uv_fs;
in vec3 normal_modelspace;
in vec4 frag_pos;

in vec3 tangentSpace_lightPos;
in vec3 tangentSpace_viewPos;
in vec3 tangentSpace_fragPos;

uniform sampler2D diffuse_map;
uniform sampler2D normal_map;
uniform int enable_normal_map;

uniform vec3 light_pos;
 
void main()
{
    // Sample the normal map and transform the value from [0,1] to [-1,1]
    vec3 normal_tangentSpace = texture(normal_map, uv_fs).xyz;
    normal_tangentSpace = (normal_tangentSpace * 2.0) - 1.0;
    
    // Sample the diffuse (albedo) texture
    vec3 tex_color = texture(diffuse_map, uv_fs).xyz;

    // Compute the light direction in tangent space
    vec3 light_dir_tangentSpace = normalize(tangentSpace_lightPos - tangentSpace_fragPos);
    
    // Use the sampled normal from the normal map for lighting calculations.
    float diffuse_intensity = max(dot(light_dir_tangentSpace, normal_tangentSpace), 0.0);
    vec4 diffuse_color = vec4(diffuse_intensity * tex_color, 1.0); // Diffuse color

    // Compute view direction in tangent space
    vec3 view_dir_tangentSpace = normalize(tangentSpace_viewPos - tangentSpace_fragPos);
    
    // Compute reflection and half vector for specular lighting
    vec3 reflect_dir = reflect(-light_dir_tangentSpace, normal_tangentSpace);
    vec3 half_dir = normalize(light_dir_tangentSpace + view_dir_tangentSpace);

    // Specular intensity using Blinn-Phong model
    float specular_intensity = pow(max(dot(normal_tangentSpace, half_dir), 0.0), 32.0);
    
    // Sum of diffuse and specular components
    float total_intensity = diffuse_intensity + specular_intensity;

    // Normalize if total_intensity > 1
    if (total_intensity > 1.0) {
        diffuse_intensity /= total_intensity;
        specular_intensity /= total_intensity;
    }
    vec3 specular_color = specular_intensity * vec3(1);
    // Combine diffuse and specular components (here, only diffuse is being used)
    vec3 final_color = (diffuse_intensity * tex_color) + specular_color;
    if(enable_normal_map == 0)
    {
        vec3 light_dir = normalize(light_pos-frag_pos.xyz);
        float diff_intensity = max( dot(light_dir,normalize(normal_modelspace)), 0 );
        fColor = vec4(diff_intensity*tex_color, 1.0);
    }
    else
    {
        fColor = vec4(final_color, 1.0);
    }
}
