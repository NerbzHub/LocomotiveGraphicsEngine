/**
	main.cpp

		Purpose: main.cpp is the very first file that gets run when the 
				application is run. This file calls the application to 
				begin running.

	@author Nathan Nette
*/
#include <iostream>
#include <chrono>
#include "gl_core_4_5.h"
#include <glfw3.h>
#include <glm.hpp>
#include <ext.hpp>
#include "soxCore.h"
#include "Application.h"
#include <crtdbg.h>

/**
	main is the beginning and the end of the application.
		Every bit of the application is called through this
		function.
*/
int main()
{
	// Begin application with the resolution 1280, 720 and with the window name
	//	SoxNSandals
	auto app = new Application(glm::vec2(1280, 720), "SoxNSandals");

	// Call run inside the application class.
	app->run();

	// Once the game loop is broken, delete the application.
	delete app;

	// End the process.
	return 0;
}