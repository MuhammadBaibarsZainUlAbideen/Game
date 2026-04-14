#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Buffer{
    public:
        unsigned int VAO, VBO;
        unsigned int Player_VBO, Player_VAO;
        Buffer(float *vertices, int vertexSize, unsigned int *indices, int indexSize, float *player_vertices, int player_size);
        

};