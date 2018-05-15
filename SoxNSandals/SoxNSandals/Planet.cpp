#include "Planet.h"



Planet::Planet()
{
}

Planet::Planet(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], glm::mat4 rotation, sns::color color)
{
	m_globalMatrix[3] = globalMatrix[3];
	m_localMatrix[3] = localMatrix[3];
	m_color = color;
}

Planet::Planet(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], glm::mat4 rotation, sns::color color, GameObject * parent)
{
	m_globalMatrix[3] = globalMatrix[3];
	m_localMatrix[3] = localMatrix[3];
	m_parent = parent;
	m_color = color;
	
}


Planet::~Planet()
{
}

void Planet::draw()
{
	aie::Gizmos::addSphere(glm::vec3(0), 1.0f, 5.0f, 5.0f, glm::vec4(0.0f, 1.0f, 0.5f, 1.0f), m_globalMatrix);
}
