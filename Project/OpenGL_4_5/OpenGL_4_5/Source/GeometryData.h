#pragma once
#include <glew.h>

GLfloat cube_pos_uv_n[] = {
            // back face
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f, // bottom-left
             1.0f,  1.0f, -1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f, // top-right
             1.0f, -1.0f, -1.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f, // bottom-right         
             1.0f,  1.0f, -1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f, // top-right
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f, // bottom-left
            -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,   0.0f,  0.0f, -1.0f, // top-left
            // front face        
            -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,   0.0f,  0.0f,  1.0f, // bottom-left
             1.0f, -1.0f,  1.0f, 1.0f, 0.0f,   0.0f,  0.0f,  1.0f, // bottom-right
             1.0f,  1.0f,  1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f, // top-right
             1.0f,  1.0f,  1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f, // top-right
            -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f, // top-left
            -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,   0.0f,  0.0f,  1.0f, // bottom-left
            // left face         
            -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, // top-right
            -1.0f,  1.0f, -1.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, // top-left
            -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,  -1.0f,  0.0f,  0.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,  -1.0f,  0.0f,  0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, // top-right
            // right face        
             1.0f,  1.0f,  1.0f, 1.0f, 0.0f,   1.0f,  0.0f,  0.0f, // top-left
             1.0f, -1.0f, -1.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f, // bottom-right
             1.0f,  1.0f, -1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f, // top-right         
             1.0f, -1.0f, -1.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f, // bottom-right
             1.0f,  1.0f,  1.0f, 1.0f, 0.0f,   1.0f,  0.0f,  0.0f, // top-left
             1.0f, -1.0f,  1.0f, 0.0f, 0.0f,   1.0f,  0.0f,  0.0f, // bottom-left     
             // bottom face      
             -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f, // top-right
              1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f, // top-left
              1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f, // bottom-left
              1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f, // bottom-left
             -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f, // bottom-right
             -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f, // top-right
             // top face         
             -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f, // top-left
              1.0f,  1.0f , 1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f, // bottom-right
              1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f, // top-right     
              1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f, // bottom-right
             -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f, // top-left
             -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f, // bottom-left    
};                               

GLfloat plane_pos_uv_n[] = {
	// Positions         // Texture Coords  // Normals    
	-1.0f, 0.0f, -1.0f,   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f
};

GLfloat plane_pos_uv_n_t_b[] = {
	// Positions         // Texture Coords  // Normals       // Tangents       // Bitangents
	-1.0f, 0.0f, -1.0f,    0.0f, 0.0f,       0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, -1.0f,    1.0f, 0.0f,       0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f,  1.0f,    1.0f, 1.0f,       0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
	-1.0f, 0.0f,  1.0f,    0.0f, 1.0f,       0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f
};

GLuint planeIndices[] = {
	   0, 1, 2,
	   2, 3, 0
};