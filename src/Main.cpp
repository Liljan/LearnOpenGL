//#define GLEW_STATIC

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>


// Shaders in here like a dumbass.

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource_1 = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const GLchar* fragmentShaderSource_2 = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";

// Normalices device coordinates: NDC
GLfloat vertices[] = {
	// first triangle
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,0.5f,0.0f
};

GLfloat tri_1[] = {
	// First triangle
	-0.9f, -0.5f, 0.0f,  // Left 
	-0.0f, -0.5f, 0.0f,  // Right
	-0.45f, 0.5f, 0.0f  // Top 
};

GLfloat tri_2[] = {
	// Second triangle
	0.0f, -0.5f, 0.0f,  // Left
	0.9f, -0.5f, 0.0f,  // Right
	0.45f, 0.5f, 0.0f   // Top 
};

GLuint indices[] = {
	0,1,3,
	1,2,3
};

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
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL, you fuck!", nullptr, nullptr);
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

	// traingle 1

	GLuint fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_1, 1, &fragmentShaderSource_1, NULL);
	glCompileShader(fragmentShader_1);

	GLuint shaderProgram_1;
	shaderProgram_1 = glCreateProgram();
	glAttachShader(shaderProgram_1, vertexShader);
	glAttachShader(shaderProgram_1, fragmentShader_1);
	glLinkProgram(shaderProgram_1);

	// traingle 2

	GLuint fragmentShader_2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_2, 1, &fragmentShaderSource_2, NULL);
	glCompileShader(fragmentShader_2);

	GLuint shaderProgram_2;
	shaderProgram_2 = glCreateProgram();
	glAttachShader(shaderProgram_2, vertexShader);
	glAttachShader(shaderProgram_2, fragmentShader_2);
	glLinkProgram(shaderProgram_2);

	// TRIANGLE 1

	// Init vertex buffer, vertex array object and element buffer object
	GLuint VBO[2], VAO[2], EBO;
	glGenBuffers(2, VBO);

	glGenVertexArrays(2, VAO);

	glGenBuffers(1, &EBO);

	// 1st triangle
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri_1), tri_1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	// 2nd triangle
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri_2), tri_2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind the VAO
	glBindVertexArray(0);

	// THEN... WAIT FOR IT!
	// Render Loop

	while (!glfwWindowShouldClose(window))
	{
		// Event polling
		glfwPollEvents();

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader program when we want to render an object
		glUseProgram(shaderProgram_1);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderProgram_2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glUseProgram(0);

		// End of frame, swap buffer
		glfwSwapBuffers(window);
	}

	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader_1);
	glDeleteShader(fragmentShader_2);
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate(); // destroys window
	return 0;
}