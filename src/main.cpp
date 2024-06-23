#include <iostream>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

struct Window
{
	int width = 0;
	int height = 0;

	void* hwnd = nullptr;
};

typedef std::shared_ptr<Window> winptr;

static void createWindow(int width, int height, winptr& window)
{
	window->hwnd = glfwCreateWindow(width, height, "Default Window", nullptr, nullptr);
}

static void destroyWindow(winptr& window)
{
	// assume hwnd is handle to GLFW window
	glfwDestroyWindow(static_cast<GLFWwindow*>(window->hwnd));
}

static bool canCloseWindow(winptr& window)
{
	return glfwWindowShouldClose(static_cast<GLFWwindow*>(window->hwnd));
}

int main(int argc, char* argv[])
{
	if (glfwInit() != GLFW_TRUE)
		perror("Error with glfw lol");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	winptr window = std::make_shared<Window>(1200, 800);
	createWindow(window->width, window->height, window);
	glfwMakeContextCurrent(static_cast<GLFWwindow*>(window->hwnd));

	int version = gladLoadGL(glfwGetProcAddress);

	// this is your render loop
	while (!canCloseWindow(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(static_cast<GLFWwindow*>(window->hwnd));
	}

	destroyWindow(window);
	glfwTerminate();
}