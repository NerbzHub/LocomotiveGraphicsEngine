#pragma once
#include "soxCore.h"

class GameObject
{
public:
	GameObject();
	GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3],glm::mat4 rotation, sns::color color);

	GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], glm::mat4 rotation, sns::color color, GameObject* parent);

	~GameObject();

	void draw();

	glm::mat4 m_globalMatrix[3];
	glm::mat4 m_localMatrix[3];
	glm::mat4 m_rotation;
	sns::color m_color;
	GameObject* m_parent;

};

