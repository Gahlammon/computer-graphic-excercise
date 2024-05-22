#include "gameObject.h"

glm::mat4 gameObject::calculatePosition()
{
	glm::mat4 M = glm::mat4(1.0f);

	M = glm::translate(M, position);
	M = M * glm::toMat4(rotation);
	M = glm::scale(M, scale);

	return M;
}

void gameObject::move(const glm::vec3& translation)
{
	position = position + translation;
	for (int i = 0; i < kids.size(); i++)
	{
		kids.at(i)->move(translation);
	}
}

void gameObject::rotate(const glm::quat& rotation)
{
	gameObject::rotation = rotation * gameObject::rotation;
	for (int i = 0; i < kids.size(); i++)
	{
		kids.at(i)->rotateAroundPoint(rotation, position);
	}
}

void gameObject::rotateAroundPoint(const glm::quat& rotation, const glm::vec3& point)
{
	move(((point - position) - (rotation * (point - position))));
	rotate(rotation);
}

void gameObject::resize(const glm::vec3& scale)
{
	gameObject::scale = gameObject::scale * scale;
	for (int i = 0; i < kids.size(); i++)
	{
		kids.at(i)->move((this->position - kids.at(i)->position) * (glm::vec3(1.0f, 1.0f, 1.0f) - scale));
		kids.at(i)->resize(scale);
	}
}

void gameObject::adopt(gameObject* child)
{
	kids.push_back(child);
}

void gameObject::getAdopted(gameObject* parent)
{
	parent->adopt(this);
}

gameObject::gameObject(Models::Model mesh, glm::vec3 position, glm::quat rotation, glm::vec3 scale) : mesh(mesh), position(position), rotation(rotation), scale(scale)
{
	kids = std::vector<gameObject*>();
}