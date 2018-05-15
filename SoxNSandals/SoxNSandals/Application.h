#pragma once
#include "SoxCore.h"

class Application
{
public:
	Application(const glm::ivec2& a_resolution = glm::ivec2(1280, 720), const char* a_name = "Window");
	~Application();

	int run();

protected:

	int initialize();

	bool update(double deltaTime);

	void iterate();

	void render();

	int terminate();

	float deltaTime;

	GLFWwindow* window;
	sns::clock m_clock;
	
};

