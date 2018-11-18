#pragma once
//uses Planetoids; created by Game
#include <vector>
#include "Planetoid.h"
#include "Renderable.h"

class Map {
	public:
		Map(std::vector<Planetoid> &planets);
		bool isSolid(int x, int y);
		int height();
		void explosion(Planetoid p);
		int width();
		float value(int x, int y);
		Renderable *renderable;
	private:
		int _index(int x, int y);
		float* _mapArray;
		int _height;
		int _width;
};