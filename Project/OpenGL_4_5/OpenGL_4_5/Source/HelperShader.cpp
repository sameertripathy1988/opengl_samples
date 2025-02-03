#include "HelperShader.h"

#include "glew.h"

HelperShader::HelperShader()
{

}

HelperShader::~HelperShader()
{
	if (program != 0) {
		glDeleteProgram(program);
	}
}
std::string HelperShader::loadFile(const char *fname)
{
	std::ifstream file(fname);
	if (!file.is_open())
	{
		cout << "Unable to open file " << fname << endl;
		exit(1);
	}

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();
	
	return fileData.str();
}
int HelperShader::createProgram(const char* vertexShaderFile, const char* fragShaderFile, const char* geomShaderFile, const char* tesControlShaderFile,
	const char* tesEvalutaionShaderFile)
{
	string vertShaderString = loadFile(vertexShaderFile);
	string fragShaderString = loadFile(fragShaderFile);
	
	string geomShaderString;
	GLuint gShaderID = -1;
	const char* geomShaderChar = NULL;

	if(geomShaderFile != NULL)
		geomShaderString = loadFile(geomShaderFile);

	//TCS
	string tesControlShaderString;
	GLuint tesControlShaderID = -1;
	const char* tesControlShaderChar = NULL;
	//TCS Load File
	if (tesControlShaderFile != NULL)
		tesControlShaderString = loadFile(tesControlShaderFile);

	//TES
	string tesEvaluationShaderString;
	GLuint tesEvaluationShaderID = -1;
	const char* tesEvaluationShaderChar = NULL;
	//TES Load File
	if (tesEvalutaionShaderFile != NULL)
		tesEvaluationShaderString = loadFile(tesEvalutaionShaderFile);


	const char* vertShaderChar = vertShaderString.c_str();
	const char* fragShaderChar = fragShaderString.c_str();
	if (geomShaderFile != NULL)
		geomShaderChar = geomShaderString.c_str();

	//TCS
	if (tesControlShaderFile != NULL)
		tesControlShaderChar = tesControlShaderString.c_str();

	//TES
	if (tesEvalutaionShaderFile != NULL)
		tesEvaluationShaderChar = tesEvaluationShaderString.c_str();

	GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (geomShaderFile != NULL)
		gShaderID = glCreateShader(GL_GEOMETRY_SHADER);
	//TCS
	if (tesControlShaderFile != NULL)
		tesControlShaderID = glCreateShader(GL_TESS_CONTROL_SHADER);

	//TES
	if (tesEvalutaionShaderFile != NULL)
		tesEvaluationShaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);

	GLint vertShaderLength = vertShaderString.length();
	GLint fragShaderLength = fragShaderString.length();
	GLint geomShaderLength = geomShaderString.length();
	//TCS
	GLint tesControlShaderLength = tesControlShaderString.length();
	//TES
	GLint tesEvaluationShaderLength = tesEvaluationShaderString.length();

	glShaderSource(vShaderID, 1, (const char**)&vertShaderChar, (GLint*)&vertShaderLength);
	glShaderSource(fShaderID, 1, (const char**)&fragShaderChar, (GLint*)&fragShaderLength);
	if(geomShaderFile != NULL)
		glShaderSource(gShaderID, 1, (const char**)&geomShaderChar, (GLint*)&geomShaderLength);
	//TCS
	if(tesControlShaderFile != NULL)
		glShaderSource(tesControlShaderID, 1, (const char**)&tesControlShaderChar, (GLint*)&tesControlShaderLength);
	//TES
	if (tesEvalutaionShaderFile != NULL)
		glShaderSource(tesEvaluationShaderID,1, (const char**)&tesEvaluationShaderChar, (GLint*)&tesEvaluationShaderLength);


	glCompileShader(vShaderID);
	glCompileShader(fShaderID);
	if (geomShaderFile != NULL)
		glCompileShader(gShaderID);
	//TCS
	if (tesControlShaderFile != NULL)
		glCompileShader(tesControlShaderID);
	//TES
	if (tesEvalutaionShaderFile != NULL)
		glCompileShader(tesEvaluationShaderID);

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vShaderID);
	glAttachShader(programID, fShaderID);
	if (geomShaderFile != NULL)
		glAttachShader(programID, gShaderID);
	//TCS
	if (tesControlShaderFile != NULL)
		glAttachShader(programID, tesControlShaderID);

	//TES
	if (tesEvalutaionShaderFile != NULL)
		glAttachShader(programID, tesEvaluationShaderID);

	glLinkProgram(programID);
	program = programID;
	return programID;
}

int HelperShader::getProgramID()
{
	return program;
}