#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include "macro.h"

using namespace std;

const int Width = 1280;
const int Height = 720;

void windowResizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void render();

int main()
{
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	GLFWwindow* window = glfwCreateWindow(Width, Height, "Sardine's First OpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window." << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Check GLAD init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to init GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, Width, Height);
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);

	clock_t lastTime = clock();
	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		clock_t time = clock();
		cout << "from last time: " << (float)(time - lastTime) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
		lastTime = time;
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
		render();
	}

	glfwTerminate();
	return 0;
}

void windowResizeCallback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);

}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void render()
{
	glClearColor(RGBA(255, 255, 255, 1.0));
	glClear(GL_COLOR_BUFFER_BIT);

	int vertices[] = {
		-.5f, -.5f, 0.0f,
		.5f, -.5f, 0.0f,
		0.0f, .5f, 0.0f,
	};
}
