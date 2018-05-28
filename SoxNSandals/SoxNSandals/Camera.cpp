#include "Camera.h"



Camera::Camera()
{

	worldTransform = glm::mat4(0);
	viewTransform = glm::mat4(0);
	projectionTransform = glm::mat4(0);
	projectionViewTransform = glm::mat4(0);

	setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));

	setPerspective(glm::pi<float>() * 0.025f, 16.0f / 9.0f, 0.1f, 1000.0f);

}


Camera::~Camera()
{
}

void Camera::updateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform;
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float nearDepth, float farDepth)
{
	projectionViewTransform = glm::perspective(fieldOfView, aspectRatio, nearDepth, farDepth);
	updateProjectionViewTransform();
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	viewTransform = glm::lookAt(from, to, up);
}

void Camera::setPosition(glm::vec3 position)
{
	worldTransform[3] = glm::vec4(position, worldTransform[3][3]);
	updateProjectionViewTransform();
}

glm::mat4 Camera::getWorldTransform()
{
	return glm::mat4();
}

glm::mat4 Camera::getView()
{
	return glm::mat4();
}

glm::mat4 Camera::getProjection()
{
	return glm::mat4();
}

glm::mat4 Camera::getProjectionView()
{
	return glm::mat4();
}

