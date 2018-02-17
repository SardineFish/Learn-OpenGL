#include "shader_program.h"


ShaderProgram::ShaderProgram()
{

}
ShaderProgram::ShaderProgram(string vertexShaderPath, string fragmentShaderPath)
{
	this->shaderProgram = glCreateProgram();
	this->vertexShader = new Shader(GL_VERTEX_SHADER, vertexShaderPath);
	this->fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentShaderPath);
	glAttachShader(this->shaderProgram, this->vertexShader->shaderID);
	glAttachShader(this->shaderProgram, this->fragmentShader->shaderID);
	glLinkProgram(this->shaderProgram);

	int succeed;
	char log[1024];
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &succeed);
	if (!succeed)
	{
		glGetProgramInfoLog(this->shaderProgram, 1024, NULL, log);
		throw runtime_error(log);
	}
}
ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::use()
{
	glUseProgram(this->shaderProgram);
}

void ShaderProgram::setUniform(string name, int value)
{
	glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), value);
}

void ShaderProgram::setUniform(string name, float value)
{
	glUniform1f(glGetUniformLocation(this->shaderProgram, name.c_str()), value);

}

void ShaderProgram::setUniform(string name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(this->shaderProgram, name.c_str()), x, y, z);
}

void ShaderProgram::setTexture0(string name, Texture* texture)
{
	texture0 = texture;
	setUniform(name, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
}

void ShaderProgram::setTexture1(string name, Texture* texture)
{
	texture1 = texture;
	setUniform(name, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
}

void ShaderProgram::setTexture2(string name, Texture* texture)
{
	texture2 = texture;
	setUniform(name, 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
}

void ShaderProgram::setTexture3(string name, Texture* texture)
{
	texture3 = texture;
	setUniform(name, 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
}

