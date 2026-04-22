#pragma once 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   
#include <glm/gtc/type_ptr.hpp>
#include "../core/updating_mvp.h"
#include "FastNoiseLite.h"
class Player{
    public:
        float player[216] = {
                // Front face (z = 1)
                0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,

                // Back face (z = 0)
                1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
                0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
                1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
                0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
                1.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,

                // Left face (x = 0)
                0.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

                // Right face (x = 1)
                1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,

                // Top face (y = 1)
                0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,

                // Bottom face (y = 0)
                0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
                1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
                1.0f, 0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
                0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
                1.0f, 0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
                0.0f, 0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
            };

        void player_movement(glm::vec3 &cube_vertices,updating_mvp &mvp,FastNoiseLite &noise,float &yaw );

};