#include "normalization.h"

std::vector<float> Normal::normaization(std::vector<unsigned int> & indices, std::vector<float> & vertices){

    for(int i = 0 ; i< indices.size(); i++){
        count += 1;
        temp.push_back(indices[i]);
        if(count == 3){

            for(int j =0; j<count; j++){
                temp_vectors.push_back(glm::vec3(vertices[temp[j] * 3 + 0],vertices[temp[j] * 3 + 1],vertices[temp[j] * 3 + 2]));


            }
            glm::vec3 edge_1 = temp_vectors[1] - temp_vectors[0];
            glm::vec3 edge_2 = temp_vectors[2] - temp_vectors[0];
            glm::vec3 normal = glm::cross(edge_1,edge_2);

            // normal_arr.push_back(normal);
            for(int f =0; f<count; f++){
                vertices_new.push_back(vertices[temp[f] * 3 + 0]); 
                vertices_new.push_back(vertices[temp[f] * 3 + 1]); 
                vertices_new.push_back(vertices[temp[f] * 3 + 2]); 
                vertices_new.push_back(normal.x);
                vertices_new.push_back(normal.y);
                vertices_new.push_back(normal.z);              


            }


            count =0;
            temp.clear();
            temp_vectors.clear();
    
    

        }




    }
    return vertices_new;

};