/**
	Application.cpp

	Purpose: Application.cpp is the source file for the Application class.
		The Application class is what runs as the game loop.
		It contains initialize, update and, render.

		This file has the code for the game loop, including the application's
		update function, what draws on the screen in render as well as the 
		logic behind the lights, camera and action.

	@author Nathan Nette
*/
#include "Application.h"

/**
	The Application Constructor creates the window for the application.
		It creates it using the argument resolution and a_name. It
		then, creates a new instance of flyCamera.
*/
Application::Application(const glm::ivec2& a_resolution, const char* a_name)
{
	m_windowResolution = a_resolution;
	m_windowName = a_name;
	m_flyCam = new FlyCamera();
}

/**
	Deconstructor is deleting the flyCam
*/
Application::~Application()
{
	delete m_flyCam;
}

/**
	run is what gets called in main to run the application.
		This is what happens when the application is running.
*/
int Application::run()
{
	// Initializes the application.
	initialize();

	// While the application window exists, run the application.
	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		update(m_deltaTime);
	}
	return 0;
}

int Application::initialize()
{
	//----------------------------------------------------------------------
	//						Clock
	m_startTime = m_clock.now();
	m_currentTime = m_clock.now();
	m_previousTime = m_clock.now();
	//----------------------------------------------------------------------

	// Check to see if we have access to the GPU.
	if (glfwInit() == false)
	{
		// -1 is a failure code.
		return -1;
	}

	// Initialize the application's window.
	// Window x and y, name of window, which screen it's on, shared or exclusive
	window = glfwCreateWindow(m_windowResolution.x, m_windowResolution.y, m_windowName, nullptr, nullptr);

	// Gets the amount of displays the PC has and allocates it into Screens.
	screens = glfwGetMonitors(&screenCount);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	// Makes the application's window the current window.
	glfwMakeContextCurrent(window);

	// If openGL doesn't load, terminate the program and throw error 3.
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	// Getting the version of OpenGL.
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	// Clears screen to grey.
	glClearColor(0.25f, 0.25f, 0.25, 1);

	// Enables depth buffer.
	glEnable(GL_DEPTH_TEST);

	
	//-----------------------------Textured-------------------------------------

	// Initialize the unlit texture shader.
	InitTexture();

	// Load in the soul spear mesh.
	if (m_spearMesh.load("../models/soulspear/soulspear.obj",
		true, true) == false) {
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	// Set the spear mesh's position.
	m_spearTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	//--------------------------PhongNormalMap----------------------------------
	//
	// Initialize the Phong normal map shader.
	InitNormalMap();
	// Initialize the Phong normal map down shader.
	InitNormalMapDown();
	//-------------------------Light---------------------------
	// Setting up the light.
	m_light.diffuse = { 1, 1, 1 };
	m_light.specular = { 1, 1, 1 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };
	m_ambientDownLight = { 0.25f, 0.25f, 0.25f };

	// Load in the Sponza Building mesh and assign it to the correct mesh.
	if (m_sponzaBuildingMesh.load("../models/Sponza/SingleObjs/Building.obj",
		true, true) == false) {
		printf("Building Mesh Error!\n");
		return false;
	}

	// Initialize the Sponza Building's transform.
	m_sponzaBuildingTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	// Load in the Sponza Curtains mesh and assign it to the correct mesh.
	if (m_sponzaCurtainsMesh.load("../models/Sponza/SingleObjs/Curtains.obj",
		true, true) == false) {
		printf("Curtains Mesh Error!\n");
		return false;
	}

	// Initialize the Sponza Curtains' transform.
	m_sponzaCurtainsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	// Load in the Sponza Fountain Plants mesh and assign it to the correct mesh.
	if (m_sponzaFountainPlantsMesh.load("../models/Sponza/SingleObjs/FountainPlants.obj",
		true, true) == false) {
		printf("FountainPlants Mesh Error!\n");
		return false;
	}

	// Initialize the Sponza Plants' transform.
	m_sponzaFountainPlantsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	// Load in the Sponza LionHeads mesh and assign it to the correct mesh.
	if (m_sponzaLionHeadsMesh.load("../models/Sponza/SingleObjs/LionHeads.obj",
		true, true) == false) {
		printf("Lion Heads Mesh Error!\n");
		return false;
	}

	// Initialize the Sponza Lion Head's transform.
	m_sponzaLionHeadsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	// Load in the Sponza Plants mesh and assign it to the correct mesh.
	if (m_sponzaPlantsMesh.load("../models/Sponza/SingleObjs/Plants.obj",
		true, true) == false) {
		printf("Plants Mesh Error!\n");
		return false;
	}

	// Initialize the Sponza Plants' transform.
	m_sponzaPlantsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	// Load in the Sponza Ribbons mesh and assign it to the correct mesh.
	if (m_sponzaRibbonsMesh.load("../models/Sponza/SingleObjs/Ribbons.obj",
		true, true) == false) {
		printf("Ribbons Mesh Error!\n");
		return false;
	}

	// Initialize the Sponza Ribbon's transform.
	m_sponzaRibbonsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	// Normal map down light init
	m_downLight.diffuse = { 1, 1, 1 };
	m_downLight.specular = { 1, 1, 1 };

	// Load in the Sponza Floor mesh and assign it to the correct mesh.
	if (m_sponzaFloorMesh.load("../models/Sponza/SingleObjs/Floor.obj",
		true, true) == false) {
		printf("Floor Mesh Error!\n");
		return false;
	}

	// Initialize the Sponza Floor's transform.
	m_sponzaFloorTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	//--------------------------------------------------------------------------

	//-----------------------------Particles------------------------------------

	// Load vertex shader from file.
	m_particleShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/particleVertex.vert");

	// Load fragment shader from file.
	m_particleShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/particleFrag.frag");

	// If the linking of the particle shader doesn't work, display error.
	if (m_particleShader.link() == false)
	{
		printf("Shader Error: %s\n", m_particleShader.getLastError());
	}
	
	// Creating a new particle emitter.
	m_emitter = new ParticleEmitter();

	// Initializing the values of the new emitter.
	m_emitter->initialise(1000, 500,
		0.1f, 1.0f,
		1, 5,
		1, 0.1f,
		glm::vec4(1, 0, 0, 1), glm::vec4(1, 1, 0, 1));

	// Initialize the particle emitter's transform.
	m_particleTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	return 0;
}

/**
	update gets called every frame. Anything that needs to be
		called every frame is in this function such as render
		and any input checks.

	@param1 deltaTime is the current frame rate of the
		application.

	@return true to keep the application running.
*/
bool Application::update(double deltaTime)
{
	// Sets the previous time to the current time.
	m_previousTime = m_currentTime;

	// Sets the current time variable to the actual current time.
	m_currentTime = m_clock.now();

	// How long it has been since the last frame.
	auto duration = m_currentTime - m_previousTime;

	// deltaTime = how long it has been since the last frame.
	m_deltaTime = duration.count() * NANO_TO_SECONDS;

	// Clearing buffer - colour and depth checks.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Query time since application started.
	float time = glfwGetTime();

	// Light looking up.
	m_light.direction = glm::normalize(glm::vec3(0, 1, 0));

	// Light looking down.
	m_downLight.direction = glm::normalize(glm::vec3(0, 1, 0));

	// Call the update function for the particles.
	m_emitter->update(deltaTime, m_flyCam->getWorldTransform());

	// Call render to draw everything to the screen.
	render();

	// Call the camera's update to see everything in the scene.
	m_flyCam->update(m_deltaTime, window);

	// Swap buffers.
	glfwSwapBuffers(window);

	// Checks whether any input has been done.
	glfwPollEvents();

	return true;
}

void Application::render()
{
	// Texture Shader
	UpdateTexture();

	//Do Normalmap
	UpdateNormalMap();

	UpdateNormalMapDown();

	// bind particle shader

	// draw Spear
	RenderSpear(&m_texturedShader);

	// Draw Building
	RenderSponzaBuilding(&m_normalMapShader);

	// Draw Curtains
	RenderSponzaCurtains(&m_normalMapShader);

	// Draw FountainPlants
	RenderSponzaFountainPlants(&m_normalMapShader);

	// Draw LionHeads
	RenderSponzaLionHeads(&m_normalMapShader);

	// Draw Plants
	RenderSponzaPlants(&m_normalMapShader);

	// Draw Ribbons
	RenderSponzaRibbons(&m_normalMapShader);

	// Draw Floor
	RenderSponzaFloor(&m_normalMapShader);

	// Bind the particle shader.
	m_particleShader.bind();

	// Bind particle transform
	auto pvm = m_flyCam->getProjectionView() * m_particleTransform;
	m_particleShader.bindUniform("ProjectionViewModel", pvm);

	// Draw the particles.
	m_emitter->draw();
}

/**
	terminate calls any necessary functions that must be called
		as the program is shutting down.

	@return returns 0 due to the program being shut down.
*/
int Application::terminate()
{
	delete m_emitter;
	delete screens;
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

/**
	InitTexture is a function that initializes a shader that
		renders an unlit model with its texture.
*/
void Application::InitTexture()
{
	//-----------------------------Textured-------------------------------------

	//load vertex shader from file
	m_texturedShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/textured.vert");

	// load fragment shader from file
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/textured.frag");

	if (m_texturedShader.link() == false)
	{
		printf("Shader Error: %s\n", m_texturedShader.getLastError());
	}

	//--------------------------------------------------------------------------
}

/**
	UpdateTexture is all of the logic that is needed to run
		every frame in regards to the texture shader.
*/
void Application::UpdateTexture()
{
	// Bind shader.
	m_texturedShader.bind();

	// Bind texture location.
	m_texturedShader.bindUniform("diffuseTexture", 0);
}

/**
	InitPhong is a function that initializes a shader that
		renders a model that is lit using phong lighting.
*/
void Application::InitPhong()
{
	//-----------------------------Phong----------------------------------------

	// Load vertex shader from file.
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/phong.vert");

	// Load fragment shader from file.
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/phong.frag");

	if (m_phongShader.link() == false)
	{
		printf("Shader Error: %s\n", m_phongShader.getLastError());
	}

	UpdatePhong();
	//--------------------------------------------------------------------------
}

/**
	UpdatePhong is all of the logic that is needed to run
		every frame in regards to the phong shader.
*/
void Application::UpdatePhong()
{
	//-----------------------------Phong----------------------------------------
	// bind phong shader program
	m_phongShader.bind();

	// Bind light.
	m_phongShader.bindUniform("Ia", m_ambientLight);
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	// Send the camera's position
	m_phongShader.bindUniform("cameraPosition", m_flyCam->getPosition());
	//--------------------------------------------------------------------------
}

/**
	InitNormalMap is a function that initializes a shader that
		renders a model that is lit using phong lighting
		and displays them with their texture and can use
		a normal map.
*/
void Application::InitNormalMap()
{
	//-----------------------------Normal Map-----------------------------------

	// Load normal shader from file.
	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");

	// Load fragment shader from file.
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");

	if (m_normalMapShader.link() == false)
	{
		printf("Shader Error: %s\n", m_normalMapShader.getLastError());
	}

	UpdateNormalMap();
	//--------------------------------------------------------------------------
}

/**
	UpdateNormalMap is all of the logic that is needed to run
		every frame in regards to the normal map shader.
*/
void Application::UpdateNormalMap()
{
	//-------------------------Normal---------------------------
	// Bind phong shader program.
	m_normalMapShader.bind();

	// Bind light.
	m_normalMapShader.bindUniform("Ia", m_ambientLight);
	m_normalMapShader.bindUniform("Id", m_light.diffuse);
	m_normalMapShader.bindUniform("Is", m_light.specular);
	m_normalMapShader.bindUniform("LightDirection", m_light.direction);

	// Send the camera's position.
	m_normalMapShader.bindUniform("cameraPosition", m_flyCam->getPosition());
}

/**
	InitNormalMapDown is a function that initializes a shader that
		renders a model that is lit using phong lighting
		and displays them with their texture and can use
		a normal map. However, this shader is so that the
		ground in the sponza scene can be lit.
*/
void Application::InitNormalMapDown()
{
	//-----------------------------Normal Map-----------------------------------

	// Load normal shader from file.
	m_normalMapShaderDown.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");

	// Load fragment shader from file.
	m_normalMapShaderDown.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");

	if (m_normalMapShaderDown.link() == false)
	{
		printf("Shader Error: %s\n", m_normalMapShaderDown.getLastError());
	}

	UpdateNormalMapDown();
	//--------------------------------------------------------------------------
}

/**
	UpdateNormalMapDown is all of the logic that is needed to run
		every frame in regards to the normal map shader that
		faces down.
*/
void Application::UpdateNormalMapDown()
{
	//-------------------------Normal---------------------------
	// Bind phong shader program.
	m_normalMapShaderDown.bind();

	// Bind light.
	m_normalMapShaderDown.bindUniform("Ia", m_ambientDownLight);
	m_normalMapShaderDown.bindUniform("Id", m_downLight.diffuse);
	m_normalMapShaderDown.bindUniform("Is", m_downLight.specular);
	m_normalMapShaderDown.bindUniform("LightDirection", m_downLight.direction);

	// Send the camera's position.
	m_normalMapShaderDown.bindUniform("cameraPosition", m_flyCam->getPosition());
}

/**
	Binds a shader to the spear and calls draw on the spear.

		@param1 shaderType is a pointer to a shader.
				This allows me to create any shader, get it
				from memory and set it to this mesh.
*/
void Application::RenderSpear(aie::ShaderProgram* shaderType)
{
	// Bind transform.
	auto pvm = m_flyCam->getProjectionView() * m_spearTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);
	
	m_spearMesh.draw();
}

/**
	Binds a shader to the SponzaBuilding and calls draw on it.

	@param1 shaderType is a pointer to a shader.
			This allows me to create any shader, get it
			from memory and set it to this mesh.
*/
void Application::RenderSponzaBuilding(aie::ShaderProgram* shaderType)
{
	// Bind transform.
	auto pvm = m_flyCam->getProjectionView() * m_sponzaBuildingTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// Bind transforms for lighting.
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaBuildingTransform)));

	// Send the camera's position.
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaBuildingMesh.draw();
}

