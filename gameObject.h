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
#include <memory>

const glm::vec3 DEFAULT_GAME_OBJECT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::quat DEFAULT_GAME_OBJECT_ROTATION = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
const glm::vec3 DEFAULT_GAME_OBJECT_SCALE = glm::vec3(1.0f, 1.0f, 1.0f);
const Models::Model DEFAULT_GAME_OBJECT_MODEL = Models::Model();

class gameObject
{
public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
	std::vector<gameObject*> kids;
	Models::Model mesh;

	glm::mat4 calculatePosition();

	void move(const glm::vec3& translation);
	void rotate(const glm::quat& rotation);
	void resize(const glm::vec3& scale);
	void rotateAroundPoint(const glm::quat& rotation, const glm::vec3& point);
	void adopt(gameObject* child);
	void getAdopted(gameObject* parent);

	gameObject(Models::Model mesh = DEFAULT_GAME_OBJECT_MODEL, glm::vec3 position = DEFAULT_GAME_OBJECT_POSITION, glm::quat rotation = DEFAULT_GAME_OBJECT_ROTATION, glm::vec3 scale = DEFAULT_GAME_OBJECT_SCALE);
};

