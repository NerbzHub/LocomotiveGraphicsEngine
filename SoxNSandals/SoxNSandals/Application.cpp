/**
	Application.cpp
*/
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
	//----------------------------------------------------------------------
	//						Clock
	//sns::clock m_clock;
	m_startTime = m_clock.now();
	m_currentTime = m_clock.now();
	m_previousTime = m_clock.now();//parentMatrix[3] = glm::vec4(0, 0, 10, 1);
	//----------------------------------------------------------------------


	//localMatrix[3] = glm::vec4(1, 0, -2, 1);

	//----------------------------------------------------------------------
	//						Rot
	glm::mat4 rot(1);
	rot = glm::rotate(0.0f, glm::vec3(0, 1, 0));
	//----------------------------------------------------------------------

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

	//-----------------------------Plain---------------------------------------

	////load vertex shader from file
	//m_shader.loadShader(aie::eShaderStage::VERTEX, "../shaders/simple.vert");

	//// load fragment shader from file
	//m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/simple.frag");

	//if (m_shader.link() == false)
	//{
	//	printf("Shader Error: %s\n", m_shader.getLastError());
	//}
	//--------------------------------------------------------------------------

	//-----------------------------Textured-------------------------------------

	////load vertex shader from file
	//m_texturedShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/textured.vert");

	//// load fragment shader from file
	//m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/textured.frag");

	//if (m_texturedShaderr.link() == false)
	//{
	//	printf("Shader Error: %s\n", m_texturedShader.getLastError());
	//}
	//--------------------------------------------------------------------------

	//InitTexture();

	//InitPhong();

	InitNormalMap();
	InitNormalMapDown();

	//-------------------------Light---------------------------
	m_light.diffuse = { 1, 1, 1 };
	m_light.specular = { 1, 1, 1 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };
	m_ambientDownLight = { 0.25f, 0.25f, 0.25f };



	/*if (m_spearMesh.load("../models/soulspear/soulspear.obj",
		true, true) == false) {
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_spearTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};*/

	if (m_sponzaBuildingMesh.load("../models/Sponza/SingleObjs/Building.obj",
		true, true) == false) {
		printf("Building Mesh Error!\n");
		return false;
	}

	m_sponzaBuildingTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	if (m_sponzaCurtainsMesh.load("../models/Sponza/SingleObjs/Curtains.obj",
		true, true) == false) {
		printf("Curtains Mesh Error!\n");
		return false;
	}

	m_sponzaCurtainsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	if (m_sponzaFountainPlantsMesh.load("../models/Sponza/SingleObjs/FountainPlants.obj",
		true, true) == false) {
		printf("FountainPlants Mesh Error!\n");
		return false;
	}

	m_sponzaFountainPlantsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	if (m_sponzaLionHeadsMesh.load("../models/Sponza/SingleObjs/LionHeads.obj",
		true, true) == false) {
		printf("Lion Heads Mesh Error!\n");
		return false;
	}

	m_sponzaLionHeadsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	if (m_sponzaPlantsMesh.load("../models/Sponza/SingleObjs/Plants.obj",
		true, true) == false) {
		printf("Plants Mesh Error!\n");
		return false;
	}

	m_sponzaPlantsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	if (m_sponzaRibbonsMesh.load("../models/Sponza/SingleObjs/Ribbons.obj",
		true, true) == false) {
		printf("Ribbons Mesh Error!\n");
		return false;
	}

	m_sponzaRibbonsTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	// Normal map down light init
	m_downLight.diffuse = { 1, 1, 1 };
	m_downLight.specular = { 1, 1, 1 };

	if (m_sponzaFloorMesh.load("../models/Sponza/SingleObjs/Floor.obj",
		true, true) == false) {
		printf("Floor Mesh Error!\n");
		return false;
	}

	m_sponzaFloorTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	////load vertex shader from file
	m_particleShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/particleVertex.vert");

	// load fragment shader from file
	m_particleShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/particleFrag.frag");

	if (m_particleShader.link() == false)
	{
		printf("Shader Error: %s\n", m_particleShader.getLastError());
	}
	
	
	m_emitter = new ParticleEmitter();
	m_emitter->initialise(1000, 500,
		0.1f, 1.0f,
		1, 5,
		1, 0.1f,
		glm::vec4(1, 0, 0, 1), glm::vec4(1, 1, 0, 1));

	m_particleTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	
	return 0;
}