/**
	Binds a shader to the SponzaCurtains and calls draw on it.

	@param1 shaderType is a pointer to a shader.
			This allows me to create any shader, get it
			from memory and set it to this mesh.
*/
void Application::RenderSponzaCurtains(aie::ShaderProgram* shaderType)
{
	// Bind transform.
	auto pvm = m_flyCam->getProjectionView() * m_sponzaCurtainsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// Bind transforms for lighting.
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaCurtainsTransform)));

	// Send the camera's position.
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaCurtainsMesh.draw();
}

/**
	Binds a shader to the SponzaFountainPlants and calls
		draw on it.

	@param1 shaderType is a pointer to a shader.
			This allows me to create any shader, get it
			from memory and set it to this mesh.
*/
void Application::RenderSponzaFountainPlants(aie::ShaderProgram * shaderType)
{
	// Bind transform.
	auto pvm = m_flyCam->getProjectionView() * m_sponzaFountainPlantsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// Bind transforms for lighting.
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaFountainPlantsTransform)));

	// Send the camera's position.
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaFountainPlantsMesh.draw();
}

/**
	Binds a shader to the SponzaLionHeads and calls draw on it.

	@param1 shaderType is a pointer to a shader.
			This allows me to create any shader, get it
			from memory and set it to this mesh.
*/
void Application::RenderSponzaLionHeads(aie::ShaderProgram * shaderType)
{
	// Bind transform.
	auto pvm = m_flyCam->getProjectionView() * m_sponzaLionHeadsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// Bind transforms for lighting.
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaLionHeadsTransform)));

	// Send the camera's position.
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaLionHeadsMesh.draw();
}

