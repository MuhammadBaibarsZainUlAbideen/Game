#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "rendering/Shader.h"
#include "core/Window.h"
#include "Buffers/buffer.h"
#include "core/movement.h"
#include "core/updating_mvp.h"
#include "FastNoiseLite.h"
#include <vector>
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;
    out vec3 Normal;
    out vec3 Pos;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    void main() {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        Normal = aNormal;
        Pos = aPos;
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 Normal;
    in vec3 Pos;
    out vec4 FragColor;
    vec3 lightDir = normalize(vec3(0,1,3));
    vec3 color_green = vec3(0.0, 0.8, 0.0);
    vec3 color_grey  = vec3(0.5, 0.5, 0.5);
    vec3 color_white = vec3(1.0, 1.0, 1.0);
    vec3 final_color;
    


    void main() {
        float light = max(dot(normalize(Normal), lightDir), 0.0);
        if(Pos.y<2.0){
            final_color = color_green;
        }else if(Pos.y < 2.3){
            final_color = color_grey;
        }else{
            final_color = color_white;
        }

        vec3 result = light*final_color;
        FragColor = vec4(result,1.0);
    }
)";

std::vector<float> generateTerrain(FastNoiseLite& noise) {
    const int SIZE = 100;
    std::vector<float> vertices;

    for (int z = 0; z < SIZE; z++) {
        for (int x = 0; x < SIZE; x++) {
            float height = noise.GetNoise((float)x, (float)z) * 10.0f;
            vertices.push_back(x);
            vertices.push_back(height);
            vertices.push_back(z);
        }
    }
    return vertices;
}
std::vector<unsigned int> generateIndices() {
    const int SIZE = 100;
    std::vector<unsigned int> indices;

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
std::vector<float> normaization(std::vector<unsigned int> & indices, std::vector<float> & vertices){
    int count = 0;
    std::vector<unsigned int> temp;
    std::vector<glm::vec3> temp_vectors;
    std::vector<glm::vec3> normal_arr;
    std::vector<float> vertices_new;

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
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
float yaw   = -90.0f;  
float pitch =   0.0f;  
float lastX =  400.0f; 
float lastY =  400.0f; 
bool firstMouse = true;

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;


    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

int main (){
    glfwInit();
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    std::vector<float> vertices = generateTerrain(noise);
    

    Window window(1800,1200,"Black");
    Move move;
    glfwSetCursorPosCallback(window.handle, mouseCallback);
    glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    Shader shader(vertexShaderSource,fragmentShaderSource);
    shader.use();
    std::vector<unsigned int> indices = generateIndices();
    std::vector<float> vertices_new = normaization(indices, vertices);
    Buffer buffer(vertices_new.data(), vertices_new.size() * sizeof(float), indices.data(), indices.size() * sizeof(unsigned int));
    updating_mvp mvp;


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    while (!glfwWindowShouldClose(window.handle)) {
        cameraPos.y = noise.GetNoise(cameraPos.x, cameraPos.z) * 10.0f + 2.0f;
        glfwPollEvents();
        move.processInput(window.handle, cameraPos, cameraFront,cameraUp);
        
        glClear(GL_COLOR_BUFFER_BIT);
        mvp.cameraPos(cameraPos,cameraFront,cameraUp,shader);        
        
        glDrawArrays(GL_TRIANGLES, 0, vertices_new.size() / 6);
        glfwSwapBuffers(window.handle);
    }

    glfwTerminate();
    return 0;
}