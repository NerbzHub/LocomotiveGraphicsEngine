/**
	Camera.cpp

	Purpose: Camera.cpp is the source file for the Camera class.
			The Camera class is used to create a camera that allows the user
			to see what's in the scene.

	@author Nathan Nette
*/
#include "Camera.h"
#include <ext.hpp>

/**
	Constructor that initializes the variables to default values.
*/
Camera::Camera()
{
	// Assigning all of the variables to have default values.
	//	If it is a matrix, set it as an identity matrix.
	worldTransform = glm::mat4(1);
	viewTransform = glm::mat4(1);
	projectionTransform = glm::mat4(1);
	projectionViewTransform = glm::mat4(1);

	// Set the camera's look at to be 10, 10, 10 and looking at 0,0.
	setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	// Allocate a default value to the perspective.
	setPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

}

/**
	Default Deconstructor
*/
Camera::~Camera()
{
}

/**
	updateProjectionViewTransform creates the projectionViewTransform.
		this must be called any time there are any changes to the
		projectionViewTransform to recalculate it.
*/
void Camera::updateProjectionViewTransform()
{
	// Calculate the Projection View Matrix.
	projectionViewTransform = projectionTransform * viewTransform;
}

/**
	SetPerspective takes in all of the necessary values needed to calculate the perpective.
		It then uses these values and calculates the new perspective.

		@param1 fieldOfView is a float that changes the field of view of the application.

		@param2 aspectRatio is the aspect ratio of the window, e.g. 16:9, 4:3, 16:10.

		@param3 fnear is the near plane of the clip space.

		@param4 ffar is the far plane of the clip space.
*/
void Camera::setPerspective(const float &fieldOfView, const float &aspectRatio, const float &fnear, const float &ffar)
{
	// Calculate the projection transform.
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, fnear, ffar);

	// Update it so that the new version of it is applied.
	updateProjectionViewTransform();
}

/**
	setLookAt sets what the camera is looking at using multiple vec3s from, to and up.

		@param1 from is a vector 3 that stores where the camera will be located.

		@param2 to is the vec3 that the camera will be looking at.

		@param3 up is for the camera's up position.
*/
void Camera::setLookAt(const glm::vec3 &from, const glm::vec3 &to, const glm::vec3 &up)
{
	// Calculates the view transform.
	viewTransform = glm::lookAt(from, to, up);

	// The world transform is the inverse of the view transform.
	worldTransform = glm::inverse(viewTransform);

	// Update it to apply it to the scene.
	updateProjectionViewTransform();
}

/**
	setPos sets the position of the camera.

		@param1 position is a vec3 that becomes the camera's new position.
*/
void Camera::setPos(const glm::vec3 &position)
{
	// Set the position inside the camera's transform.
	worldTransform[3] = glm::vec4(position, worldTransform[3][3]);

	// Calculates the view transform which is the inverse of the world transform.
	viewTransform = glm::inverse(worldTransform);

	// Update it to apply it to the scene.
	updateProjectionViewTransform();
}

/**
	getWorldTransform returns the current world transform of the camera.

		@return worldTransform is the camera's current place in world space.
*/
glm::mat4 Camera::getWorldTransform() const
{
	return worldTransform;
}

/**
	getView returns the view transform of the camera.

		@return viewTransform of the camera.
*/
glm::mat4 Camera::getView() const
{
	return viewTransform;
}

/**
	getProjection returns the current projection transform of the camera.

		@return projectionTransform which is the current projection transform
			of camera.
*/
glm::mat4 Camera::getProjection() const
{
	return projectionTransform;
}

/**
	getProjectionView gets the current projectionView of the camera.

		@return projectionViewTransform is the current projection view
			transform of the camera.
*/
glm::mat4 Camera::getProjectionView() const
{
	return projectionViewTransform;
}

/**
	getPosition extracts the current position of the camera from the
		worldTransform then returns it.

	@return tempv3 is the position xyz of the camera.
*/
glm::vec3 Camera::getPosition() const
{
	// Create a temporary vec3.
	glm::vec3 tempv3;

	// Extract the position from the camera's world transform.
	tempv3.x = worldTransform[3].x;
	tempv3.y = worldTransform[3].y;
	tempv3.z = worldTransform[3].z;

	// return it as a vec3.
	return tempv3;
}