/**
	Binds a shader to the SponzaPlants and calls draw on it.

	@param1 shaderType is a pointer to a shader.
		This allows me to create any shader, get it
		from memory and set it to this mesh.
*/
void Application::RenderSponzaPlants(aie::ShaderProgram * shaderType)
{
	// Bind transform.
	auto pvm = m_flyCam->getProjectionView() * m_sponzaPlantsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// Bind transforms for lighting.
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaPlantsTransform)));

	// Send the camera's position.
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaPlantsMesh.draw();
}

/**
	Binds a shader to the SponzaRibbons and calls draw on it.

	@param1 shaderType is a pointer to a shader.
			This allows me to create any shader, get it
			from memory and set it to this mesh.
*/
void Application::RenderSponzaRibbons(aie::ShaderProgram * shaderType)
{
	// Bind transform.
	auto pvm = m_flyCam->getProjectionView() * m_sponzaRibbonsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// Bind transforms for lighting.
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaRibbonsTransform)));

	// Send the camera's position.
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaRibbonsMesh.draw();
}

/**
	Binds a shader to the SponzaFloor and calls draw on it.

	@param1 shaderType is a pointer to a shader.
			This allows me to create any shader, get it
			from memory and set it to this mesh.
*/
void Application::RenderSponzaFloor(aie::ShaderProgram * shaderType)
{
	// Bind transform.
	auto pvm = m_flyCam->getProjectionView() * m_sponzaFloorTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// Bind transforms for lighting.
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaFloorTransform)));

	// Send the camera's position.
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaFloorMesh.draw();
}

