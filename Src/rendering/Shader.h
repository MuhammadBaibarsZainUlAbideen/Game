#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexSrc, const char* fragmentSrc);
    
    void use();
    
};