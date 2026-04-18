#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   
#include <glm/gtc/type_ptr.hpp>
#include "../rendering/Shader.h"


class updating_mvp{
    public:
        glm::mat4 model;
        void cameraPos(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, Shader shader );

};