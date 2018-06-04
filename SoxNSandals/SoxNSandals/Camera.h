#pragma once
#include "soxCore.h"

class Camera
{
public:
	Camera();
	~Camera();

	virtual void update(double deltaTime, GLFWwindow* a_glfwWindow) = 0;
	void setPerspective(const float &fieldOfView, const float &aspectRatio, const float &fnear, const float &ffar);
	void setLookAt(const glm::vec3 &from, const glm::vec3 &to, const glm::vec3 &up);
	void setPos(const glm::vec3 &position);
	glm::mat4 getWorldTransform() const;
	glm::mat4 getView() const;
	glm::mat4 getProjection() const;
	glm::mat4 getProjectionView() const;

protected:

	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;

	void updateProjectionViewTransform();

};