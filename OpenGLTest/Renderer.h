#pragma once

#include <iostream>
#include <list>
#define _USE_MATH_DEFINES
#include <Math.h>
#include <thread>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IRenderable.h"
#include "Map.h"
#include "MarchingSquares.h"
#include "shader.h"

class Renderer {
	public:
		Renderer(IRenderable **pp);
		~Renderer();
};

