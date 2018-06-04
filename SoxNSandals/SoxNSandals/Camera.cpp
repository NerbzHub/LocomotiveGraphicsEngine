#include "Camera.h"
#include <ext.hpp>


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

void Camera::setPerspective(const float &fieldOfView, const float &aspectRatio, const float &fnear, const float &ffar)
{
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, fnear, ffar);
	updateProjectionViewTransform();
}

void Camera::setLookAt(const glm::vec3 &from, const glm::vec3 &to, const glm::vec3 &up)
{
	viewTransform = glm::lookAt(from, to, up);
}

void Camera::setPos(const glm::vec3 &position)
{
	worldTransform[3] = glm::vec4(position, worldTransform[3][3]);
	updateProjectionViewTransform();
}

glm::mat4 Camera::getWorldTransform() const
{
	return worldTransform;
}

glm::mat4 Camera::getView() const
{
	return viewTransform;
}

glm::mat4 Camera::getProjection() const
{
	return projectionTransform;
}

glm::mat4 Camera::getProjectionView() const
{
	return projectionViewTransform;
}
