#pragma once
#include "FastNoiseLite.h"
#include <vector>
class TG{
    public:
        struct chunks{
            vector <float> chunk_size;       
        }
        std::vector<chunks> all_chunks;
        std::vector<unsigned int> indices;
        const int SIZE = 100;
        const int chun_size = 25;
        std::vector<float> vertices;
        std::vector<float> generateTerrain(FastNoiseLite& noise);
        std::vector<unsigned int> generateIndices();

};
