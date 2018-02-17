#pragma once
#include <string>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stb_image.h>

typedef unsigned char byte;

using namespace std;
class Texture
{
public:
	Texture();
	Texture(string path);
	~Texture();

	GLuint texture;
	int width;
	int height;
	int nrChannels;
	string path;
	byte* data;
	bool flipVertical;

};

