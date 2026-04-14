#include "Window.h"

Window::Window(int width, int height, const char* title) {
    glfwInit();
    handle = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(handle);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}