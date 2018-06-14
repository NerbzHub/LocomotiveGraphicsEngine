#pragma once
#include "soxCore.h"
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

	// Initialise various shapes.
	void createQuad();
	void createCube();
	void createCylinder();


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
	FlyCamera* m_flyCam;
	Planet m_planet;

	//----------Shader----------
	aie::ShaderProgram m_shader;
	glm::mat4 m_quadTransform;

	//----------Mesh------------
	Mesh m_quadMesh;
	Mesh m_cubeMesh;
	Mesh m_circleMesh;
	Mesh m_cylinderMesh;


	//----------imgui-----------
	//ImGuiWindow* m_PanelGameObject;
	

	//----------OBJ-------------
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;

};

