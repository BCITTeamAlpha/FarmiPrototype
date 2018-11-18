#include "Planetoid.h"
#include "glm/glm.hpp"

const float Planetoid::C_MASS = 50.0f;

Planetoid::Planetoid(float x, float y, float r) : 
	_r(r),
	//Calculates the mass of a planetoid with similar density to earth based
	//on the radius. Scale factor makes the radius more reasonable for a planet.
	//Multiplied by the gravitational constant for efficiency reasons.
	_m(r*r*C_MASS),
	_pos(x, y)
{ }

// signed distance of a point from the surface of the planetoid
float Planetoid::distanceFunction(int x, int y) {
	return glm::length(_pos - glm::vec2(x, y)) - _r;
}