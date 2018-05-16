#pragma once
#include "soxCore.h"
class Camera
{
public:
	Camera();
	~Camera();

	void CreateCamera(glm::mat4 view, glm::mat4 projection);
};

