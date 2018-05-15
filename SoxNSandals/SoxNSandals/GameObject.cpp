#include "GameObject.h"



GameObject::GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3])
{
	m_globalMatrix[3] = globalMatrix[3];
	m_localMatrix[3] = localMatrix[3];
}

GameObject::GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], GameObject * parent)
{
	m_globalMatrix[3] = globalMatrix[3];
	m_localMatrix[3] = localMatrix[3];
	m_parent = parent;
}


GameObject::~GameObject()
{
}
