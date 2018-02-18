#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "macro.h"
#include "shaderLoader.h"
#include "shader.h"
#include "shader_program.h"
#include "texture.h"

using namespace std;
using namespace glm;

typedef unsigned char byte;

const int Width = 1280;
const int Height = 720;

void windowResizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void render(float time);
void initShader();
void initBuffer();
void initTexture();

ShaderProgram shaderProgram;
unsigned int VBO, VAO, EBO;
Texture texture, texWall;

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

	initShader();
	initBuffer();
	initTexture();

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float lastTime = (float)glfwGetTime();
	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		float time = (float)glfwGetTime();
		//cout << "from last time: " << (float)(time - lastTime) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
		lastTime = time;
		processInput(window);
		render(time);
		glfwSwapBuffers(window);
		glfwPollEvents();
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

void render(float time)
{
	glClearColor(RGBA(50, 50, 50, 1.0));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glUseProgram(shaderProgram.shaderProgram);
	shaderProgram.use();
	shaderProgram.setUniform("t", time);
	//glUniform1f(glGetUniformLocation(shaderProgram.shaderProgram, "t"), time);
	shaderProgram.setTexture0("myTexture", &texture);
	shaderProgram.setTexture1("texWall", &texWall);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	mat4 model;
	model = rotate(model, radians(time*10), vec3(1.0f, 0, 0));
	model = rotate(model, radians(time * 30), vec3(0, 1.0f, 0));
	mat4 view;
	view = translate(view, vec3(0, 0, -3.0f));
	mat4 projection;
	projection = perspective(radians(90.0f), (float)Width / (float)Height, 0.1f, 100.0f);

	mat4 trans = projection * view*model;
	//trans = perspective(radians(45.0f), 1.0f, -0.5f, 10.0f);

	//int idx = glGetUniformLocation(shaderProgram.shaderProgram, "transform");
	//trans = rotate(trans, radians(time*30), vec3(1.0, 1.0, 0.0));
	//trans = scale(trans, vec3(.8, .8, .8));
	shaderProgram.setUniformMatrix("transform", value_ptr(trans));
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.shaderProgram, "transform"), 1, GL_FALSE, value_ptr(trans));

	//shaderProgram.setUniform("myTexture", 0);
	//shaderProgram.setUniform("texWall", 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texWall.texture);
	glBindVertexArray(VAO);
	for (int i = 0; i < 10; i++)
	{
		model = translate(mat4(1.0), cubePositions[i]);
		
		trans = projection * view * model;
		trans = rotate(trans, radians(time * 10), vec3(1.0f, 0, 0));
		trans = rotate(trans, radians(time * 30), vec3(0, 1.0f, 0));

		shaderProgram.setUniformMatrix("transform", value_ptr(trans));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//glDrawArrays(GL_TRIANGLES, 0, 36); 

	//glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void initShader()
{
	shaderProgram = ShaderProgram("src/shader/vertexShader.glsl", "src/shader/fragmentShader.glsl");
}
void initBuffer()
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	unsigned int indices[] = {
		0,1,3,
		1,2,3,
		4,5,6,
	};
	float texCoords[] = {
		.5,.5,
		.5f,-.5f,
		-.5f,-.5f,
		-.5f,.5f,
		1,-1,
		-1,-1,
		0,1,
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Copy vertices into VBO (?
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Copy index array into EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/

	


}

void initTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture = Texture("res/texture/img.jpg");
	texWall = Texture("res/texture/wall.jpg");

	//shaderProgram.setTexture0("myTexture", &texture);
	//shaderProgram.setTexture1("texWall", &texWall);

}