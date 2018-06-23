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

	void InitTexture();
	void UpdateTexture();

	void InitPhong();
	void UpdatePhong();

	void InitNormalMap();
	void UpdateNormalMap();

	void InitNormalMapDown();

	void UpdateNormalMapDown();

	// Initialise various shapes.
	void createQuad();
	void createCube();
	void createCylinder();

	bool CreateBunny();

	void RenderBunny();

	void RenderBuddha();

	void RenderSpear(aie::ShaderProgram* shaderType);

	//void RenderSponza(aie::ShaderProgram* shaderType);

	void RenderSponzaBuilding(aie::ShaderProgram* shaderType);

	void RenderSponzaCurtains(aie::ShaderProgram * shaderType);

	void RenderSponzaFountainPlants(aie::ShaderProgram * shaderType);

	void RenderSponzaLionHeads(aie::ShaderProgram * shaderType);

	void RenderSponzaPlants(aie::ShaderProgram * shaderType);

	void RenderSponzaRibbons(aie::ShaderProgram * shaderType);

	void RenderSponzaFloor(aie::ShaderProgram * shaderType);


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
	aie::ShaderProgram m_texturedShader;
	aie::ShaderProgram m_phongShader;
	aie::ShaderProgram m_normalMapShader;
	aie::ShaderProgram m_normalMapShaderDown;

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

