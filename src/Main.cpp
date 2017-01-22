//#define GLEW_STATIC

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

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

	// Render Loop

	while (!glfwWindowShouldClose(window))
	{
		// Event polling
		glfwPollEvents();

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// End of frame, swap buffer
		glfwSwapBuffers(window);
	}

	glfwTerminate(); // destroys window
}