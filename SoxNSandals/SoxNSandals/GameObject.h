#pragma once
#include "soxCore.h"
class GameObject
{
public:
	GameObject();
	GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], glm::mat4 rotation);

	GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], glm::mat4 rotation, GameObject* parent);

	~GameObject();

	void draw();

	glm::mat4 m_globalMatrix[3];
	glm::mat4 m_localMatrix[3];
	glm::mat4 m_rotation;
	GameObject* m_parent;

};

