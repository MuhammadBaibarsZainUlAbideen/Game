#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
class Move{
    public:
        float cameraSpeed;
        
        void processInput(GLFWwindow* window, glm::vec3& cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
        
};