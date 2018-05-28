#pragma once
#include "SoxCore.h"
#include "Planet.h"
#include "FlyCamera.h"

class FlyCamera;

class Application
{
public:
	Application(const glm::ivec2& a_resolution, const char* a_name);
	~Application();

	int run();

protected:

	int initialize();

	bool update(double deltaTime);

	void iterate();

	void render();

	int terminate();

	double m_deltaTime;


	glm::ivec2 m_windowResolution;
	const char* m_windowName;
	GLFWmonitor** screens;
	int screenCount = 0;
	GLFWwindow* window;
	sns::clock m_clock;
	sns::time m_startTime;
	sns::time m_currentTime;
	sns::time m_previousTime;
	glm::mat4 view;
	glm::mat4 projection;
	FlyCamera m_flyCam;
	Planet m_planet;

	//----------imgui-----------
	//ImGuiWindow* m_PanelGameObject;

};

