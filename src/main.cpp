#include <iostream>
#include <memory>

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

	printf("%s\n", "Hello World!");

	winptr window = std::make_shared<Window>(1920, 1080);
	createWindow(window->width, window->height, window);

	while (!canCloseWindow(window))
	{
		glfwPollEvents();
	}

	glfwTerminate();
}