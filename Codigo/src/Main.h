#define GLFW_INCLUDE_GLU
#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void updateUserInterface();

void getMatriz4x4(glm::vec4, float*);

void render();

void initHelpers();

void initLights();

void initSounds();

void initObjs();

void reshape(GLFWwindow *window, int width, int height);

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

void destroy();

bool initGlfw();

bool initUserInterface();

int main(void);
