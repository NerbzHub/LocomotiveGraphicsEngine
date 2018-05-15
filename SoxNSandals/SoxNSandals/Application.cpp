#include "Application.h"



Application::Application(const glm::ivec2& a_resolution = glm::ivec2(1280, 720), const char* a_name = "Window")
{
	window = glfwCreateWindow(a_resolution.x, a_resolution.y, a_name, nullptr, nullptr);
}

Application::~Application()
{

}

int Application::run()
{
	return 0;
}

int Application::initialize()
{
	//sns::clock m_clock;
	sns::time m_startTime = m_clock.now();
	sns::time m_currentTime = m_clock.now();
	sns::time m_previousTime = m_clock.now();

	//parentMatrix[3] = glm::vec4(0, 0, 10, 1);
	//localMatrix[3] = glm::vec4(1, 0, -2, 1);


	glm::mat4 rot(1);
	rot = glm::rotate(0.0f, glm::vec3(0, 1, 0));

	//globalMatrix = parentMatrix * localMatrix;

	// if we can hook into the gpu.
	if (glfwInit() == false)
	{
		// -1 is a failure code.
		return -1;
	}

	GLFWmonitor** screens;
	int count = 0;
	screens = glfwGetMonitors(&count);
	std::cout << count << std::endl;

	// Window x and y, name of window, which screen it's on, shared or exclusive
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}


	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}


	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	//Clears screen to grey.
	glClearColor(0.25f, 0.25f, 0.25, 1);

	//enables depth buffer.
	glEnable(GL_DEPTH_TEST);


	aie::Gizmos::create(10000, 10000, 10000, 10000);

	// my camera is located at 10, 10, 10 and looking at the world's 0.
	glm::mat4 view = glm::lookAt(glm::vec3(15, 15, 15), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,
		16 / 9.f, 0.1f, 1000.f);



	return 0;
}

bool Application::update(double deltaTime)
{
	return false;
}

void Application::iterate()
{
}

void Application::render()
{
}

int Application::terminate()
{
	aie::Gizmos::destroy();

	glfwDestroyWindow(window);
	//Clean up window and gpu linkage.
	glfwTerminate();
	return 0;
}
