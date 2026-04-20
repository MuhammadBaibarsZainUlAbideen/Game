#include "movement.h"


void Move::processInput(GLFWwindow* window, glm::vec3& cube_vertices,glm::vec3& cameraFront){
    speed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cube_vertices += speed * glm::vec3(cameraFront.x, 0.0f, cameraFront.z);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cube_vertices -= speed * glm::vec3(cameraFront.x, 0.0f, cameraFront.z);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cube_vertices.z -= speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cube_vertices.z += speed;
}
