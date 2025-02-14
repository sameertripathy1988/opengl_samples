
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
#include "PhongLighting.h"
#include "ShadowMapping.h"
#include "CascadedShadowMapping.h"
#include <Util.h>

using namespace std;

#define CURRENT_TEST 12
#define MAX_TESTS 15

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

BlankTest** tests;
BlankTest* currentTest;
int nCurrentTest = CURRENT_TEST;

void menu(int);
void keyboardUp(unsigned char key, int x, int y);
void keyboardSpecialFunc(int key, int x, int y);
void mouseWheelFunction(int wheel, int direction, int x, int y);

int prev_y = 0;
int prev_x = 0;
bool bIsMouseLBDown = false;

float prev_time = 0.0f;

void RenderScene(void)
{
	float current_time = GetTickCount64() / 1000.0f;;
	Util::delta_time = current_time - prev_time;
	prev_time = current_time;

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
	tests[12] = new PhongLighting();
	tests[13] = new ShadowMapping();
	tests[14] = new CascadedShadowMapping();

	currentTest = tests[nCurrentTest];

	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);  // Major = 4, Minor = 0
	glutInitContextProfile(GLUT_CORE_PROFILE);  // Use core profile

	// Optional: Enable forward compatibility (removes deprecated features)
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowPosition(1920/2, 1080/2);//optional
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //optional
	glutCreateWindow(currentTest->name);
	// Initialize GLEW
	glewExperimental = GL_TRUE;  // Important for core profile
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Error initializing GLEW: " << glewGetErrorString(err) << std::endl;
		return -1;
	}

	// Check OpenGL version
	std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << std::endl;
	glutKeyboardUpFunc(keyboardUp);
	glutKeyboardFunc([](unsigned char x, int y, int z)
		{
			currentTest->UpdateInput(x, y, z);
		});
	glutSpecialFunc(keyboardSpecialFunc);
	
	glutMouseWheelFunc(mouseWheelFunction);
	glutMouseFunc(
		[](int button, int state, int x, int y)
		{
			if (button == GLUT_LEFT_BUTTON)
			{
				if (state == GLUT_DOWN)
				{
					bIsMouseLBDown = true;
					prev_y = y;
					prev_x = x;
				}
				else
					bIsMouseLBDown = false;
			}
		}
	);
	glutMotionFunc(
		[](int x, int y) {
			if (bIsMouseLBDown)
			{
				int dx = x - prev_x;
				int dy = y - prev_y;
				currentTest->UpdateMouseInput(dx, dy, bIsMouseLBDown);
				prev_y = y;
				prev_x = x;
			}
			else
			{
				prev_x = x;
				prev_y = y;
			}
		});
	GLenum error = glewInit();
	if (error == GLEW_OK) {

		// Get the OpenGL version string
		const char* glew_version_str = (const char*)glGetString(GL_VERSION);

		// Print the version
		std::cout << "Supported OpenGL version with GLEW: " << glew_version_str << std::endl;

	}
	if (GL_ARB_direct_state_access)
	{
		cout << "DSA" << endl;
	}
	else
		cout << "No DSA" << endl;
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

void clearCurrentTest()
{
	currentTest->clear();
}

void clearAll()
{
	for (int i = 0; i < MAX_TESTS; i++)
	{
		tests[i]->clear();
		delete tests[i];
		tests[i] = nullptr;
	}
	delete[] tests;
	tests = nullptr;
}
bool canSwitch = true;
void switchTest()
{
	canSwitch = false;
	clearCurrentTest();
	currentTest = tests[nCurrentTest];
	currentTest->InitScene();
	glutSetWindowTitle(currentTest->name);
	canSwitch = true;
}
//Only once when key is released
void keyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		clearAll();
		exit(0);
		break;
	
	default:
		/*currentTest = tests[nCurrentTest];*/
		currentTest->UpdateButtonUp(key);
		break;
	}
}

//Continous press inputs if kept pressed
void keyboardSpecialFunc(int key, int x, int y)
{
	if (!canSwitch) return;
	switch (key)
	{
		case GLUT_KEY_F1:
			nCurrentTest--;
			if (nCurrentTest == -1) nCurrentTest = MAX_TESTS - 1;
			std::cout << "F1" << nCurrentTest << std::endl;
			switchTest();
			break;
		case GLUT_KEY_F2:
			nCurrentTest++;
			if (nCurrentTest == MAX_TESTS ) nCurrentTest = 0;
			std::cout << "F2" << nCurrentTest << std::endl;
			switchTest();
			break;
		case GLUT_KEY_F5:
			switchTest();
			break;
		default:
			break;
	}
}

void mouseWheelFunction(int wheel, int direction, int x, int y)
{
	currentTest = tests[nCurrentTest];
	currentTest->UpdateMouseWheel(wheel, direction, x, y);
}

