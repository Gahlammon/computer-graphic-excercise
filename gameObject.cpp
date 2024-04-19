#include "gameObject.h"

glm::mat4 gameObject::calculatePosition()
{
	glm::mat4 M = glm::mat4(1.0f);

	M = glm::translate(M, position);
	M = M * glm::toMat4(rotation);
	//M = glm::rotate(M, 1.0f, glm::normalize(glm::eulerAngles(rotation));
	M = glm::scale(M, scale);

	return M;
}

void gameObject::move(glm::vec3 translation)
{
	position = position + translation;
}

void gameObject::rotate(glm::quat rotation)
{
	gameObject::rotation = rotation * gameObject::rotation;
}

void gameObject::resize(glm::vec3 scale)
{
	gameObject::scale = gameObject::scale * scale;
}

gameObject::gameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	gameObject::position = position;
	gameObject::rotation = rotation;
	gameObject::scale = scale;
}