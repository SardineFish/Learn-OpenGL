#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "shaderLoader.h"

using namespace std;
class Shader
{
public:
	Shader();
	Shader(GLenum type, string path);
	~Shader();
	GLuint shaderID;
	string path;
	string sourceCode;
	GLenum type;
};

