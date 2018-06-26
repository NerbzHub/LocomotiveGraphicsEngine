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
		Default Deconstructor
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

			@return true to keep the application running.
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

			@return returns 0 due to the program being shut down.
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

	/**
		Binds a shader to the spear and calls draw on the spear.

			@param1 shaderType is a pointer to a shader.
				This allows me to create any shader, get it
				from memory and set it to this mesh.
	*/
	void RenderSpear(aie::ShaderProgram* shaderType);

	/**
		Binds a shader to the SponzaBuilding and calls draw on it.

			@param1 shaderType is a pointer to a shader.
				This allows me to create any shader, get it
				from memory and set it to this mesh.
	*/
	void RenderSponzaBuilding(aie::ShaderProgram* shaderType);

	/**
		Binds a shader to the SponzaCurtains and calls draw on it.

			@param1 shaderType is a pointer to a shader.
				This allows me to create any shader, get it
				from memory and set it to this mesh.
	*/
	void RenderSponzaCurtains(aie::ShaderProgram * shaderType);

	/**
		Binds a shader to the SponzaFountainPlants and calls 
			draw on it.

			@param1 shaderType is a pointer to a shader.
				This allows me to create any shader, get it
				from memory and set it to this mesh.
	*/
	void RenderSponzaFountainPlants(aie::ShaderProgram * shaderType);

	/**
		Binds a shader to the SponzaLionHeads and calls draw on it.

			@param1 shaderType is a pointer to a shader.
				This allows me to create any shader, get it
				from memory and set it to this mesh.
	*/
	void RenderSponzaLionHeads(aie::ShaderProgram * shaderType);

	/**
		Binds a shader to the SponzaPlants and calls draw on it.

			@param1 shaderType is a pointer to a shader.
				This allows me to create any shader, get it
				from memory and set it to this mesh.
	*/
	void RenderSponzaPlants(aie::ShaderProgram * shaderType);

	/**
		Binds a shader to the SponzaRibbons and calls draw on it.

			@param1 shaderType is a pointer to a shader.
				This allows me to create any shader, get it
				from memory and set it to this mesh.
	*/
	void RenderSponzaRibbons(aie::ShaderProgram * shaderType);

	/**
		Binds a shader to the SponzaFloor and calls draw on it.

			@param1 shaderType is a pointer to a shader.
				This allows me to create any shader, get it
				from memory and set it to this mesh.
	*/
	void RenderSponzaFloor(aie::ShaderProgram * shaderType);


	// m_deltaTime stores the frame count of the application. It
	//	gets passed into the update function.
	double m_deltaTime;

	// Stores the resolution for the application's window as an ivec2.
	glm::ivec2 m_windowResolution;

	// Stores the name for the application's window as a const char*.
	const char* m_windowName;

	// Storing the screens as monitors.
	GLFWmonitor** screens;

	// The amount of screens that the computer has.
	int screenCount = 0;

	// The application's window.
	GLFWwindow* window;

	// Clock.
	sns::clock m_clock;

	// Start time of the application.
	sns::time m_startTime;

	// Current time.
	sns::time m_currentTime;

	// Time since previous frame.
	sns::time m_previousTime;

	// View Matrix for the camera.
	glm::mat4 view;

	// Projection Matrix for the camera.
	glm::mat4 projection;

	// Creating a fly camera for the scene.
	FlyCamera* m_flyCam;

	// Particle emitter.
	ParticleEmitter* m_emitter;

	//----------Shaders----------
	//
	// Regular shader that just draws basic rgba on mesh.
	aie::ShaderProgram m_shader;

	// Shader that allows textures to be drawn to a mesh, unlit.
	aie::ShaderProgram m_texturedShader;

	// Shader that supports phong lights. Doesn't draw textures.
	aie::ShaderProgram m_phongShader;

	// Shader that supports phong lights, textures and, normal maps.
	aie::ShaderProgram m_normalMapShader;

	// Shader that supports phong lights, textures and, normal maps.
	aie::ShaderProgram m_normalMapShaderDown;

	// Shader for the particles.
	aie::ShaderProgram m_particleShader;

	// Transform for where the particle emitter will be in world space.
	glm::mat4 m_particleTransform;

	// Transform of where the centre of the quad will be placed.
	glm::mat4 m_quadTransform;

	//----------Light----------
	struct Light {
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	// Creating new phong light for the scene.
	Light m_light;

	// Creating a new phong light for the scene.
	Light m_downLight;

	// Strength of the light for m_light.
	glm::vec3 m_ambientLight;

	// Strength of the light for m_downlight.
	glm::vec3 m_ambientDownLight;


	//----------Texture---------
	aie::Texture m_gridTexture;


	//----------Mesh------------
	Mesh m_quadMesh;
	Mesh m_cubeMesh;
	Mesh m_circleMesh;
	Mesh m_cylinderMesh;

	//----------OBJ-------------
	// Creating an instance of a mesh for the Sould Spear to be loaded to.
	aie::OBJMesh m_spearMesh;

	// Creating a transform to store the location of the Soul Spear.
	glm::mat4 m_spearTransform;

	//------Sponza Meshes-------
	// Creating an instance of a mesh to store the Sponza Building Mesh.
	aie::OBJMesh m_sponzaBuildingMesh;

	// Creating a new transform matrix to store where the Sponza Building's position is.
	glm::mat4 m_sponzaBuildingTransform;

	// Creating an instance of a mesh to store the Sponza Curtain Mesh.
	aie::OBJMesh m_sponzaCurtainsMesh;

	// Creating a new transform matrix to store where the Sponza Curtain's position is.
	glm::mat4 m_sponzaCurtainsTransform;

	// Creating an instance of a mesh to store the Sponza Fountain Plants Mesh.
	aie::OBJMesh m_sponzaFountainPlantsMesh;

	// Creating a new transform matrix to store where the Sponza Fountain Plants's position is.
	glm::mat4 m_sponzaFountainPlantsTransform;

	// Creating an instance of a mesh to store the Sponza Lion Heads Mesh.
	aie::OBJMesh m_sponzaLionHeadsMesh;

	// Creating a new transform matrix to store where the Sponza Lion Head's position is.
	glm::mat4 m_sponzaLionHeadsTransform;

	// Creating an instance of a mesh to store the Sponza Plants Mesh.
	aie::OBJMesh m_sponzaPlantsMesh;

	// Creating a new transform matrix to store where the Sponza Plants's position is.
	glm::mat4 m_sponzaPlantsTransform;

	// Creating an instance of a mesh to store the Sponza Ribbons Mesh.
	aie::OBJMesh m_sponzaRibbonsMesh;

	// Creating a new transform matrix to store where the Sponza Ribbons's position is.
	glm::mat4 m_sponzaRibbonsTransform;

	// Creating an instance of a mesh to store the Sponza Floor Mesh.
	aie::OBJMesh m_sponzaFloorMesh;

	// Creating a new transform matrix to store where the Sponza Floor's position is.
	glm::mat4 m_sponzaFloorTransform;
};

