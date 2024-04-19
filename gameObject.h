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

const glm::vec3 DEFAULT_GAME_OBJECT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::quat DEFAULT_GAME_OBJECT_ROTATION = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
const glm::vec3 DEFAULT_GAME_OBJECT_SCALE = glm::vec3(1.0f, 1.0f, 1.0f);

class gameObject
{
public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	glm::mat4 calculatePosition();

	gameObject(glm::vec3 position = DEFAULT_GAME_OBJECT_POSITION, glm::quat rotation = DEFAULT_GAME_OBJECT_ROTATION, glm::vec3 scale = DEFAULT_GAME_OBJECT_SCALE);
};

