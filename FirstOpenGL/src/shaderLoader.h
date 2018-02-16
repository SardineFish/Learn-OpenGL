#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string readFile(string path);

unsigned int loadShader(GLenum type, const string path);