#pragma once
#include "model.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stdlib.h>
#include <stdio.h>

class gameObject
{
public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f);
	const glm::quat DEFAULT_ROTATION = glm::quat(glm::vec3(0.0f));
	const glm::vec3 DEFAULT_SCALE = glm::vec3(1.0f);

	glm::mat4 calculatePosition();

	gameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	gameObject(glm::vec3 position, glm::quat rotation);
	gameObject(glm::vec3 position);
	gameObject();
};

