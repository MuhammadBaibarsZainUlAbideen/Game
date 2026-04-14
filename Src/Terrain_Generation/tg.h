#pragma once
#include "FastNoiseLite.h"
#include <vector>
class TG{
    public:
        std::vector<unsigned int> indices;
        const int SIZE = 100;
        std::vector<float> vertices;
        std::vector<float> generateTerrain(FastNoiseLite& noise);
        std::vector<unsigned int> generateIndices();

};