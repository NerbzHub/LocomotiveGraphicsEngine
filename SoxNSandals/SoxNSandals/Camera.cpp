#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::CreateCamera(glm::mat4 view, glm::mat4 projection)
{
	//my camera is located at 10, 10, 10 and looking at the world's 0.
	/*glm::mat4*/ view = glm::lookAt(glm::vec3(15, 15, 15), glm::vec3(0), glm::vec3(0, 1, 0));
	/*glm::mat4*/ projection = glm::perspective(glm::pi<float>() * 0.25f,
		16 / 9.f, 0.1f, 1000.f);
}

bool Camera::Update(float deltaTime)
{
	return false;
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float nearDepth, float farDepth)
{
	projectionViewTransform = glm::perspective(fieldOfView, aspectRatio, nearDepth, farDepth);
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{

}

void Camera::setPosition(glm::vec3 position)
{

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

void Camera::updateProjectionViewTransform()
{
}
