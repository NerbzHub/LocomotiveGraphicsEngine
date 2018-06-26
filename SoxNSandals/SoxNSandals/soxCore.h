/**
	soxCore.h

	Purpose: This file stores includes and an engine exclusive
			namespace. This is included at the top of every header
			which allows instant access to majority of the necessary
			includes.

	@author Nathan Nette
*/
#pragma once
#include <iostream>
#include <chrono>
#include "gl_core_4_5.h"
#include <glfw3.h>
#include <glm.hpp>
#include <ext.hpp>
#include "Shader.h"
#include "OBJMesh.h"
#include "tiny_obj_loader.h"

/* TIME, Clock, AND DURATION ALIASING*/
using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;
// Expected use: seconds = nanoseconds * NANO_TO_SECONDS
static const double NANO_TO_SECONDS = 0.000000001;
// Expected use: nanoseconds = seconds * NANO_TO_SECONDS
static const ullong NANO_IN_SECONDS = 1000000000ULL;

// sns stands for Sox and Sandals.
namespace sns
{
	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;
	using color = glm::vec4;
}
