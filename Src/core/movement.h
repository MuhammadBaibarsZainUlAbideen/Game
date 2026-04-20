#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
class Move{
    public:
        float speed;
        glm::vec3 right;
        
        void processInput(GLFWwindow* window, glm::vec3& cube_vertices,glm::vec3& cameraFront,glm::vec3& cameraUp);
        
};