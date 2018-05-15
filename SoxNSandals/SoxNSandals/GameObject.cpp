#include "GameObject.h"



GameObject::GameObject()
{
}

GameObject::GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], glm::mat4 rotation)
{
	m_globalMatrix[3] = globalMatrix[3];
	m_localMatrix[3] = localMatrix[3];

	m_rotation = rotation;
}

GameObject::GameObject(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], glm::mat4 rotation, GameObject * parent)
{
	m_globalMatrix[3] = globalMatrix[3];
	m_localMatrix[3] = localMatrix[3];
	m_parent = parent;
}


GameObject::~GameObject()
{
}

void GameObject::draw()
{
	//aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 5.0f, 5.0f, glm::vec4(0.0f, 1.0f, 0.5f, 1.0f), &globalMatrix);
}