bool Application::update(double deltaTime)
{

	m_previousTime = m_currentTime;
	m_currentTime = m_clock.now();

	auto duration = m_currentTime - m_previousTime;

	m_deltaTime = duration.count() * NANO_TO_SECONDS;

	// Clearing buffer - colour and depth checks.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);


	// query time since application started
	float time = glfwGetTime();

	// light looking up
	m_light.direction = glm::normalize(glm::vec3(0, 1, 0));
	//light looking down
	m_downLight.direction = glm::normalize(glm::vec3(0, 1, 0));

	


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

	m_emitter->update(deltaTime, m_flyCam->getWorldTransform());

	render();

	m_flyCam->update(m_deltaTime, window);

	glfwSwapBuffers(window);

	glfwPollEvents();


	//render();
	//aie::Gizmos::draw(m_flyCam.getProjectionView());

	// so does our render code!

	return true;
}

void Application::render()
{

	//// bind shader
	//m_shader.bind();

	// bind shader
	//m_texturedShader.bind();

	//// bind texture location
	//m_texturedShader.bindUniform("diffuseTexture", 0);

	// bind texture location
	//m_texturedShader.bindUniform("diffuseTexture", 0);

	// bind transform
	/*auto pvm = m_flyCam->getProjectionView() * m_spearTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);*/

	/*auto pvm = m_flyCam->getProjectionView() * m_quadTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);*/


	////-------------------------Phong---------------------------
	//// bind phong shader program
	//m_phongShader.bind();

	//// bind light
	//m_phongShader.bindUniform("Ia", m_ambientLight);
	//m_phongShader.bindUniform("Id", m_light.diffuse);
	//m_phongShader.bindUniform("Is", m_light.specular);
	//m_phongShader.bindUniform("LightDirection", m_light.direction);

	//// bind transform
	//auto pvm = m_flyCam->getProjectionView() * m_spearTransform;
	//m_phongShader.bindUniform("ProjectionViewModel", pvm);

	//// bind transforms for lighting
	//m_phongShader.bindUniform("NormalMatrix",
	//	glm::inverseTranspose(glm::mat3(m_spearTransform)));

	//// Send the camera's position
	//m_phongShader.bindUniform("cameraPosition", m_flyCam->getPosition());


	// bind texture to specified location
	//m_gridTexture.bind(0);
	
	//Do phong
	//UpdatePhong();

	//Do Normalmap
	UpdateNormalMap();

	UpdateNormalMapDown();

	// bind particle shader

	// draw quad
	//m_quadMesh.draw();

	// draw cube
	//m_cubeMesh.draw();

	// draw cylinder
	//m_cylinderMesh.draw();
	
	// draw circle
	//m_circleMesh.draw();
	
	// draw bunny
	//m_bunnyMesh.draw();
	//RenderBunny();

	// draw buddha
	//RenderBuddha();

	// draw Spear
	//RenderSpear(&m_normalMapShader);

	// draw Sponza
	//RenderSponza(&m_normalMapShader);

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

	m_particleShader.bind();

	// bind particle transform
	auto pvm = m_flyCam->getProjectionView() * m_particleTransform;
	m_particleShader.bindUniform("ProjectionViewModel", pvm);
	m_emitter->draw();

	// a simple shader

	//aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 15.0f, 15.0f, glm::vec4(1.0f, 0.0f, 0.5f, 1.0f), &parentMatrix);
	//aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 5.0f, 5.0f, glm::vec4(0.0f, 1.0f, 0.5f, 1.0f), &globalMatrix);
}


int Application::terminate()
{
	delete m_emitter;
	delete screens;
	glfwDestroyWindow(window);
	//Clean up window and gpu linkage.
	glfwTerminate();
	return 0;
}

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

void Application::UpdateTexture()
{
}

void Application::InitPhong()
{
	//-----------------------------Phong----------------------------------------

	//load vertex shader from file
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/phong.vert");

	// load fragment shader from file
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/phong.frag");


	if (m_phongShader.link() == false)
	{
		printf("Shader Error: %s\n", m_phongShader.getLastError());
	}

	UpdatePhong();
	//--------------------------------------------------------------------------
}

void Application::UpdatePhong()
{
	// from here
	//-------------------------Phong---------------------------
	// bind phong shader program
	m_phongShader.bind();

	// bind light
	m_phongShader.bindUniform("Ia", m_ambientLight);
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);
	// to here is going into phong creation

	//this aswell
	// Send the camera's position
	m_phongShader.bindUniform("cameraPosition", m_flyCam->getPosition());
}

