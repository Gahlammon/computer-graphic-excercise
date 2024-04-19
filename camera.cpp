#include "camera.h"

glm::mat4 camera::calculateView()
{
	glm::mat4 V = glm::toMat4(rotation);
	V = glm::translate(V, position);

	return V;
}

glm::mat4 camera::calculatePerspective()
{
	float aspect = resolution.x / resolution.y;
	if (aspect < 1 && aspect != 0) {
		aspect = 1 / aspect;
	}

	glm::mat4 P = glm::perspective(fov, aspect, clippingNear, clippingFar);

	return P;
}

void camera::lookAt(glm::vec3 point, glm::vec3 upward)
{
	rotation = glm::quat(glm::lookAt(position, point, upward));
}

void camera::move(glm::vec3 vector)
{
	position = position + vector;
}

void camera::rotate(glm::quat rotation)
{
	camera::rotation = rotation * camera::rotation;
}

camera::camera(glm::vec2 resolution, float fov, glm::vec3 position, glm::quat rotation, float clippingNear, float clippingFar)
{
	camera::resolution = resolution;
	camera::fov = fov;
	camera::position = position;
	camera::rotation = rotation;
	camera::clippingNear = clippingNear;
	camera::clippingFar = clippingFar;
}
