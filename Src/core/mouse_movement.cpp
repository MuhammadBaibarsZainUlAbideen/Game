#include "mouse_movement.h"

mouse_movement::mouse_movement(glm::vec3 cameraPos,glm::vec3 cameraFront,glm::vec3 cameraUp){
            this->cameraPos = cameraPos;
            this->cameraFront = cameraFront;
            this->cameraUp=cameraUp;
}
void mouse_movement::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;


    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}
mouse_movement::MouseFunc mouse_movement::getMouseCallback() {
    return mouseCallback;
}