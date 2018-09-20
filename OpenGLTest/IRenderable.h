#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class IRenderable {
	public:
		glm::vec3 _position;
		glm::vec3 _rotation;
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec4> _colors;
		std::vector<glm::vec3> _normals;
		std::vector<GLuint> _elements;
		GLuint _vertexBufferLocation;
		GLuint _colorBufferLocation;
		GLuint _normalBufferLocation;
		GLuint _elementBufferLocation;
		GLuint _id; // use ID for signalling renderer to remove from rendering list?
		// or maybe have a setable flag that tells Renderer to delete it?
		bool _invalidated;
};
