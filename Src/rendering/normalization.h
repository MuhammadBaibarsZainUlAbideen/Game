#pragma once
#include "FastNoiseLite.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   
#include <glm/gtc/type_ptr.hpp>


class Normal{
    public:
        int count = 0;
        std::vector<unsigned int> temp;
        std::vector<glm::vec3> temp_vectors;
        std::vector<glm::vec3> normal_arr;
        std::vector<float> vertices_new;
        std::vector<float> normaization(std::vector<unsigned int> & indices, std::vector<float> & vertices);
    
};