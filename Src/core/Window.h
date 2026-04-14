#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window{
    public:
        GLFWwindow* handle;
        Window(int width, int height, const char* title);
        

};