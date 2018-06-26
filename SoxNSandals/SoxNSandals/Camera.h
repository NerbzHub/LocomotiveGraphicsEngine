/**
	Camera.h

	Purpose: Camera.h is the header file for the Camera class.
			The Camera class is used to create a camera that allows the user
			to see what's in the scene. 

	@author Nathan Nette
*/
#pragma once
#include "soxCore.h"

/**
	The Camera class allows creation of a camera for the scene.
		It allows you to set position, the direction of what it's looking at,
		set the perspective.
*/
class Camera
{
public:
	/**
		Default Constructor
	*/
	Camera();
	/**
		Default Deconstructor
	*/
	~Camera();

	/**
		Update runs every frame. Anything that needs to be run every frame
			must be stored in here.

			@param1 deltaTime is a double that the current frame rate.

			@param2 a_glfwWindow is a pointer to get the memory address of the application's
				window.
	*/
	virtual void update(double deltaTime, GLFWwindow* a_glfwWindow) = 0;

	/**
		SetPerspective takes in all of the necessary values needed to calculate the perpective.
			It then uses these values and calculates the new perspective.

			@param1 fieldOfView is a float that changes the field of view of the application.

			@param2 aspectRatio is the aspect ratio of the window, e.g. 16:9, 4:3, 16:10.

			@param3 fnear is the near plane of the clip space.

			@param4 ffar is the far plane of the clip space.
	*/
	void setPerspective(const float &fieldOfView, const float &aspectRatio, const float &fnear, const float &ffar);

	/**
		setLookAt sets what the camera is looking at using multiple vec3s from, to and up.

			@param1 from is a vector 3 that stores where the camera will be located.

			@param2 to is the vec3 that the camera will be looking at.

			@param3 up is for the camera's up position.
	*/
	void setLookAt(const glm::vec3 &from, const glm::vec3 &to, const glm::vec3 &up);

	/**
		setPos sets the position of the camera.

			@param1 position is a vec3 that becomes the camera's new position.
	*/
	void setPos(const glm::vec3 &position);

	/**
		getWorldTransform returns the current world transform of the camera.

			@return worldTransform is the camera's current place in world space.
	*/
	glm::mat4 getWorldTransform() const;

	/**
		getView returns the view transform of the camera.

			@return viewTransform of the camera.
	*/
	glm::mat4 getView() const;

	/**
		getProjection returns the current projection transform of the camera.

			@return projectionTransform which is the current projection transform
					of camera.
	*/
	glm::mat4 getProjection() const;

	/**
		getProjectionView gets the current projectionView of the camera.

			@return projectionViewTransform is the current projection view 
				transform of the camera.
	*/
	glm::mat4 getProjectionView() const;

	/**
		getPosition extracts the current position of the camera from the 
			worldTransform then returns it.

			@return tempv3 is the position xyz of the camera.
	*/
	glm::vec3 getPosition() const;

protected:

	/**
		updateProjectionViewTransform creates the projectionViewTransform.
			this must be called any time there are any changes to the 
			projectionViewTransform to recalculate it.
	*/
	void updateProjectionViewTransform();

	// The transform of the camera in world space.
	glm::mat4 worldTransform;

	// The view transform of the camera.
	glm::mat4 viewTransform;

	// The projectionTransform of the camera.
	glm::mat4 projectionTransform;

	// The projectionViewTransform of the camera.
	glm::mat4 projectionViewTransform;


};