void Application::InitNormalMap()
{
	//-----------------------------Normal Map-----------------------------------

	//load normal shader from file
	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");

	// load fragment shader from file
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");


	if (m_normalMapShader.link() == false)
	{
		printf("Shader Error: %s\n", m_normalMapShader.getLastError());
	}

	UpdateNormalMap();
	//--------------------------------------------------------------------------
}

void Application::UpdateNormalMap()
{
	//-------------------------Normal---------------------------
	// bind phong shader program
	m_normalMapShader.bind();

	// bind light
	m_normalMapShader.bindUniform("Ia", m_ambientLight);
	m_normalMapShader.bindUniform("Id", m_light.diffuse);
	m_normalMapShader.bindUniform("Is", m_light.specular);
	m_normalMapShader.bindUniform("LightDirection", m_light.direction);

	//this aswell
	// Send the camera's position
	m_normalMapShader.bindUniform("cameraPosition", m_flyCam->getPosition());
}

void Application::InitNormalMapDown()
{
	//-----------------------------Normal Map-----------------------------------

	//load normal shader from file
	m_normalMapShaderDown.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");

	// load fragment shader from file
	m_normalMapShaderDown.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");


	if (m_normalMapShaderDown.link() == false)
	{
		printf("Shader Error: %s\n", m_normalMapShaderDown.getLastError());
	}

	UpdateNormalMapDown();
	//--------------------------------------------------------------------------
}

void Application::UpdateNormalMapDown()
{
	//-------------------------Normal---------------------------
	// bind phong shader program
	m_normalMapShaderDown.bind();

	// bind light
	m_normalMapShaderDown.bindUniform("Ia", m_ambientDownLight);
	m_normalMapShaderDown.bindUniform("Id", m_downLight.diffuse);
	m_normalMapShaderDown.bindUniform("Is", m_downLight.specular);
	m_normalMapShaderDown.bindUniform("LightDirection", m_downLight.direction);

	//this aswell
	// Send the camera's position
	m_normalMapShaderDown.bindUniform("cameraPosition", m_flyCam->getPosition());
}

void Application::RenderSpear(aie::ShaderProgram* shaderType)
{
	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_spearTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_spearTransform)));

	// Send the camera's position
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());
	
	m_spearMesh.draw();
}

//void Application::RenderSponza(aie::ShaderProgram* shaderType)
//{
//	// bind transform
//	auto pvm = m_flyCam->getProjectionView() * m_sponzaTransform;
//	shaderType->bindUniform("ProjectionViewModel", pvm);
//
//	// bind transforms for lighting
//	shaderType->bindUniform("NormalMatrix",
//		glm::inverseTranspose(glm::mat3(m_sponzaTransform)));
//
//	// Send the camera's position
//	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());
//
//	m_sponzaMesh.draw();
//}

void Application::RenderSponzaBuilding(aie::ShaderProgram* shaderType)
{
	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_sponzaBuildingTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaBuildingTransform)));

	// Send the camera's position
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaBuildingMesh.draw();
}

void Application::RenderSponzaCurtains(aie::ShaderProgram* shaderType)
{
	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_sponzaCurtainsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaCurtainsTransform)));

	// Send the camera's position
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaCurtainsMesh.draw();
}

void Application::RenderSponzaFountainPlants(aie::ShaderProgram * shaderType)
{
	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_sponzaFountainPlantsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaFountainPlantsTransform)));

	// Send the camera's position
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaFountainPlantsMesh.draw();
}

void Application::RenderSponzaLionHeads(aie::ShaderProgram * shaderType)
{
	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_sponzaLionHeadsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaLionHeadsTransform)));

	// Send the camera's position
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaLionHeadsMesh.draw();
}

void Application::RenderSponzaPlants(aie::ShaderProgram * shaderType)
{
	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_sponzaPlantsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaPlantsTransform)));

	// Send the camera's position
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaPlantsMesh.draw();
}

void Application::RenderSponzaRibbons(aie::ShaderProgram * shaderType)
{
	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_sponzaRibbonsTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaRibbonsTransform)));

	// Send the camera's position
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaRibbonsMesh.draw();
}

void Application::RenderSponzaFloor(aie::ShaderProgram * shaderType)
{
	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_sponzaFloorTransform;
	shaderType->bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	shaderType->bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_sponzaFloorTransform)));

	// Send the camera's position
	shaderType->bindUniform("cameraPosition", m_flyCam->getPosition());

	m_sponzaFloorMesh.draw();
}

