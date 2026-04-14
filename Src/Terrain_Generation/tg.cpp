#include "tg.h"

std::vector<float> TG::generateTerrain(FastNoiseLite& noise) {
    


    for (int z = 0; z < SIZE; z++) {
        for (int x = 0; x < SIZE; x++) {
            float height = noise.GetNoise((float)x, (float)z) * 10.0f;
            vertices.push_back(x);
            vertices.push_back(height);
            vertices.push_back(z);
        }
    }
    return vertices;
};

std::vector<unsigned int> TG::generateIndices() {
    
    

    for (int z = 0; z < SIZE - 1; z++) {
        for (int x = 0; x < SIZE - 1; x++) {
            int topLeft     = z * SIZE + x;
            int topRight    = topLeft + 1;
            int bottomLeft  = (z + 1) * SIZE + x;
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