#pragma once

#include <math.h>

class Planetoid {
	public:
		Planetoid(float x, float y, float r);
		const float _x;
		const float _y;
		const float _r;
		const float _m;
		float distanceFunction(int x, int y);
	private:
};