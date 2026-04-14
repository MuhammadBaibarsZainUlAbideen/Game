#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Buffer{
    public:
        unsigned int VAO, VBO;
        Buffer(float *vertices, int vertexSize, unsigned int *indices, int indexSize);
        

};