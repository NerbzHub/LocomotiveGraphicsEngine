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


	aie::Gizmos::create(10000, 10000, 10000, 10000);

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


	/*if (m_sponzaMesh.load("../models/Sponza/sponza.obj",
		true, true) == false) {
		printf("House Mesh Error!\n");
		return false;
	}

	m_sponzaTransform = {
		0.5,0,0,0,
		0,0.5,0,0,
		0,0,0.5,0,
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

	//if (m_houseMesh.load("../models/house_obj/house_obj.obj",
	//	true, true) == false) {
	//	printf("House Mesh Error!\n");
	//	return false;
	//}

	//m_houseTransform = {
	//	0.001f,0,0,0,
	//	0,0.001f,0,0,
	//	0,0,0.001f,0,
	//	0,0,0,1
	//};

	/*if (m_grassMesh.load("../models/Grass/grass_low_poly.obj",
		true, true) == false) {
		printf("Grash Mesh Error!\n");
		return false;
	}

	m_grassTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};*/

	/*if (m_treeMesh.load("../models/Tree/Lowpoly_tree_sample.obj",
		true, true) == false) {
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_treeTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};*/

	/*if (m_largeStoneMesh.load("../models/Rocks/LogGrassStone.obj",
		true, true) == false) {
		printf("Large Stone Mesh Error!\n");
		return false;
	}

	m_largeStoneTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};*/


	//createQuad();

	// Quad is 10 units wide.
	/*m_quadTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1 
	};*/

	// Bunny Mesh
	/*if (m_bunnyMesh.load("../stanford/Bunny.obj") == false)
	{
		printf("Bunny Mesh Error! \n");
		return false;
	}
	
	m_bunnyTransform =
	{
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};*/

	//// Buddha Mesh
	//if (m_buddhaMesh.load("../stanford/Buddha.obj") == false)
	//{
	//	printf("Buddha Mesh Error! \n");
	//	return false;
	//}

	/*m_buddhaTransform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};*/

	//// load imaginary texture
	//aie::Texture texture1;
	//texture1.load("../textures/Crackles.png");
	//// create a 2x2 black-n-white checker texture
	//// RED simply means one colour channel, i.e. grayscale
	//aie::Texture texture2;
	//unsigned char texelData[4] = { 0, 255, 255, 0 };
	//texture2.create(2, 2, aie::Texture::RED, texelData);


	// define 6 vertices for 2 triangles
	/*Mesh::Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };
	m_quadMesh.initialise(6, vertices);*/


	// define 4 vertices for 2 triangles

	//Mesh::Vertex verticess[4];
	//verticess[0].position = { -0.5f, 0, 0.5f, 1 };
	//verticess[1].position = { 0.5f, 0, 0.5f, 1 };
	//verticess[2].position = { -0.5f, 0, -0.5f, 1 };
	//verticess[3].position = { 0.5f, 0, -0.5f, 1 };

	//unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };

	//m_quadMesh.initialise(4, verticess, 6, indices);

	//
	//// Quad is 10 units wide.
	//m_quadTransform =
	//{
	//	10,0,0,0,
	//	0,10,0,0,
	//	0,0,10,0,
	//	0,0,0,1 
	//};

	//createQuad();
	/*m_quadTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1 
	};*/

	//createCube();
	//createCylinder();
	//glm::vec3 worldCenter(1, 1, 1);
	//glm::vec4 defaultColour(200, 200, 200, 1);
	//m_circleMesh.initialiseCircle(glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, 10.0f);

	/*m_quadTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1
	};*/

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


	// query time since application started
	float time = glfwGetTime();
	// rotate light
	/*m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2),
		glm::sin(time * 2), 0));*/
	// light looking up
	m_light.direction = glm::normalize(glm::vec3(1, 1, 1));
	//light looking down
	m_downLight.direction = glm::normalize(glm::vec3(1, 1, 1));
	


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
	RenderSponzaFloor(&m_normalMapShaderDown);


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
	m_normalMapShaderDown.bindUniform("Ia", m_ambientLight);
	m_normalMapShaderDown.bindUniform("Id", m_downLight.diffuse);
	m_normalMapShaderDown.bindUniform("Is", m_downLight.specular);
	m_normalMapShaderDown.bindUniform("LightDirection", m_downLight.direction);

	//this aswell
	// Send the camera's position
	m_normalMapShaderDown.bindUniform("cameraPosition", m_flyCam->getPosition());
}

void Application::createQuad()
{
	Mesh::Vertex verticess[4];
	verticess[0].position = { -0.5f, 0, 0.5f, 1 };
	verticess[1].position = { 0.5f, 0, 0.5f, 1 };
	verticess[2].position = { -0.5f, 0, -0.5f, 1 };
	verticess[3].position = { 0.5f, 0, -0.5f, 1 };

	unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };

	m_quadMesh.initialise(4, verticess, 6, indices);
}

void Application::createCube()
{
	// cube
	Mesh::Vertex vertices[8];
	// bottom top left
	vertices[0].position = { -1, -1, -1, 1 };
	// bottom top right
	vertices[1].position = { 1, -1, -1, 1 };
	// bottom bottom left
	vertices[2].position = { -1, -1, 1, 1 };
	// bottom bottom right
	vertices[3].position = { 1, -1, 1, 1 };
	// top top left
	vertices[4].position = { -1, 1, -1, 1 };
	// top top right
	vertices[5].position = { 1, 1, -1, 1 };
	// top bottom left
	vertices[6].position = { -1, 1, 1, 1 };
	// top bottom right
	vertices[7].position = { 1, 1, 1, 1 };
	unsigned int indices[36] = { 0,1,2, 1,2,3, // -y
								 0,1,4, 1,4,5, // -z
								 1,3,5, 3,5,7, // +x
								 4,5,7, 4,6,7, // +y
								 2,6,7, 2,3,7, // +z
								 0,4,6, 0,2,6};// -x
	m_cubeMesh.initialise(8, vertices, 36, indices);
}

bool Application::CreateBunny()
{
	// load vertex shader from file
	m_shader.loadShader(aie::eShaderStage::VERTEX,
		"../shaders/simple.vert");

	// load fragment shader from file
	m_shader.loadShader(aie::eShaderStage::FRAGMENT,
		"../shaders/simple.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	// higher poly version, use bunny_OP.obj for lower poly version
	if (m_bunnyMesh.load("../stanford/bunny_OP.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
		return false;
	}
	else
	{
		m_bunnyTransform = { 0.5f,0,0,0,
			0,0.5f,0,0,
			0,0,0.5f,0,
			-5,0,-5,1 };
	}
}

void Application::RenderBunny()
{
	// bind shader
	m_shader.bind();

	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_quadTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	// draw bunny
	// bind transform
	auto pvmbunny = m_flyCam->getProjectionView() * m_bunnyTransform;
	m_shader.bindUniform("ProjectionViewModel", pvmbunny);

	// draw bunny
	m_bunnyMesh.draw();
}

void Application::RenderBuddha()
{
	// bind shader
	m_texturedShader.bind();

	// bind transform
	auto pvm = m_flyCam->getProjectionView() * m_quadTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);

	// draw buddha
	// bind transform
	auto pvmbuddha = m_flyCam->getProjectionView() * m_buddhaTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvmbuddha);

	// draw bunny
	m_buddhaMesh.draw();
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

