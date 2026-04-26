#include "tg.h"

std::vector<TG::Chunk> TG::generateTerrain(FastNoiseLite& noise) {
    

    for(int i = 0; i < SIZE; i += 25){
        Chunk chunk;
        
        for (int z = 0; z < chun_size; z++) {
            for (int x = 0; x < chun_size; x++) {
            float height = noise.GetNoise((float)x, (float)z) * 10.0f;
                chunk.chunk_size.push_back(x);
                chunk.chunk_size.push_back(height);
                chunk.chunk_size.push_back(z);
            }
        }
        all_chunks.push_back(chunk);
    }
    return all_chunks;
};

std::vector<unsigned int> TG::generateIndices() {
    
    

    for (int z = 0; z < chun_size - 1; z++) {
        for (int x = 0; x < chun_size - 1; x++) {
            int topLeft     = z * chun_size + x;
            int topRight    = topLeft + 1;
            int bottomLeft  = (z + 1) * chun_size + x;
            int bottomRight = bottomLeft + 1;

           
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
    return indices;
}