#include "ModelLoadingTest.h"


static float angle = 0.0f;

ModelLoadingTest::ModelLoadingTest()
{
	name = "OpenGL 4.5 Model Loading Test";
	rotMatrix = new MyMatrix();
}

ModelLoadingTest::~ModelLoadingTest()
{
	delete rotMatrix;
	delete texShader;
}

GLuint uvBuffer;

void ModelLoadingTest::InitScene()
{

	std::string inputfile = "cube.obj";
	
	
	std::string err = tinyobj::LoadObj(shapes, materials, inputfile.c_str());

	if (!err.empty()) {
		std::cerr << err << std::endl;
		exit(1);
	}

	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;

	for (size_t i = 0; i < shapes.size(); i++) {
		printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
		printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
		printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
		//	assert((shapes[i].mesh.indices.size() % 3) == 0);
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2], shapes[i].mesh.material_ids[f]);
		}

		printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
		//	assert((shapes[i].mesh.positions.size() % 3) == 0);
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			printf("  v[%ld] = (%f, %f, %f)\n", v,
				shapes[i].mesh.positions[3 * v + 0],
				shapes[i].mesh.positions[3 * v + 1],
				shapes[i].mesh.positions[3 * v + 2]);
		}
	}
	for (size_t i = 0; i < materials.size(); i++) {
		printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
		printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
		printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
		printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
		printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
		printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
		printf("  material.Ns = %f\n", materials[i].shininess);
		printf("  material.Ni = %f\n", materials[i].ior);
		printf("  material.dissolve = %f\n", materials[i].dissolve);
		printf("  material.illum = %d\n", materials[i].illum);
		printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
		printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
		printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
		//printf("  material.map_Ns = %s\n", materials[i].normal_texname.c_str());
		std::map<string, string >::const_iterator it(materials[i].unknown_parameter.begin());
		std::map<string, string>::const_iterator itEnd(materials[i].unknown_parameter.end());
		for (; it != itEnd; it++) {
			printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
		}
		printf("\n");
	}

	GLfloat points[] =
	{
		-0.5f, 0.5f, 0.0f, //0,1
		0.5f, 0.5f, 0.0f,  //1,1
		0.5f, -0.5f, 0.0f, //1,0
		-0.5f, -0.5f, 0.0f //0,0
	};


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;


	/*GLfloat uv[] = { 0, 1.0,
	1.0, 1.0,
	1.0, 0,
	0, 1.0,
	1.0, 0,
	0, 0
	};*/

	//Inverted Y
	GLfloat uv[] = { 1.0, 1,
		1.0, 0.0,
		0, 0.0,
		0, 1
	};


	texShader = new HelperShader();
	texShader->createProgram("MVP_Texture.vsh", "MVP_Texture.fsh");

	//VBO created in memory
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.positions.size() * sizeof(float), a, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	
	
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int width, height, channels;
	unsigned char* pixelData = NULL;
	pixelData = SOIL_load_image("crate.png", &width, &height, &channels, 4);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)pixelData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glUseProgram(texShader->getProgramID());
	
	GLint texLoc = glGetUniformLocation(texShader->getProgramID(), "basic_texture");
	glUniform1i(texLoc, 0);
}

void ModelLoadingTest::UpdateScene()
{
	
}


void ModelLoadingTest::RenderScene()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0, 0.5, 1.0, 1.0);//clear white
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(texShader->getProgramID());

	
//	angle += 5.0f;
	for (int i = 0; i < shapes.size(); i++)
	{
		MyMatrix mat_Model;
		MyMatrix mat_View;
		MyMatrix mat_Proj;

		//MyMatrix mat_Scale;
		//mat_Scale.scaleMatrix(0.75f, 0.75f, 0.75f);

		MyMatrix mat_TranslationO;
		mat_TranslationO.translateMatrix(-1.0f, -1.0f, -1.0f);


		MyMatrix mat_Translation;
		mat_Translation.translateMatrix(0.0f, 0.0f, -10.0f);

	//	MyMatrix mat_RotationAbtZ;
	// 	mat_RotationAbtZ.rotateMatrixAboutY(angle);

		Quaternion q;
		q.CreateFromAxisAngle(0.0f, 0.0f, 1.0f, 90);

		q = Quaternion::normalize(q);
		q.createMatrix(rotMatrix);


		mat_Model = mat_Translation * (*rotMatrix) * mat_TranslationO;// *mat_Scale;

		mat_Proj.createPerspectiveProjectionMatrix(60.0f, 1024.0f, 768.0f, 0.1f, 100.0f); //Initially camera is identity matrix i.e. camera space = world space,
																						  //direction vector pointing -z i.e. inside the screen(into)

		mat_View.lookAt(Vector(0,4*sinf(TORADIAN(45)), -5 * cosf(TORADIAN(45))), Vector(0, 0, -10), Vector(0, 1, 0));

		GLuint Ppos = glGetUniformLocation(texShader->getProgramID(), "P");
		GLuint Vpos = glGetUniformLocation(texShader->getProgramID(), "V");
		GLuint Mpos = glGetUniformLocation(texShader->getProgramID(), "M");

		glUseProgram(texShader->getProgramID());

		glUniformMatrix4fv(Ppos, 1, GL_TRUE, &mat_Proj.arr[0][0]);
		glUniformMatrix4fv(Vpos, 1, GL_TRUE, &mat_View.arr[0][0]);
		glUniformMatrix4fv(Mpos, 1, GL_TRUE, &mat_Model.arr[0][0]);
		GLfloat* a = &(shapes[i].mesh.positions[0]);
		GLuint *b = &(shapes[i].mesh.indices[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, shapes[i].mesh.positions.size() * sizeof(float), a, GL_DYNAMIC_DRAW);

	//	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	//	glBufferData(GL_ARRAY_BUFFER, shapes[i].mesh.texcoords.size() * sizeof(float), &shapes[i].mesh.texcoords[0], GL_STATIC_DRAW);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, b);
	}
}