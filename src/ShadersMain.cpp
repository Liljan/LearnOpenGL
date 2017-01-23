//#define GLEW_STATIC

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <cmath>


// Shaders in here like a dumbass.

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"ourColor = color;\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"color = ourColor;\n"
"}\n\0";

// Normalices device coordinates: NDC

// set-up vertices w. colors
GLfloat vertices[] = {
	// first triangle
/*	0.5f, 0.5f, 0.0f,
	0.5f, -0.5, 0.0f,
	-0.5f, -0.5f, 0.0f, */
	//-0.5f,0.5f,0.0f

	-1.0f, -1.0f, 0.0f,		/*1.0f, 0.0f, 0.0f,*/  // Bottom Right
	1.0f, -1.0f, 0.0f,		/*0.0f, 1.0f, 0.0f,*/// Bottom Left
	0.0f,  1.0f, 0.0f/*,		0.0f, 0.0f, 1.0f */ // Top 
};

GLuint indices[] = {
	0,1,3,
	//1,2,3
};

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main() {
	std::cout << "Situation" << std::endl;

	// CODE

	// Setup OpenGL v. 3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Open window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL, you fuck!", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Window done goofed." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	// setup call-back function
	glfwSetKeyCallback(window, key_callback);

	// Init GLEW

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW done goofed." << std::endl;
	}

	// Init window
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Build and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Init vertex buffer, vertex array object and element buffer object
	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &EBO);

	// 1st triangle
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind the VAO
	glBindVertexArray(0);

	// THEN... WAIT FOR IT!
	// Render Loop

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		// Event polling
		glfwPollEvents();

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader program when we want to render an object
		glUseProgram(shaderProgram);

		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = sin(timeValue) / 2.0f + 0.5f;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glUseProgram(0);

		// End of frame, swap buffer
		glfwSwapBuffers(window);
	}

	glUseProgram(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate(); // destroys window
	return 0;
}