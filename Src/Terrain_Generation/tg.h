#pragma once
#include "FastNoiseLite.h"
#include <vector>
#include "../Buffers/buffer.h"
class TG{
    public:
        struct Chunk{
            std::vector <float> chunk_size;     
            Buffer *buffer= nullptr;
            
        };
        std::vector<Chunk> all_chunks;
        std::vector<unsigned int> indices;
        const int SIZE = 100;
        const int chun_size = 25;
        std::vector<float> vertices;
        std::vector<Chunk> generateTerrain(FastNoiseLite& noise);
        std::vector<unsigned int> generateIndices();

};
