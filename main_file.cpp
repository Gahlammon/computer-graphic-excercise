#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <time.h>
#include <Windows.h>
#include <wtypes.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "camera.h"
#include "gameObject.h"

Models::Model temp;

void initOpenGLProgram(GLFWwindow* window)
{
    initShaders();
	glEnable(GL_DEPTH_TEST);
	spLambert->use();
	spConstant->use();
	glUniform4f(spLambert->u("color"), 1.0f, 1.0f, 1.0f, 1.0f);
}

void freeOpenGLProgram(GLFWwindow* window)
{
    freeShaders();
}

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void initGLFW()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		fprintf(stderr, "Unable to initiate GLFW\n");
		exit(EXIT_FAILURE);
	}
}

void initGLEWwindow(GLFWwindow* window, int swapInterval)
{
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Unable to initiate GLEW\n");
		exit(EXIT_FAILURE);
	}
	initOpenGLProgram(window);
}

GLFWwindow* initWindow(int x, int y, int swapInterval, bool fullscreen = false)
{
	initGLFW();
	ShowCursor(false);

	GLFWwindow* window = glfwCreateWindow(x, y, "OpenGL", fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Unable to create window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	initGLEWwindow(window, swapInterval);

	return window;
}

void closeWindow(GLFWwindow* window)
{
	freeOpenGLProgram(window);
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


void drawScene(GLFWwindow* window, camera* sceneCamera, std::vector<gameObject*>* sceneObjects, bool rendered = true)
{
	glm::mat4 M, V, P;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 255);

	P = sceneCamera->calculatePerspective();
	glUniformMatrix4fv(rendered ? spLambert->u("P") : spConstant->u("P"), 1, false, glm::value_ptr(P));
	V = sceneCamera->calculateView();
	glUniformMatrix4fv(rendered ? spLambert->u("V") : spConstant->u("V"), 1, false, glm::value_ptr(V));

	for (int i = 0; i < sceneObjects->size(); i++)
	{
		M = sceneObjects->at(i)->calculatePosition();
		glUniformMatrix4fv(rendered ? spLambert->u("M") : spConstant->u("M"), 1, false, glm::value_ptr(M));
		rendered ? temp.drawSolid() : temp.drawWire();
	}

	glfwSwapBuffers(window);
}

void inputHandling(camera* sceneCamera, float deltaTime)
{
	glm::vec3 movement = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);

	if (GetKeyState('W') & 0x8000)
	{
		movement.z += deltaTime;
	}
	if (GetKeyState('S') & 0x8000)
	{
		movement.z -= deltaTime;
	}
	if (GetKeyState('A') & 0x8000)
	{
		movement.x += deltaTime;
	}
	if (GetKeyState('D') & 0x8000)
	{
		movement.x -= deltaTime;
	}
	if (GetKeyState('I') & 0x8000)
	{
		rotation.x -= deltaTime;
	}
	if (GetKeyState('K') & 0x8000)
	{
		rotation.x += deltaTime;
	}
	if (GetKeyState('J') & 0x8000)
	{
		rotation.y -= deltaTime;
	}
	if (GetKeyState('L') & 0x8000)
	{
		rotation.y += deltaTime;
	}

	sceneCamera->move(5.0f * movement * sceneCamera->rotation);
	sceneCamera->rotate(rotation);
}

int main(void)
{
	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	Models::Model mesh = Models::Model();

	temp.meshImport("assets/test.obj");

	glm::vec2 resolution = glm::vec2(desktop.right, desktop.bottom);
	float fov = glm::radians(70.0f);
	int swapInterval = 1;
	bool viewmodeRendered = true;
	bool keyPressed = false;

	GLFWwindow* window = initWindow(resolution.x, resolution.y, swapInterval, true);
	camera* sceneCamera = new camera(resolution, fov, glm::vec3());
	std::vector<gameObject*>* objects = new std::vector<gameObject*>();

	objects->push_back(new gameObject(glm::vec3(5.0f, 5.0f, 5.0f)));
	objects->push_back(new gameObject(glm::vec3(5.0f, 9.0f, 5.0f)));
	objects->at(0)->adopt(objects->at(1));
	objects->push_back(new gameObject(glm::vec3(3.0f, 5.0f, 5.0f), glm::quat(glm::vec3(45.0f, 0.0f, 90.0f)), glm::vec3(2.5f, 1.0f, 0.5f)));
	objects->push_back(new gameObject(glm::vec3(0.0f, -5.0f, 0.0f)));
	for (int i = 4; i < 4 + 18; i++)
	{
		objects->push_back(new gameObject(glm::vec3(10.0f, -5.0f, 0.0f)));
		objects->at(i)->rotateAroundPoint(glm::quat(glm::vec3(0.0f, glm::radians(20.0f * (i - 4)), 0.0f)), glm::vec3(0.0f, -5.0f, 0.0f));
		objects->at(3)->adopt(objects->at(i));
	}
	sceneCamera->lookAt(objects->at(0)->position);

	viewmodeRendered ? spLambert->use() : spConstant->use();

	clock_t sceneClock = clock();
	float deltaTime = 0.0f;
	while (!glfwWindowShouldClose(window) && !(GetKeyState('Q') & 0x8000))
	{
		deltaTime = float(clock() - sceneClock) / CLOCKS_PER_SEC;
		sceneClock = clock();

		inputHandling(sceneCamera, deltaTime);
		if ((GetKeyState('Z') & 0x8000) && !keyPressed)
		{
			viewmodeRendered = !viewmodeRendered;
			viewmodeRendered ? spLambert->use() : spConstant->use();
		}
		if ((!(GetKeyState('Z') & 0x8000) && keyPressed) || ((GetKeyState('Z') & 0x8000) && !keyPressed)) { keyPressed = !keyPressed; }

		objects->at(0)->move(glm::vec3(1.0f * deltaTime, 0.0f, 0.0f));
		objects->at(3)->rotate(glm::vec3(0.0f, 2.0f, 0.0f) * deltaTime);

		drawScene(window, sceneCamera, objects, viewmodeRendered);
		glfwPollEvents();
	}
	closeWindow(window);
}
