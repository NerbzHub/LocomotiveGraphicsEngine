/**
	FlyCamera.cpp

	Purpose: FlyCamera.cpp is the source file for the class FlyCamera.
		The FlyCamera class creates a camera that allows the user
		to fly around the scene using WASD for movement and Mouse
		to look around. It inherits from the Camera class. The
		main functionality is from the camera class. This file
		controls the input and movement.

	@author Nathan Nette
*/
#include "FlyCamera.h"

/**
	The constructor of FlyCamera just assigns default values
		for mouse input and movement speed values.
*/
FlyCamera::FlyCamera()
{
	// Assigning some default values.
	m_dMouseX = 0.0f;
	m_dMouseY = 0.0f;

	deltaMouseX = 0.0f;
	deltaMouseY = 0.0f;

	fMouseSensitivity = 2.5f;

	fMoveSpeed = 50.0f;
	fSprintSpeed = 150.0f;
}

/**
	Default Deconstructor.
*/
FlyCamera::~FlyCamera()
{
}

/**
	update runs every frame. All keyboard and mouse input must
		be in here, as it must be checked for every frame.
		Any movement values must be edited in here as well.

		@param1 deltaTime is the current frame rate.

		@param2 a_GLWindow is a pointer to get the address of
				the application's window.
*/
void FlyCamera::update(double deltaTime, GLFWwindow* a_GLWindow)
{
	// Calculate the mouse's delta x and y.
	glfwGetCursorPos(a_GLWindow, &m_dMouseX, &m_dMouseY);

	// Calculate relative world up.
	glm::vec4 up = glm::inverse(worldTransform) * glm::vec4(0, 1, 0, 0);
	glm::mat4 rotMat(1);

	// If deltaMouseX is 0, when glm rotate is used, rotMat results in NaN which breaks the application.
	if (-deltaMouseX != 0.0f)
	{
		// Rotate around the world's up.
		rotMat = glm::rotate((float(-deltaMouseX) * fMouseSensitivity)* float(deltaTime), glm::vec3(up[0], up[1], up[2]));
		viewTransform = rotMat * viewTransform;
	}

	// Rotate up and down.
	rotMat = glm::rotate((float(-deltaMouseY) * fMouseSensitivity)* float(deltaTime), glm::vec3(1, 0, 0));
	viewTransform = rotMat * viewTransform;

	// Radians to degrees.
	deltaMouseX = ((1280 / 2 - m_dMouseX) * 0.0174533);
	deltaMouseY = ((720 / 2 - m_dMouseY) * 0.0174533);

	// Keep mouse locked to screen.
	glfwSetCursorPos(a_GLWindow, 1280 / 2, 720 / 2);

	// Hide the mouse.
	glfwSetInputMode(a_GLWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Update world transform.
	worldTransform = glm::inverse(viewTransform);

	//-----------------Keyboard input-----------------------------
	// Move fowards, on the camera's z axis.
	if (glfwGetKey(a_GLWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[2] * deltaTime * -fCurrentSpeed;
	}

	// Move backwards, on the camera's z axis.
	if (glfwGetKey(a_GLWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[2] * deltaTime * fCurrentSpeed;
	}

	// Strafe left.
	if (glfwGetKey(a_GLWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[0] * deltaTime * -fCurrentSpeed;
	}

	// Strafe right.
	if (glfwGetKey(a_GLWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[0] * deltaTime * fCurrentSpeed;
	}

	// Hold shift to go 3 times as fast(similar to sprint in games).
	if (glfwGetKey(a_GLWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		fCurrentSpeed = fSprintSpeed;
	}
	else
	{
		fCurrentSpeed = fMoveSpeed;
	}

	// Debug set pos to centre of world.
	if (glfwGetKey(a_GLWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		setPos(glm::vec3(0, 0, 0));
	}

	//------------------------------------------------------------

	// Making sure that the forward matrix is maintained.
	worldTransform[3][3] = 1.0f;

	// Update the view transform then the projection view.
	viewTransform = glm::inverse(worldTransform);
	updateProjectionViewTransform();
}