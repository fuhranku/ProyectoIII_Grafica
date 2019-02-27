#include "Main.h"
#include <iostream> 
#include <fstream> 
using namespace std;
using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;

void updateUserInterface()
{

}

void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		//despliegue de modelos
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
	glPopMatrix();
}

void initHelpers()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
}

void initLights()
{
	//Propiedades de luz 1:
	GLfloat light_position0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular0[] = { 0.22f, 1.0f, 0.02f, 1.0f };
	GLfloat light_ambient0[] = { 0.0F, 0.0F, 0.27F, 1.0F };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glEnable(GL_LIGHT0);

	//Propiedades de luz 2:
	GLfloat light_position1[] = { 0.0F, 0.0F, 0.0F, 1.0F };
	GLfloat light_diffuse1[] = { 0.59f, 0.15f, 0.62f, 1.0f };
	GLfloat light_specular1[] = { 1.0f, 0.16f , 0.77f, 1.0f };
	GLfloat light_ambient1[] = { 0.0F, 0.2F, 0.33F, 1.0F };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glEnable(GL_LIGHT1);

}

void initSounds()
{
	//inicializar sonido
}

void initObjs()
{
	//cargar objetos
}

void getMatriz4x4(glm::vec4 quat, float *mat)
{
	float yy2 = 2.0f * quat[1] * quat[1];
	float xy2 = 2.0f * quat[0] * quat[1];
	float xz2 = 2.0f * quat[0] * quat[2];
	float yz2 = 2.0f * quat[1] * quat[2];
	float zz2 = 2.0f * quat[2] * quat[2];
	float wz2 = 2.0f * quat[3] * quat[2];
	float wy2 = 2.0f * quat[3] * quat[1];
	float wx2 = 2.0f * quat[3] * quat[0];
	float xx2 = 2.0f * quat[0] * quat[0];

	mat[0] = -yy2 - zz2 + 1.0f;
	mat[1] = xy2 + wz2;
	mat[2] = xz2 - wy2;
	mat[4] = xy2 - wz2;
	mat[5] = -xx2 - zz2 + 1.0f;
	mat[6] = yz2 + wx2;
	mat[8] = xz2 + wy2;
	mat[9] = yz2 - wx2;
	mat[10] = -xx2 - yy2 + 1.0f;

	mat[3] = mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
	mat[15] = 1;
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{


	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			//evento al presionar teclas
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		}
	}
}



void destroy()
{
	//liberar todo de la memoria
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Chapter 2", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	/* listener for input with cursor "raycast" , mouse click event, and enter char
		glfwSetMouseButtonCallback(gWindow, mouseButton);
		glfwSetCursorPosCallback(gWindow, cursorPos);
		glfwSetCharCallback(gWindow, charInput);
	*/

	return true;
}

bool initUserInterface()
{
	//inicializar menu

	return true;
}

void initScene()
{
	//inicializar todo
	initHelpers();//camera,etc
	initLights();
	initSounds();
	initObjs();		
}

int main(void)
{
	gWidth = 1600;
	gHeight = 900;
	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;

	initScene();
	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	while (!glfwWindowShouldClose(gWindow))
	{ //todo esto se llama por frame

		render(); 

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}
