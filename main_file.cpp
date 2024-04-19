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
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "camera.h"
#include "gameObject.h"

void initOpenGLProgram(GLFWwindow* window)
{
    initShaders();
	spConstant->use();
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

GLFWwindow* initWindow(int x, int y, int swapInterval)
{
	initGLFW();
	//ShowCursor(false);
	
	GLFWwindow* window = glfwCreateWindow(x, y, "OpenGL", NULL, NULL);
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


void drawScene(GLFWwindow* window, camera* sceneCamera, std::vector<gameObject>* sceneObjects)
{
	glm::mat4 M, V, P;

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 255);

	P = sceneCamera->calculatePerspective();
	glUniformMatrix4fv(spConstant->u("P"), 1, false, glm::value_ptr(P));
	V = sceneCamera->calculateView();
	glUniformMatrix4fv(spConstant->u("V"), 1, false, glm::value_ptr(V));

	for (int i = 0; i < sceneObjects->size(); i++)
	{
		M = sceneObjects->at(i).calculatePosition();
		glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));
		Models::cube.drawWire();
	}

	glfwSwapBuffers(window);
}

void inputHandling(camera* sceneCamera, float deltaTime)
{
	glm::vec3 movement = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3();

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
		rotation.y += deltaTime;
	}
	if (GetKeyState('L') & 0x8000)
	{
		rotation.y -= deltaTime;
	}

	sceneCamera->move(movement * sceneCamera->rotation);
	sceneCamera->rotate(rotation);
}

int main(void)
{
	glm::vec2 resolution = glm::vec2(640, 640);
	float fov = glm::radians(70.0f);
	int swapInterval = 1;

	GLFWwindow* window = initWindow((int)resolution.x, (int)resolution.y, swapInterval);
	camera* sceneCamera = new camera(resolution, fov, glm::vec3());
	std::vector<gameObject>* objects = new std::vector<gameObject>();

	objects->push_back(gameObject(glm::vec3(5.0f, 5.0f, 5.0f)));
	objects->push_back(gameObject(glm::vec3(3.0f, 5.0f, 5.0f)));
	objects->push_back(gameObject(glm::vec3(3.0f, 3.0f, 5.0f)));
	sceneCamera->lookAt(objects->at(0).position);

	clock_t sceneClock = clock();
	float deltaTime = 0.0f;
	while (!glfwWindowShouldClose(window) && !(GetKeyState('Q') & 0x8000))
	{
		deltaTime = float(clock() - sceneClock) / CLOCKS_PER_SEC;
		sceneClock = clock();

		inputHandling(sceneCamera, deltaTime);

		//sceneCamera->lookAt(objects->at(0).position);
		drawScene(window, sceneCamera, objects);
		glfwPollEvents();
	}
	closeWindow(window);
}
