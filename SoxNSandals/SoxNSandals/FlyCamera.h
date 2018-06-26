/**
	FlyCamera.h

	Purpose: FlyCamera.h is the header file for the class FlyCamera.
			The FlyCamera class creates a camera that allows the user
			to fly around the scene using WASD for movement and Mouse 
			to look around. It inherits from the Camera class. The
			main functionality is from the camera class. This file 
			controls the input and movement.

@author Nathan Nette
*/
#pragma once
#include "soxCore.h"
#include "Camera.h"

/**
	The FlyCamera class inherits from Camera. The majority of the code
		in this class is input and movement so that the camera can fly around.
*/
class FlyCamera : public Camera
{
public:
	/**
		The constructor of FlyCamera just assigns default values 
			for mouse input and movement speed values.
	*/
	FlyCamera();

	/**
		Default Deconstructor.
	*/
	~FlyCamera();

	/**
		update runs every frame. All keyboard and mouse input must
			be in here, as it must be checked for every frame.
			Any movement values must be edited in here as well.

			@param1 deltaTime is the current frame rate.

			@param2 a_GLWindow is a pointer to get the address of 
					the application's window.
	*/
	void update(double deltaTime, GLFWwindow * a_GLWindow);

	// A double to store the mouse's X value.
	double m_dMouseX;

	// A double to store the mouse's Y value.
	double m_dMouseY;

	// A double to store the mouse's X value in screen space.
	double deltaMouseX;
	// A double to store the mouse's Y value in screen space.
	double deltaMouseY;

	// A float that is the sensitivity of the mouse.
	float fMouseSensitivity;

	// How fast the camera can move in world space.
	float fMoveSpeed;

	// How fast the camera moves while sprinting.
	float fSprintSpeed;

	// How fast the camera is currently going.
	float fCurrentSpeed;
};

