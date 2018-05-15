#pragma once
#include "GameObject.h"

class Planet : public GameObject
{
public:
	Planet();
	// Constructor without a parent
	Planet(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], glm::mat4 rotation, sns::color color);
	//Constructor with a parent
	Planet(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], glm::mat4 rotation, sns::color color, GameObject* parent);

	~Planet();

	void draw();


	
	glm::mat4 m_rotation;
	//rot = glm::rotate(0.0f, glm::vec3(0, 1, 0));
	sns::color m_color;
};

