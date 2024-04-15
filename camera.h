#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stdlib.h>
#include <stdio.h>

class camera
{
public:

	glm::vec2 resolution;
	glm::vec3 position;
	glm::quat rotation;
	float fov;
	float clippingNear;
	float clippingFar;

	const float DEFAULT_CLIPPING_NEAR = 0.1;
	const float DEFAULT_CLIPPING_FAR = 1000;
	const glm::quat DEFAULT_ROTATION = glm::quat();

	glm::mat4 calculateView();
	glm::mat4 calculatePerspective();

	camera(glm::vec2 resolution, glm::vec3 position, glm::quat rotation, float fov, float clippingNear, float clippingFar);
	camera(glm::vec2 resolution, glm::vec3 position, glm::quat rotation, float fov);
	camera(glm::vec2 resolution, glm::vec3 position, float fov);
};

