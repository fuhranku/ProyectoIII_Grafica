#include "Main.h"
#include "Model.h"
#include "SOff.h"
#include "Off.h"
#include "Obj.h"
#include "UserInterface.h"
#include <iostream> 
#include <fstream> 

using namespace std;
using std::vector;
GLFWwindow *gWindow;
int gWidth, gHeight, picked;
CUserInterface * userInterface;
vector <CModel *> models;
float rgb[3], mouseX,mouseY;

void pick() {
	double x, y;
	float color[3];
	glm::vec3 translation, scale;
	glm::vec4 rotation;

	//Limpio la pantalla:
	glClearColor(0.28f, 0.29f, 0.30f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Capturo la posición del mouse:
	glfwGetCursorPos(gWindow, &x, &y);
	x = float(x);
	y = gHeight - float(y);

	//Dibujo los modelos:
	for (unsigned int i = models.size(); i > 0; i--)
	{
		//Recupero transformaciones del modelo i:
		translation = models[i - 1]->getTranslation();
		scale = models[i - 1]->getScaling();
		rotation = models[i - 1]->getRotation();
		//Recupero matriz de modelo:
		glPushMatrix();
		//Transformaciones:
		glTranslatef(translation.x, translation.y, translation.z);
		glScalef(scale.x, scale.y, scale.z);
		rotate(rotation);
		//Dibujo el modelo:
		models[i - 1]->display(COLOR_PICK);
		//Capturo color del pixel donde ocurrió el click:
		glReadPixels((int)x, (int)y, 1, 1, GL_RGB, GL_FLOAT, &color);
		//Redondeo a 2 decimales:
		color[0] = roundf(color[0] * 100) / 100;

		if (equalColors(color, models[i - 1]->getPickColor())) {
			picked = i - 1;

				userInterface->setModelTranslation(models[picked]->getTranslation());
				userInterface->setModelScaling(models[picked]->getScaling());
				userInterface->setCurrentFile(models[picked]->getModelName());
				userInterface->setMeshColor(models[picked]->getMeshColor());
				userInterface->setFillColor(models[picked]->getFillColor());
				userInterface->setPointsColor(models[picked]->getPointsColor());
				userInterface->setMesh(models[picked]->getMesh());
				userInterface->setPoints(models[picked]->getPoints());
				userInterface->setFill(models[picked]->getFill());
				userInterface->setShadingType(models[picked]->getShadingType());
				userInterface->setAmbientColor(models[picked]->getAmbientColor());
				userInterface->setDiffuseColor(models[picked]->getDiffuseColor());
				userInterface->setSpecularColor(models[picked]->getSpecularColor());
			if (picked > 0) {
				userInterface->setShininess(models[picked]->getShininess());
				userInterface->setModelRotation(models[picked]->getRotation());
				userInterface->setBoundingBox(models[picked]->getBoundingBoxBool());
				userInterface->setBoundingBoxColor(models[picked]->getBoundingBoxColor());
				userInterface->setSideNormalBool(models[picked]->getSideNormalBool());
				userInterface->setVerticesNormalBool(models[picked]->getVerticesNormalBool());
				userInterface->setBFCulling(models[picked]->getBFCulling());
				userInterface->setZBuffer(models[picked]->getZBuffer());				
			}
			if (picked == 0 || picked == 1){
				userInterface->swapToLightMode();
				userInterface->setLightStatus(models[picked]->getLightStatus());
			}

			glPopMatrix();
			break;
		}
		glPopMatrix();
	}

}

void updateUserInterface()
{
	glm::vec3 updateScale = userInterface->getModelScaling();
	float scaleAll = userInterface->getScaleAll();
	updateScale.x += scaleAll;
	updateScale.y += scaleAll;
	updateScale.z += scaleAll;

	if (picked > -1){
		userInterface->setModelScaling(updateScale);
		models[picked]->setTranslation(userInterface->getModelTranslation());
		models[picked]->setScaling(userInterface->getModelScaling());
		models[picked]->setRotation(userInterface->getModelRotation());
		models[picked]->setBoundingBoxBool(userInterface->getBoundingBox());
		models[picked]->setBoundingBoxColor(userInterface->getBoundingBoxColor());
		models[picked]->setSideNormalsColor(userInterface->getSideNormalsColor());
		models[picked]->setVerticesNormalsColor(userInterface->getVerticesNormalsColor());
		models[picked]->setMeshColor(userInterface->getMeshColor());
		models[picked]->setFillColor(userInterface->getFillColor());
		models[picked]->setPointsColor(userInterface->getPointsColor());
		models[picked]->setMesh(userInterface->getMesh());
		models[picked]->setPoints(userInterface->getPoints());
		models[picked]->setFill(userInterface->getFill());
		models[picked]->setSideNormalBool(userInterface->getSideNormalBool());
		models[picked]->setVerticesNormalBool(userInterface->getVerticesNormalBool());
		models[picked]->setAmbientColor(userInterface->getAmbientColor());
		models[picked]->setDiffuseColor(userInterface->getDiffuseColor());
		models[picked]->setSpecularColor(userInterface->getSpecularColor());
		models[picked]->setBFCulling(userInterface->getBFCulling());
		models[picked]->setZBuffer(userInterface->getZBuffer());
		models[picked]->setShadingType(userInterface->getShadingType());
		models[picked]->setShininess(userInterface->getShininess());
	}
	if (picked == 0  || picked == 1) {
		updateLights();
		models[picked]->setLightStatus(userInterface->getLightStatus());
	}

}

void display()
{
	//Color picking:
	if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_LEFT) && picked == -1)
		pick();

	//Limpio la pantalla:
	glClearColor(0.28f, 0.29f, 0.30f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Display Luz 1:
	if (!models[0]->getLightStatus())
		glDisable(GL_LIGHT0);
	else 
		glEnable(GL_LIGHT0);

		models[0]->displayLight(GL_LIGHT0);
	//Display Luz 2:
	if (!models[1]->getLightStatus())
		glDisable(GL_LIGHT1);
	else
		glEnable(GL_LIGHT1);

		models[1]->displayLight(GL_LIGHT1);

	//Display modelos:
	glm::vec3 translation, scale;
	glm::vec4 rotation;
	for (unsigned int i = 2; i < models.size(); i++)
	{	
		glPushMatrix();
		//Se recuperan las transformaciones del modelo i:
		translation = models[i]->getTranslation();
		rotation = models[i]->getRotation();
		scale = models[i]->getScaling();
		//Se aplican las transformaciones:
		glTranslatef(translation.x, translation.y, translation.z);
		rotate(rotation);
		glScalef(scale.x, scale.y, scale.z);
		//Backface Culling:
		if (models[i]->getBFCulling()){
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else {
			glDisable(GL_CULL_FACE);
		}
		//Despliegue del modelo de acuerdo al método seleccionado:
		switch (userInterface->getCurrentDeploy()) {
		case GL_BEGIN_GL_END:
			if (models[i]->getFill())
				models[i]->display(GL_FILL);
			if (models[i]->getMesh())
				models[i]->display(GL_LINE);
			if (models[i]->getPoints())
				models[i]->display(GL_POINT);
			break;
		case DISPLAY_LIST:
			if (models[i]->getFill()) {
				models[i]->createList(GL_FILL);
				models[i]->displayList();
			}
			if (models[i]->getMesh()) {
				models[i]->createList(GL_LINE);
				models[i]->displayList();
			}
			if (models[i]->getPoints()) {
				models[i]->createList(GL_POINT);
				models[i]->displayList();
			}
			break;
		case VERTEX_POINTER:
			if (models[i]->getFill()) {
				models[i]->vertexPointer(GL_FILL);
			}
			if (models[i]->getMesh()) {
				models[i]->vertexPointer(GL_LINE);
			}
			if (models[i]->getPoints()) {
				models[i]->vertexPointer(GL_POINT);
			}
			break;
		case VBO:
			models[i]->displayVBO(); 
			
			break;	
		}
		glPopMatrix();
	}
		
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();
	if (!userInterface->getZBuffer())
		glDisable(GL_DEPTH_TEST);
	else
		glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (userInterface->getProjectionBool() == PERSPECTIVE)
		gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);
	else
		glOrtho(-10,10,-10,10,1,1000);

	glMatrixMode(GL_MODELVIEW);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;
	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && picked != -1){ 
		//cout << "Elemento "<<picked<<" deseleccionado" << endl;
		picked = -1;
		userInterface->swapToRegularMode();
		rebootInterface("None");
	}
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < models.size(); i++)
		delete models[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Proyecto II - Grafica. Frank Ponte V23950509", NULL, NULL);

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
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);
	glewInit();
	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

