#include "Application.h"


Application::Application(const glm::ivec2& a_resolution, const char* a_name)
{
	m_windowResolution = a_resolution;
	m_windowName = a_name;
	m_flyCam = new FlyCamera();
}

Application::~Application()
{
	delete m_flyCam;
}

int Application::run()
{
	initialize();

	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		update(m_deltaTime);
	}
	return 0;
}

int Application::initialize()
{
	//sns::clock m_clock;
	m_startTime = m_clock.now();
	m_currentTime = m_clock.now();
	m_previousTime = m_clock.now();//parentMatrix[3] = glm::vec4(0, 0, 10, 1);
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
	window = glfwCreateWindow(m_windowResolution.x, m_windowResolution.y, m_windowName, nullptr, nullptr);

	screens = glfwGetMonitors(&screenCount);
	//std::cout << screenCount << std::endl;

	// Window x and y, name of window, which screen it's on, shared or exclusive

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


	//load vertex shader from file
	m_shader.loadShader(aie::eShaderStage::VERTEX, "../shaders/simple.vert");

	// load fragment shader from file
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/simple.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
	}
	
	m_quadMesh.initialiseQuad();
	
	// Quad is 10 units wide.
	m_quadTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1 
	};

	//// my camera is located at 10, 10, 10 and looking at the world's 0.
	/*view = glm::lookAt(glm::vec3(15, 15, 15), glm::vec3(0), glm::vec3(0, 1, 0));
	projection = glm::perspective(glm::pi<float>() * 0.25f,
		16 / 9.f, 0.1f, 1000.f);*/

	return 0;
}

bool Application::update(double deltaTime)
{

	m_previousTime = m_currentTime;
	m_currentTime = m_clock.now();

	auto duration = m_currentTime - m_previousTime;

	m_deltaTime = duration.count() * NANO_TO_SECONDS;
	//std::cout << duration.count() << ' ' << deltaTime << '\n';

	//------------imgui------------
	//drawGUI();

	// Clearing buffer - colour and depth checks.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// our game logic and update code goes here!


	aie::Gizmos::clear();
	aie::Gizmos::addTransform(glm::mat4(1));
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}


	//aie::Gizmos::addAABBFilled(glm::vec3(0), glm::vec3(1.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));



	glm::mat4 rot(1);

	rot = glm::rotate(float(deltaTime), glm::vec3(0, 1, 0));
	//Parent orbits centre
	//parentMatrix = rot * parentMatrix;

	//Parent spins
	rot = glm::rotate(float(deltaTime) * 3, glm::vec3(0, 1, 0));
	//parentMatrix = parentMatrix * rot;




	// Rotate child around parent
	rot = glm::rotate(float(deltaTime) * 2, glm::vec3(0, 1, 0));
	//localMatrix = rot * localMatrix;


	// spin child
	rot = glm::rotate(float(deltaTime) * 5, glm::vec3(0, 1, 0));
	//localMatrix = localMatrix * rot;

	// once child syncs with parent
	//globalMatrix = parentMatrix * localMatrix;



	//aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 15.0f, 15.0f, glm::vec4(1.0f, 0.0f, 0.5f, 1.0f), &parentMatrix);
	//aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 5.0f, 5.0f, glm::vec4(0.0f, 1.0f, 0.5f, 1.0f), &globalMatrix);

	render();
	glfwPollEvents();
	//render();
	//aie::Gizmos::draw(m_flyCam.getProjectionView());

	// so does our render code!
	glfwSwapBuffers(window);

	return true;
}

void Application::iterate()
{
}

void Application::render()
{
	m_flyCam->update(m_deltaTime, window);

	// bind shader
	m_shader.bind();

	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_quadTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	// define 6 vertices for 2 triangles
	Mesh::Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };
	m_quadMesh.initialise(6, vertices);

	// draw quad
	m_quadMesh.draw();

	

	aie::Gizmos::draw(m_flyCam->getProjectionView());

	// a simple shader

	//aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 15.0f, 15.0f, glm::vec4(1.0f, 0.0f, 0.5f, 1.0f), &parentMatrix);
	//aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 5.0f, 5.0f, glm::vec4(0.0f, 1.0f, 0.5f, 1.0f), &globalMatrix);
}


int Application::terminate()
{
	aie::Gizmos::destroy();

	glfwDestroyWindow(window);
	//Clean up window and gpu linkage.
	glfwTerminate();
	return 0;
}
