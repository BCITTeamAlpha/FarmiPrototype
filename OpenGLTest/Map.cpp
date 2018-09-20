#include "Map.h"

using std::numeric_limits;
using std::vector;
using std::min;
using std::max;


Map::Map(vector<Planetoid> planets, int width, int height) {
	_height = width;
	_width = height;

	_mapArray = new float[_height * _width];

	// calculate the union of all planetoid distance fields
	for (int x = 0; x < _width; x++) {
		for (int y = 0; y < _height; y++) {
			_mapArray[_index(x, y)] = numeric_limits<float>::max();
			for (int i = 0; i < planets.size(); i++) {
				_mapArray[_index(x, y)] = min(
					_mapArray[_index(x, y)], 
					planets[i].distanceFunction(x, y)
				);
			}
		}
	}
}

// calculate array index so it can be accessed as it were 2d
inline int Map::_index(int x, int y) {
	return x + y * _width;
}

bool Map::isSolid(int x, int y) {
	return _mapArray[_index(x, y)] <= 0.0f;
}

float Map::value(int x, int y) {
	return _mapArray[_index(x, y)];
}

int Map::width() {
	return _width;
}

int Map::height() {
	return _height;
}

void Map::explosion(Planetoid p) {
	for (int x = 0; x < _width; x++) {
		for (int y = 0; y < _height; y++) {
			_mapArray[_index(x, y)] = max(
				_mapArray[_index(x, y)],
				-p.distanceFunction(x, y)
			);
		}
	}
}
