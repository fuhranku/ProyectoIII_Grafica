#include "../headers/GL/glew.h"
#define GLFW_INCLUDE_GLU
#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"

#include <vector>


using std::string;

void updateUserInterface();

void display();


void reshape(GLFWwindow *window, int width, int height);

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

void mouseButton(GLFWwindow* window, int button, int action, int mods);

void cursorPos(GLFWwindow* window, double x, double y);

void charInput(GLFWwindow* window, unsigned int scanChar);

void destroy();

bool initGlfw();

bool initUserInterface();

int main(void);

void beginLoad(string path);

void pick();

bool equalColors(float* rgb1, float* rgb2);

string getFileName(const string& s);

void rotate(glm::vec4 rotation);

void rebootInterface(string filename);


void setLight(string name, GLenum lightNumber, GLfloat* light_ambient, GLfloat* light_diffuse, GLfloat* light_specular, GLfloat* light_position, glm::vec3 t);

void updateLights();