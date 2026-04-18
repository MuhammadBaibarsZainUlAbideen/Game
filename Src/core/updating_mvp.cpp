#include "updating_mvp.h"

void updating_mvp :: cameraPos(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, Shader shader ){
    glm::mat4 view       = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"),      1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"),       1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
};