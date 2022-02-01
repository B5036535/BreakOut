#include <GLFW/glfw3.h>
#include "Game.h"


const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Breakout", nullptr, nullptr);
	Game g(window, WIDTH, HEIGHT);
	//glfwSetWindowUserPointer(window, this);

	//figure this out
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glfwPollEvents();
		g.Update(static_cast<float>(1.f/60.f));
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 1;
}