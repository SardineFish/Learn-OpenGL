#include "shader.h"


Shader::Shader()
{
	
}
Shader::Shader(GLenum type,string path)
{
	this->type = type;
	this->path = path;
	this->shaderID = glCreateShader(type);
	this->sourceCode = readFile(path);
	const char* code = this->sourceCode.c_str();
	glShaderSource(this->shaderID, 1, &code, NULL);
	glCompileShader(this->shaderID);
	int success;
	char infoLog[1024];
	glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->shaderID, GL_COMPILE_STATUS, NULL, infoLog);
		throw runtime_error(infoLog);
	}
}


Shader::~Shader()
{
	glDeleteShader(this->shaderID);
}
