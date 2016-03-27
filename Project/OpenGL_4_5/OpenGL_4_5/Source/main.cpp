
#include "glew.h"
#include "freeglut.h"
#include "HelperShader.h"
#include "BlankTest.h"
#include "TriangleTest.h"
#include "TextureMaping.h"
#include "ColoredTriangle.h"
#include "MVPTest.h"
#include "ModelLoadingTest.h"
#include "TessellationTest.h"
#include "GeometryShaderSample.h"
#include "GeometryShaderCircleTest.h"
#include "GeometryShaderModelExplodingTest.h"
#include "AmbientLightingTest.h"
#include "DiffuseLightingTest.h"
#include "SpecularLightingTest.h"

using namespace std;

#define CURRENT_TEST 9
#define MAX_TESTS 12

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

BlankTest** tests;
BlankTest* currentTest;
int nCurrentTest = CURRENT_TEST;

void menu(int);
void keyboardUp(unsigned char key, int x, int y);
void keyboardSpecialFunc(int x, int y, int z);
void mouseWheelFunction(int wheel, int direction, int x, int y);

void RenderScene(void)
{
	currentTest->UpdateScene();
	currentTest->RenderScene();
	glutSwapBuffers();
	glutPostRedisplay();
}

void InitScene()
{
	currentTest->InitScene();
}

int main(int argc, char **argv)
{

	tests = new BlankTest*[MAX_TESTS];
	
	tests[0] = new TriangleTest();
	tests[1] = new TextureMaping();
	tests[2] = new ColoredTriangle();
	tests[3] = new MVPTest();
	tests[4] = new ModelLoadingTest();
	tests[5] = new TessellationTest();
	tests[6] = new GeometryShaderSample();
	tests[7] = new GeometryShaderCircleTest();
	tests[8] = new GeometryShaderModelExplodingTest();
	tests[9] = new AmbientLightingTest();
	tests[10] = new DiffuseLightingTest();
	tests[11] = new SpecularLightingTest();

	currentTest = tests[nCurrentTest];

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowPosition(1920/2, 1080/2);//optional
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //optional
	glutCreateWindow(currentTest->name);
	
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keyboardSpecialFunc);
	
	glutMouseWheelFunc(mouseWheelFunction);
	GLenum error = glewInit();
	if (!glewIsSupported("GL_VERSION_4_5"))
		std::cout << "GLEW 4.5 not supported\n ";
	
	InitScene();
	glEnable(GL_DEPTH_TEST);

	// register callbacks
	glutDisplayFunc(RenderScene);

	glutMainLoop();
	return 0;
}

void menu(int value)
{
	if (value == 1)
		nCurrentTest++;
	else if (value == 2)
		nCurrentTest--;

	currentTest = tests[nCurrentTest];
	currentTest->InitScene();
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
		if (nCurrentTest != MAX_TESTS - 1)
		{
			nCurrentTest++;
			currentTest = tests[nCurrentTest];
			currentTest->InitScene();
			glutSetWindowTitle(currentTest->name);
		}
		break;
	case 'a':
		if (nCurrentTest != 0)
		{
			nCurrentTest--;
			currentTest = tests[nCurrentTest];
			currentTest->InitScene();
			glutSetWindowTitle(currentTest->name);
		}
		break;
	case 27:
		exit(0);
		break;
	default:
		currentTest = tests[nCurrentTest];
		currentTest->UpdateInput((int)key, x, y);
		break;
	}
}

void keyboardSpecialFunc(int x, int y, int z)
{
	currentTest = tests[nCurrentTest];
	currentTest->UpdateInput(x, y, z);
}

void mouseWheelFunction(int wheel, int direction, int x, int y)
{
	currentTest = tests[nCurrentTest];
	currentTest->UpdateMouseWheel(wheel, direction, x, y);
}

