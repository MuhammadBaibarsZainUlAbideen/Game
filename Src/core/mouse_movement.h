#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   
#include <glm/gtc/type_ptr.hpp>

class mouse_movement{
    public:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront; 
        glm::vec3 cameraUp;   
        float yaw   = -90.0f;  
        float pitch =   0.0f;  
        float lastX =  400.0f; 
        float lastY =  400.0f; 
        bool firstMouse = true;
        using MouseFunc = void(*)(GLFWwindow*, double, double);
        mouse_movement(glm::vec3 cameraPos,glm::vec3 cameraFront,glm::vec3 cameraUp);
        void mouseCallback(GLFWwindow* window, double xpos, double ypos);
        MouseFunc getMouseCallback();


};