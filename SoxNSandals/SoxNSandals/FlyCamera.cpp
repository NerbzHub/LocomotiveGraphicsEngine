#include "FlyCamera.h"

FlyCamera::FlyCamera()
{
	// assigning some default values

	m_dMouseX = 0.0f;
	m_dMouseY = 0.0f;

	deltaMouseX = 0.0f;
	deltaMouseY = 0.0f;

	

	fMouseSensitivity = 2.5f;

	fMoveSpeed = 50.0f;
	fSprintSpeed = 150.0f;
}

FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(double deltaTime, GLFWwindow* a_GLWindow)
{
	// calculate the mouse's delta x and y
	glfwGetCursorPos(a_GLWindow, &m_dMouseX, &m_dMouseY);

	// calculate relative world up
	glm::vec4 up = glm::inverse(worldTransform) * glm::vec4(0, 1, 0, 0);
	glm::mat4 rotMat(1);

	// if deltaMouseX is 0, when glm rotate is used, rotMat results in NaN which breaks the app
	if (-deltaMouseX != 0.0f)
	{
		// rotate around the world's up
		rotMat = glm::rotate((float(-deltaMouseX) * fMouseSensitivity)* float(deltaTime), glm::vec3(up[0], up[1], up[2]));
		viewTransform = rotMat * viewTransform;
	}

	// rotate up and down
	rotMat = glm::rotate((float(-deltaMouseY) * fMouseSensitivity)* float(deltaTime), glm::vec3(1, 0, 0));
	viewTransform = rotMat * viewTransform;

	// radians to degrees
	deltaMouseX = ((1280 / 2 - m_dMouseX) * 0.0174533);
	deltaMouseY = ((720 / 2 - m_dMouseY) * 0.0174533);

	// keep mouse locked to screen
	glfwSetCursorPos(a_GLWindow, 1280 / 2, 720 / 2);

	// hide the mouse
	glfwSetInputMode(a_GLWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//std::cout << -deltaMouseX << std::endl;
	//std::cout << -deltaMouseY << std::endl;

	//update world transform
	worldTransform = glm::inverse(viewTransform);

	// keyboard input

	// move fowards, on the camera's z axis
	if (glfwGetKey(a_GLWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[2] * deltaTime * -fCurrentSpeed;
	}

	// move backwards, on the camera's z axis
	if (glfwGetKey(a_GLWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[2] * deltaTime * fCurrentSpeed;
	}

	// strafe left
	if (glfwGetKey(a_GLWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[0] * deltaTime * -fCurrentSpeed;
	}

	// strafe right
	if (glfwGetKey(a_GLWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[0] * deltaTime * fCurrentSpeed;
	}

	// Hold shift to go 3 times as fast(similar to sprint in games)
	if (glfwGetKey(a_GLWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		fCurrentSpeed = fSprintSpeed;
	}
	else
	{
		fCurrentSpeed = fMoveSpeed;
	}

	// debug set pos to centre of world 
	if (glfwGetKey(a_GLWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		setPos(glm::vec3(0, 0, 0));
	}


	// making sure that the forward matrix is maintained
	worldTransform[3][3] = 1.0f;

	// update the view transform then the projection view
	viewTransform = glm::inverse(worldTransform);
	updateProjectionViewTransform();
}