#include <vector>
#include <Windows.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "MarchingSquares.h"
#include "Renderer.h"
#include "Planetoid.h"
#include "Map.h"

IRenderable *p, **pp = &p;

void PassToRenderer(IRenderable &x) {
	p = &x;
	while (*pp != NULL) {
		Sleep(1);
	}
}

std::vector<glm::vec3> quadVertices = { { 0, 5, 0 },{ 5, 5, 0 },{ 0, 0, 0 },{ 5, 0, 0 } };
std::vector<glm::vec4> quadColors = { { 1, 0, 0, 1 },{ 1, 0, 0, 1 },{ 1, 0, 0, 1 },{ 1, 0, 0, 1 } };
std::vector<glm::vec3> quadNormals = { { 0, 0, 1 },{ 0, 0, 1 },{ 0, 0, 1 },{ 0, 0, 1 } };
std::vector<GLuint> quadElements = { 0, 1, 2, 2, 1, 3 };

int main() {
	Renderer renderer = Renderer(std::ref(pp));

	IRenderable R;
	R._vertices = quadVertices;
	R._colors = quadColors;
	R._normals = quadNormals;
	R._elements = quadElements;
	R._position = { 64.0f, 32.0f, 0.0f };

	std::vector<Planetoid> planets;
	planets.push_back(Planetoid(48.0f, 88.0f, 16.0f));
	planets.push_back(Planetoid(88.0f, 50.0f, 8.0f));
	planets.push_back(Planetoid(32.0f, 32.0f, 32.0f));
	planets.push_back(Planetoid(8.0f, 120.0f, 12.0f));
	planets.push_back(Planetoid(120.0f, 120.0f, 48.0f));
	planets.push_back(Planetoid(128.0f, 0.0f, 32.0f));
	Map map = Map(planets, 128, 128);

	map._vertices = MarchingSquares::GenerateMesh(map);
	map._position = { 0, 0, 0 };
	for (GLuint i = 0; i < map._vertices.size(); i++) {
		map._colors.push_back({ 0, 1, 0, 1 });
		map._normals.push_back(glm::vec3(0, 0, 1));
		map._elements.push_back(i);
	}

	PassToRenderer(R);
	PassToRenderer(map);

	for (int tick = 0;; tick++) {
		//
		// Colt, put your stuff somewhere around here for now
		//
		R._position.x += 0.1f;
		Sleep(10);
	}
}