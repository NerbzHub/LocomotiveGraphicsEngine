#pragma once
#include "soxCore.h"
class FlyCamera
{
public:
	FlyCamera();
	~FlyCamera();

	void update(float deltaTime);

	void setSpeed(float speed);

protected:

	float speed;
	glm::vec3 up;
};

