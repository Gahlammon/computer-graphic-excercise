#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stdlib.h>
#include <stdio.h>

const float DEFAULT_CLIPPING_NEAR = 0.1;
const float DEFAULT_CLIPPING_FAR = 1000;
const glm::quat DEFAULT_CAMERA_ROTATION = glm::quat();
const glm::vec3 DEFAULT_CAMERA_UPWARD_VECTOR = glm::vec3(0.0f, 1.0f, 0.0f);

class camera
{
public:

	glm::vec2 resolution;
	glm::vec3 position;
	glm::quat rotation;
	float fov;
	float clippingNear;
	float clippingFar;

	glm::mat4 calculateView();
	glm::mat4 calculatePerspective();
	void lookAt(glm::vec3 point, glm::vec3 upward = DEFAULT_CAMERA_UPWARD_VECTOR);

	camera(glm::vec2 resolution, float fov, glm::vec3 position, glm::quat rotation = DEFAULT_CAMERA_ROTATION, float clippingNear = DEFAULT_CLIPPING_NEAR, float clippingFar = DEFAULT_CLIPPING_FAR);
};

