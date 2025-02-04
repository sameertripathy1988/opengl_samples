#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 uvPos;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec2 uv_fs;
out vec3 normal_modelspace;
out vec4 frag_pos;
out vec4 frag_pos_lightspace;

out vec3 tangentSpace_lightPos;
out vec3 tangentSpace_viewPos;
out vec3 tangentSpace_fragPos;

uniform vec3 light_pos;
uniform vec3 view_pos;

uniform mat4 M,V,P;
uniform mat4 lightSpaceMatrix;
uniform int enableShadow;
void main()
{
    mat3 normal_matrix = mat3(transpose(inverse(mat3(M))));

    //Calc T and N in MODEL Space
    vec3 T = normalize(normal_matrix * aTangent); //Tangent in MODEL Space
    vec3 N = normalize(normal_matrix * normal); //NORMAL in MODEL Space

    T = normalize(T - dot(T, N) * N); //Orthogonalize T
    vec3 B = cross(N, T); //Calculate B

    mat3 invTBN = transpose(mat3(T, B, N)); //TBN Matrix as inverse and transpose are same for orthogonal matrix
    tangentSpace_lightPos = invTBN * light_pos;
    tangentSpace_viewPos = invTBN * view_pos;

    //Sending extra normal data to Fragment shader in case of no normal map
    normal_modelspace = mat3(transpose(inverse(M))) * normal;
    frag_pos = M * vPosition;
    tangentSpace_fragPos = invTBN * frag_pos.xyz;
    uv_fs = uvPos;
    if(enableShadow == 1)
    {
        frag_pos_lightspace = lightSpaceMatrix * vec4(frag_pos.xyz, 1);
    }
    gl_Position =  P * V * M * vec4(vPosition.xyz,1);
}