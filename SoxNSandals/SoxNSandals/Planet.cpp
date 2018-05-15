#include "Planet.h"



Planet::Planet()
{
}

Planet::Planet(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], sns::color color)
{
	m_globalMatrix[3] = globalMatrix[3];
	m_localMatrix[3] = localMatrix[3];
	m_color = color;
}

Planet::Planet(glm::mat4 globalMatrix[3], glm::mat4 localMatrix[3], sns::color color, GameObject * parent)
{
	m_globalMatrix[3] = globalMatrix[3];
	m_localMatrix[3] = localMatrix[3];
	m_parent = parent;
	m_color = color;
}


Planet::~Planet()
{
}
