#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() 
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float triangle[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.0f
    };

    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    float twoTriangles[] = {
        -0.25f, 0.25f, 0.0f,
        -0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.25f, 0.25f, 0.0f,
        0.5f, 0.0f, 0.0f,
    };

    float triangleOne[] = {
        0.25f, 0.25f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    float triangleTwo[] = {
        -0.25f, 0.25f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.0f
    };

    unsigned int twoTrianglesIndices[] = {
        3, 4, 2,
        0, 2, 1
    };

    //Creating 2 trianles
    // Can create 2 unsigned int VAOs/VBOs or use
    // unsigned int VAOs[2], VBOs[2] as well

    //First Triangle
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //unsigned int EBO;
    //glGenBuffers(1, &EBO);

    //unsigned int EBO_TwoTriangles;
    //glGenBuffers(1, &EBO_TwoTriangles);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(twoTrianglesIndices), twoTrianglesIndices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Second Triangle
    //unsigned int VAO_TriangleTwo;
    //glGenVertexArrays(1, &VAO_TriangleTwo);
    
    //glBindVertexArray(VAO_TriangleTwo);

    //unsigned int VBO_TriangleTwo;
    //glGenBuffers(1, &VBO_TriangleTwo);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO_TriangleTwo);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangleTwo), triangleTwo, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    Shader ourShader("./shader.vs", "./shader.fs");


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //activate shader
        ourShader.use();

        // update the uniform color
        //float timeValue = glfwGetTime();
        //float greenValue = sin(timeValue) / 2.0f + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgramT1, "ourColor");
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glUseProgram(shaderProgramT2);
        //glBindVertexArray(VAO_TriangleTwo);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    glfwTerminate();
    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}