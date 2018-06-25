#include <iostream>
#include <chrono>
#include "gl_core_4_5.h"
#include <glfw3.h>
#include "Gizmos.h"
#include <glm.hpp>
#include <ext.hpp>
#include "soxCore.h"
#include "Application.h"
#include <crtdbg.h>

int main()
{
	//At start of main()
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto app = new Application(glm::vec2(1280, 720), "Sox");

	app->run();

	delete app;

	return 0;
}