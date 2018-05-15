#pragma once
#include "soxCore.h"
class GameObject
{
public:
	GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3]);

	GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], GameObject* parent);

	~GameObject();

	glm::mat4 m_globalMatrix[3];
	glm::mat4 m_localMatrix[3];
	GameObject* m_parent;

};

