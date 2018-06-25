/**
	Application.h

	Purpose: Application.h is the header file for the Application class.
			The Application class is what runs as the game loop.
			It contains initialize, update and, render.

			Anything that needs to be inside the application must be 
			declared in this file. This includes shaders, geometry, lights,
			etc.

	@author Nathan Nette
*/
#pragma once
#include "soxCore.h"
#include "Planet.h"
#include "FlyCamera.h"
#include "ParticleEmitter.h"

// Forward declarations
class FlyCamera;

/**
	The Application class is what runs as the game loop.
		It contains initialize, update and, render.

		Anything that needs to be inside the application must be 
		declared in this file. This includes shaders, geometry, lights,
		etc.
*/
class Application
{
public:
	/**
		Application Constructor
			@param1 a_resolution is a vec2 of signed ints to store
					the resolution of the window for the application.
			@param2 a_name is the name that will appear on the window
					when the application is running.
	*/
	Application(const glm::ivec2& a_resolution, const char* a_name);

	/**
		Default Constructor
	*/
	~Application();

	/**
		run is the function to run the application.
	*/
	int run();

protected:

	/**
		initialize is the function that initializes all of the 
			necessary parameters.
	*/
	int initialize();

	/**
		update gets called every frame. Anything that needs to be
			called every frame is in this function such as render
			and any input checks.

			@param1 deltaTime is the current frame rate of the 
					application. 
	*/
	bool update(double deltaTime);

	/**
		render gets called every frame. Render handles all of the
			functions and calls that draw anything to the screen.
			Without this function, nothing would draw.
	*/
	void render();

	/**
		terminate calls any necessary functions that must be called
			as the program is shutting down.
	*/
	int terminate();

	/**
		InitTexture is a function that initializes a shader that
			renders a model with its texture.
	*/
	void InitTexture();
	/**
		UpdateTexture is all of the logic that is needed to run
			every frame in regards to the texture shader.
	*/
	void UpdateTexture();

	/**
		InitPhong is a function that initializes a shader that
			renders a model that is lit using phong lighting.
	*/
	void InitPhong();
	/**
		UpdatePhong is all of the logic that is needed to run
			every frame in regards to the phong shader.
	*/
	void UpdatePhong();

	/**
		InitNormalMap is a function that initializes a shader that
			renders a model that is lit using phong lighting
			and displays them with their texture and can use
			a normal map.
	*/
	void InitNormalMap();
	/**
		UpdateNormalMap is all of the logic that is needed to run
		every frame in regards to the normal map shader.
	*/
	void UpdateNormalMap();

	/**
		InitNormalMap is a function that initializes a shader that
			renders a model that is lit using phong lighting
			and displays them with their texture and can use
			a normal map. However, this shader is so that the
			ground in the sponza scene can be lit.
	*/
	void InitNormalMapDown();

	/**
		UpdateNormalMapDown is all of the logic that is needed to run
			every frame in regards to the normal map shader that
			faces down.
	*/
	void UpdateNormalMapDown();

	/**
		Create quad, creates a quad that can be drawn with a texture
		on it.
	*/
	void createQuad();
	/**
		Create cube creates a cube.
	*/
	void createCube();


	void RenderSpear(aie::ShaderProgram* shaderType);

	//void RenderSponza(aie::ShaderProgram* shaderType);

	void RenderSponzaBuilding(aie::ShaderProgram* shaderType);

	void RenderSponzaCurtains(aie::ShaderProgram * shaderType);

	void RenderSponzaFountainPlants(aie::ShaderProgram * shaderType);

	void RenderSponzaLionHeads(aie::ShaderProgram * shaderType);

	void RenderSponzaPlants(aie::ShaderProgram * shaderType);

	void RenderSponzaRibbons(aie::ShaderProgram * shaderType);

	void RenderSponzaFloor(aie::ShaderProgram * shaderType);


	// m_deltaTime stores the frame count of the application. It
	//	gets passed into the update function.
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
	FlyCamera* m_flyCam;
	ParticleEmitter* m_emitter;

	//----------Shader----------
	aie::ShaderProgram m_shader;
	aie::ShaderProgram m_texturedShader;
	aie::ShaderProgram m_phongShader;
	aie::ShaderProgram m_normalMapShader;
	aie::ShaderProgram m_normalMapShaderDown;
	aie::ShaderProgram m_particleShader;
	glm::mat4 m_particleTransform;

	glm::mat4 m_quadTransform;

	//----------Light----------
	struct Light {
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	Light m_light;
	Light m_downLight;

	

	glm::vec3 m_ambientLight;

	glm::vec3 m_ambientDownLight;


	//----------Texture---------
	aie::Texture m_gridTexture;


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

	aie::OBJMesh m_buddhaMesh;
	glm::mat4 m_buddhaTransform;

	aie::OBJMesh m_spearMesh;
	glm::mat4 m_spearTransform;

	//------Sponza Meshes-------
	/*aie::OBJMesh m_sponzaMesh;
	glm::mat4 m_sponzaTransform;*/

	aie::OBJMesh m_sponzaBuildingMesh;
	glm::mat4 m_sponzaBuildingTransform;

	aie::OBJMesh m_sponzaCurtainsMesh;
	glm::mat4 m_sponzaCurtainsTransform;

	aie::OBJMesh m_sponzaFountainPlantsMesh;
	glm::mat4 m_sponzaFountainPlantsTransform;

	aie::OBJMesh m_sponzaLionHeadsMesh;
	glm::mat4 m_sponzaLionHeadsTransform;

	aie::OBJMesh m_sponzaPlantsMesh;
	glm::mat4 m_sponzaPlantsTransform;

	aie::OBJMesh m_sponzaRibbonsMesh;
	glm::mat4 m_sponzaRibbonsTransform;

	aie::OBJMesh m_sponzaFloorMesh;
	glm::mat4 m_sponzaFloorTransform;
};

