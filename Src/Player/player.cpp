#include  "player.h"

void Player::player_movement(glm::vec3 &cube_vertices,updating_mvp &mvp,FastNoiseLite &noise,float &yaw){
        mvp.model = glm::mat4(1.0f);
        cube_vertices.y = noise.GetNoise(cube_vertices.x, cube_vertices.z) * 10.0f;
        mvp.model = glm::translate(mvp.model, cube_vertices);
        mvp.model = glm::rotate(mvp.model, glm::radians(-yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp.model = glm::scale(mvp.model, glm::vec3(1.0f, 1.3f, 1.0f));
};