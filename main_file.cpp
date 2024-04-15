#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "camera.h"

void initOpenGLProgram(GLFWwindow* window)
{
    initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************	
}

void freeOpenGLProgram(GLFWwindow* window)
{
    freeShaders();
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************	
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


void drawScene(GLFWwindow* window, camera* sceneCamera)
{
	glm::mat4 M, V, P;

	M = glm::mat4(1.0f);
	V = sceneCamera->calculateView();
	P = sceneCamera->calculatePerspective();
}

int main(void)
{
	glm::vec2 resolution = glm::vec2(640, 640);
	float fov = glm::radians(70.0f);
	int swapInterval = 1;

	GLFWwindow* window = initWindow((int)resolution.x, (int)resolution.y, swapInterval);
	camera* sceneCamera = new camera(resolution, glm::vec3(), fov);

	while (!glfwWindowShouldClose(window))
	{		
		drawScene(window, sceneCamera);
		glfwPollEvents();
	}
	closeWindow(window);
}
