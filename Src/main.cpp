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
#include "Terrain_Generation/tg.h"
#include "rendering/normalization.h"
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
    vec3 lightDir = normalize(vec3(2,1,0));
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
float player[] = {
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

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, -3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cube_vertices = glm::vec3(0.0f, 0.0f, 0.0f);
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

    //Making Objects

    FastNoiseLite noise;
    Normal normalization;
    Window window(1800,1200,"Black");
    Shader shader(vertexShaderSource,fragmentShaderSource);
    TG tg;
    Move move;
    updating_mvp mvp;


    //Usage of Noise Objects + tg
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    std::vector<float> vertices = tg.generateTerrain(noise);

    //Usage of tg + notmalization + Creating and Using buffer object
    std::vector<unsigned int> indices = tg.generateIndices();
    std::vector<float> vertices_new = normalization.normaization(indices, vertices);
    Buffer buffer(vertices_new.data(), vertices_new.size() * sizeof(float), indices.data(), indices.size() * sizeof(unsigned int),player, sizeof(player));

    //Usage of Shader Object
    shader.use();
    
    //OpenGl Mouse Call Back
    glfwSetCursorPosCallback(window.handle, mouseCallback);
    glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    while (!glfwWindowShouldClose(window.handle)) {
        glfwPollEvents();
        // cameraPos.y = cube_vertices.y + 1.5f;
        // cameraPos.x = cube_vertices.x - 1.0f;
        // cameraPos.z = cube_vertices.z;

        

        
        
        move.processInput(window.handle, cube_vertices,cameraFront);
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
            
        glBindVertexArray(buffer.VAO);   
        mvp.model = glm::mat4(1.0f);
        mvp.cameraPos(cameraPos,cameraFront,cameraUp,shader,cube_vertices); 
        
        glDrawArrays(GL_TRIANGLES, 0, vertices_new.size() / 6);
        glBindVertexArray(buffer.Player_VAO);
        cube_vertices.y = noise.GetNoise(cube_vertices.x, cube_vertices.z) * 10.0f;
        mvp.model = glm::translate(glm::mat4(1.0f), cube_vertices);
        mvp.cameraPos(cameraPos,cameraFront,cameraUp,shader,cube_vertices); 
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window.handle);
        
    }

    glfwTerminate();
    return 0;
}