#include "updating_mvp.h"

void updating_mvp :: cameraPos(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, Shader shader,glm::vec3 &cube_vertices ){
    eye_position = cube_vertices - glm::normalize(cameraFront) * 5.0f + glm::vec3(0.0f, 2.0f, 0.0f); 
    glm::mat4 view       = glm::lookAt(eye_position, cube_vertices, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"),      1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"),       1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
};