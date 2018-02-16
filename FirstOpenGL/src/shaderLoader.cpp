#include "shaderLoader.h"

using namespace std;
string readFile(const string path)
{
	ifstream file;
	file.open(path, ios::in);

	stringstream strStream;
	strStream << file.rdbuf();
	string text = strStream.str();
	const char* str = text.c_str();
	return text;
}

unsigned int loadShader(GLenum type, const string path)
{
	string srcStr = readFile(path);
	const char* code = srcStr.c_str();
	unsigned int shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	int succeed;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &succeed);
	if (!succeed)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		throw runtime_error(infoLog);
	}
	return shader;
}