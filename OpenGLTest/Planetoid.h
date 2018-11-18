#pragma once
//created by Map
#include <glm/vec2.hpp>

struct Planetoid {
	Planetoid(float x, float y, float r);
	glm::vec2 _pos;
	const float _r;
	const float _m;
	float distanceFunction(int x, int y);
	static const float C_MASS;
};