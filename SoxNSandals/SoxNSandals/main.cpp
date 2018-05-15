#include <iostream>
#include <chrono>
#include "gl_core_4_5.h"
#include <glfw3.h>
#include "Gizmos.h"
#include <glm.hpp>
#include <ext.hpp>

/* TIME, Clock, AND DURATION ALIASING*/
using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;
// Expected use: seconds = nanoseconds * NANO_TO_SECONDS
static const double NANO_TO_SECONDS = 0.000000001;
// Expected use: nanoseconds = seconds * NANO_TO_SECONDS
static const ullong NANO_IN_SECONDS = 1000000000ULL;

namespace sns
{

	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;
}

//Parent
glm::mat4 parentMatrix(1);

//Child object
glm::mat4 localMatrix(1);
glm::mat4 globalMatrix(1);


int main()
{
	sns::clock m_clock;
	sns::time m_startTime = m_clock.now();
	sns::time m_currentTime = m_clock.now();
	sns::time m_previousTime = m_clock.now();

	parentMatrix[3] = glm::vec4(0, 0, 10, 1);
	localMatrix[3] = glm::vec4(1, 0, -2, 1);


	glm::mat4 rot(1);
	rot = glm::rotate(0.0f, glm::vec3(0, 1, 0));

	globalMatrix = parentMatrix * localMatrix;

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



	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		m_previousTime = m_currentTime;
		m_currentTime = m_clock.now();

		auto duration = m_currentTime - m_previousTime;

		float deltaTime = duration.count() * NANO_TO_SECONDS;
		std::cout << duration.count() << ' ' << deltaTime << '\n';


		// Clearing buffer - colour and depth checks.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// our game logic and update code goes here!

		aie::Gizmos::clear();
		aie::Gizmos::addTransform(glm::mat4(1));
		glm::vec4 white(1);
		glm::vec4 black(0, 0, 0, 1);
		for (int i = 0; i < 21; ++i) {
			aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
				glm::vec3(-10 + i, 0, -10),
				i == 10 ? white : black);
			aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
				glm::vec3(-10, 0, -10 + i),
				i == 10 ? white : black);
		}

		//
		//aie::Gizmos::addAABBFilled(glm::vec3(0), glm::vec3(1.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		glm::mat4 rot(1);

		rot = glm::rotate(deltaTime, glm::vec3(0, 1, 0));
		//Parent orbits centre
		parentMatrix = rot * parentMatrix;

		//Parent spins
		rot = glm::rotate(deltaTime * 3, glm::vec3(0, 1, 0));
		parentMatrix = parentMatrix * rot;




		// Rotate child around parent
		rot = glm::rotate(deltaTime * 2, glm::vec3(0, 1, 0));
		localMatrix = rot * localMatrix;


		// spin child
		rot = glm::rotate(deltaTime * 5, glm::vec3(0, 1, 0));
		localMatrix = localMatrix * rot;

		// once child syncs with parent
		globalMatrix = parentMatrix * localMatrix;



		aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 15.0f, 15.0f, glm::vec4(1.0f, 0.0f, 0.5f, 1.0f), &parentMatrix);
		aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 5.0f, 5.0f, glm::vec4(0.0f, 1.0f, 0.5f, 1.0f), &globalMatrix);


		aie::Gizmos::draw(projection * view);

		// so does our render code!
		glfwSwapBuffers(window);
		glfwPollEvents();
	}




	std::cin.get();
	aie::Gizmos::destroy();

	glfwDestroyWindow(window);
	//Clean up window and gpu linkage.
	glfwTerminate();
	return 0;
}