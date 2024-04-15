#include "camera.h"

glm::mat4 camera::calculateView()
{
	glm::mat4 V = glm::toMat4(rotation);

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

camera::camera(glm::vec2 resolution, glm::vec3 position, glm::quat rotation, float fov, float clippingNear, float clippingFar)
{
	camera::resolution = resolution;
	camera::position = position;
	camera::rotation = rotation;
	camera::fov = fov;
	camera::clippingNear = clippingNear;
	camera::clippingFar = clippingFar;
}
camera::camera(glm::vec2 resolution, glm::vec3 position, glm::quat rotation, float fov)
{
	camera(resolution, position, rotation, fov, DEFAULT_CLIPPING_NEAR, DEFAULT_CLIPPING_FAR);
}
camera::camera(glm::vec2 resolution, glm::vec3 position, float fov)
{
	camera(resolution, position, DEFAULT_ROTATION, fov, DEFAULT_CLIPPING_NEAR, DEFAULT_CLIPPING_FAR);
}
