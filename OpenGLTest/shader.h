#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string& fileName, unsigned int type);
	virtual ~Shader();
	GLuint GetShader();
private:
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);
	
	GLuint myShader;
};

#endif