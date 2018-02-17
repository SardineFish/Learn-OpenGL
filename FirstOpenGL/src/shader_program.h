#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "shader.h"
#include "texture.h"

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(string vertexShaderPath,string fragmentShaderPath);
	~ShaderProgram();

	void use();
	void setUniform(string name, int value);
	void setUniform(string name, float value);
	void setUniform(string name, float x, float y, float z);

	void setTexture0(string name, Texture texture);
	void setTexture1(string name, Texture texture);
	void setTexture2(string name, Texture texture);
	void setTexture3(string name, Texture texture);

	GLuint shaderProgram;
	Shader vertexShader;
	Shader fragmentShader;
	Texture texture0;
	Texture texture1;
	Texture texture2;
	Texture texture3;
	
};