bool initScene()
{
	glm::vec3 translation;

	//Propiedades de luz 1:
	GLfloat light_position0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular0[] = { 0.22f, 1.0f, 0.02f, 1.0f };
	GLfloat light_ambient0[] = { 0.0F, 0.0F, 0.27F, 1.0F };
	translation.x = 4.49f; translation.y = 2.19f; translation.z = -1.95f;
	setLight("Luz 1", GL_LIGHT0, light_ambient0, light_diffuse0, light_specular0, light_position0,translation);
	//Propiedades de luz 2:
	GLfloat light_position1[] = { 0.0F, 0.0F, 0.0F, 1.0F };
	GLfloat light_diffuse1[] = { 0.59f, 0.15f, 0.62f, 1.0f };
	GLfloat light_specular1[] = { 1.0f, 0.16f , 0.77f, 1.0f };
	GLfloat light_ambient1[] = { 0.0F, 0.2F, 0.33F, 1.0F };
	translation.x = -2.42f; translation.y = -0.78f; translation.z = 4.75f;
	setLight("Luz 2", GL_LIGHT1, light_ambient1, light_diffuse1, light_specular1, light_position1,translation);

	//Inicializar interfaz:
	//rebootInterface("None");

	return true;
}

void setLight(string name, GLenum lightNumber, GLfloat* light_ambient, GLfloat* light_diffuse, GLfloat* light_specular, GLfloat* light_position,glm::vec3 t) {
	CObj* lightSphere = new CObj();

	//Iniciar luz:
	glLightfv(lightNumber, GL_AMBIENT, light_ambient);
	glLightfv(lightNumber, GL_DIFFUSE, light_diffuse);
	glLightfv(lightNumber, GL_SPECULAR, light_specular);
	glLightfv(lightNumber, GL_POSITION, light_position);
	glEnable(lightNumber);

	lightSphere->load("../files/sphere.obj");
	//Iniciar esfera que representa la luz:
	lightSphere->setAmbientColor(light_ambient);
	lightSphere->setDiffuseColor(light_diffuse);
	lightSphere->setSpecularColor(light_specular);
	lightSphere->setPickColor(rgb);
	lightSphere->setTranslation(t);
	lightSphere->setModelName(name);
	lightSphere->setNormals();
	lightSphere->setMesh(true);
	lightSphere->setFill(false);
	models.push_back(lightSphere);
	rgb[0] -= 0.01f;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	picked = -1;
	rgb[0] = 1.0f;
	rgb[1] = rgb[2] = 0.0f;

	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;
	initScene();

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	while (!glfwWindowShouldClose(gWindow))
	{
		reshape(gWindow, gWidth, gHeight);

		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}

void beginLoad(string path) {
	string aux = path;
	string extension = aux.erase(0, aux.find(".") + 1);
	string filename = getFileName(path);

	//Caso archivo OFF:
	if (extension == "off" || extension == "OFF" ){
		COff* coff = new COff();
		coff->setPickColor(rgb);
		if (!coff->load(path))
			return;
		coff->setModelName(filename);
		coff->setNormals();
		models.push_back(coff);
	}

	//Caso archivo OBJ:
	else if (extension == "obj" || extension == "OBJ"){
		CObj* cobj = new CObj();
		cobj->setPickColor(rgb);
		if (!cobj->load(path))
			return;
		cobj->setModelName(filename);
		cobj->setNormals();
		models.push_back(cobj);
	}

	//Valores iniciales para el nuevo modelo cargado:
	picked = models.size() - 1;
	rgb[0] -= 0.01f;
	rebootInterface(filename);

}

bool equalColors(float* rgb1, float* rgb2) {
	if (rgb1[0] != rgb2[0] || rgb1[1] != rgb2[1] || rgb1[2] != rgb2[2])
		return false;
	return true;
}

string getFileName(const string& s) {

	char sep = '/';

#ifdef _WIN32
	sep = '\\';
#endif

	size_t i = s.rfind(sep, s.length());
	if (i != string::npos) {
		return(s.substr(i + 1, s.length() - i));
	}

	return("");
}

void rotate(glm::vec4 rotation) {
	float matrix[4*4];

	float yy2 = 2.0f * rotation[1] * rotation[1];
	float xy2 = 2.0f * rotation[0] * rotation[1];
	float xz2 = 2.0f * rotation[0] * rotation[2];
	float yz2 = 2.0f * rotation[1] * rotation[2];
	float zz2 = 2.0f * rotation[2] * rotation[2];
	float wz2 = 2.0f * rotation[3] * rotation[2];
	float wy2 = 2.0f * rotation[3] * rotation[1];
	float wx2 = 2.0f * rotation[3] * rotation[0];
	float xx2 = 2.0f * rotation[0] * rotation[0];
	matrix[0 * 4 + 0] = -yy2 - zz2 + 1.0f;
	matrix[0 * 4 + 1] = xy2 + wz2;
	matrix[0 * 4 + 2] = xz2 - wy2;
	matrix[0 * 4 + 3] = 0;
	matrix[1 * 4 + 0] = xy2 - wz2;
	matrix[1 * 4 + 1] = -xx2 - zz2 + 1.0f;
	matrix[1 * 4 + 2] = yz2 + wx2;
	matrix[1 * 4 + 3] = 0;
	matrix[2 * 4 + 0] = xz2 + wy2;
	matrix[2 * 4 + 1] = yz2 - wx2;
	matrix[2 * 4 + 2] = -xx2 - yy2 + 1.0f;
	matrix[2 * 4 + 3] = 0;
	matrix[3 * 4 + 0] = matrix[3 * 4 + 1] = matrix[3 * 4 + 2] = 0;
	matrix[3 * 4 + 3] = 1;

	glMultMatrixf(matrix);
}

void rebootInterface(string filename) {
	glm::vec3 zero3;
	glm::vec4 zero4;
	float zerof[3];

	userInterface->setCurrentFile(filename);
	userInterface->setModelTranslation(zero3);
	zero3.x = zero3.y = zero3.z = 1.0f;
	userInterface->setModelScaling(zero3);
	userInterface->setModelRotation(zero4);
	userInterface->setScaleAll(0.0f);
	userInterface->setBoundingBox(false);

	zerof[0] = 0.0f; zerof[1] = 0.0f; zerof[2] = 0.0f;
	userInterface->setMeshColor(zerof);
	zerof[0] = 1.0f; zerof[1] = 0.0f; zerof[2] = 0.0f;
	userInterface->setFillColor(zerof);
	zerof[0] = 1.0f; zerof[1] = 1.0f; zerof[2] = 1.0f;
	userInterface->setPointsColor(zerof);
	zerof[0] = 1.0f; zerof[1] = 1.0f; zerof[2] = 0.0f;
	userInterface->setSideNormalsColor(zerof);
	zerof[0] = 0.0f; zerof[1] = 1.0f; zerof[2] = 1.0f;
	userInterface->setVerticesNormalsColor(zerof);
	zerof[0] = 0.0f; zerof[1] = 1.0f; zerof[2] = 0.0f;
	userInterface->setBoundingBoxColor(zerof);
	zerof[0] = 0.47f; zerof[1] = 0.42f; zerof[2] = 0.33f;
	userInterface->setAmbientColor(zerof);
	zerof[0] = 1.0f; zerof[1] = 1.0f; zerof[2] = 1.0f;
	userInterface->setDiffuseColor(zerof);
	zerof[0] = 1.0f; zerof[1] = 1.0f; zerof[2] = 0.0f;
	userInterface->setSpecularColor(zerof);

	userInterface->setMesh(false);
	userInterface->setPoints(false);
	userInterface->setFill(true);
	userInterface->setSideNormalBool(false);
	userInterface->setVerticesNormalBool(false);
	userInterface->setBFCulling(false);
	userInterface->setZBuffer(true);
	userInterface->setShadingType(FLAT);
	userInterface->setLightStatus(true);
	userInterface->setShininess(20.0f);

}

void updateLights() {
	float* light_diffuse = new float(4);
	float* light_specular = new float(4);
	float* light_ambient = new float(4);

	light_ambient = models[picked]->getAmbientColor();

	light_diffuse = models[picked]->getDiffuseColor();

	light_specular = models[picked]->getSpecularColor();

	switch (picked) {
	case 0:
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		break;
	case 1:
		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
		break;
	}

}