#include "gameObject.h"

glm::mat4 gameObject::calculatePosition()
{
	glm::mat4 M = glm::mat4(1.0f);

	M = glm::toMat4(rotation);
	M = glm::scale(M, scale);
	M = glm::translate(M, position);

	return M;
}

gameObject::gameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	gameObject::position = position;
	gameObject::rotation = rotation;
	gameObject::scale = scale;
}