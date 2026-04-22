#include "movement.h"


void Move::processInput(GLFWwindow* window, glm::vec3& cube_vertices,glm::vec3& cameraFront,glm::vec3& cameraUp){
    speed = 0.05f;

    //Perpendicular calculation
    glm::vec3 right = glm::normalize(glm::cross(cameraFront, cameraUp));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
         cube_vertices += speed * glm::vec3(cameraFront.x, 0.0f, cameraFront.z);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cube_vertices -= speed * glm::vec3(cameraFront.x, 0.0f, cameraFront.z);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cube_vertices -= speed * glm::vec3(right.x, 0.0f, right.z);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cube_vertices += speed * glm::vec3(right.x, 0.0f, right.z);
}
