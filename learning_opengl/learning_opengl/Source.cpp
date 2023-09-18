#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";

const char* fragmentShaderSourceT1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n";

const char* fragmentShaderSourceT2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";



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
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    //unsigned int EBO;
    //glGenBuffers(1, &EBO);

    //unsigned int EBO_TwoTriangles;
    //glGenBuffers(1, &EBO_TwoTriangles);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(twoTrianglesIndices), twoTrianglesIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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


    //Shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShaderT1;
    fragmentShaderT1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderT1, 1, &fragmentShaderSourceT1, nullptr);
    glCompileShader(fragmentShaderT1);

    unsigned int fragmentShaderT2;
    fragmentShaderT2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderT2, 1, &fragmentShaderSourceT2, nullptr);
    glCompileShader(fragmentShaderT2);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShaderT1, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShaderT2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgramT1;
    shaderProgramT1 = glCreateProgram();

    glAttachShader(shaderProgramT1, vertexShader);
    glAttachShader(shaderProgramT1, fragmentShaderT1);
    glLinkProgram(shaderProgramT1);


    glGetProgramiv(shaderProgramT1, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramT1, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgramT2;
    shaderProgramT2 = glCreateProgram();

    glAttachShader(shaderProgramT2, vertexShader);
    glAttachShader(shaderProgramT2, fragmentShaderT2);
    glLinkProgram(shaderProgramT2);

    glGetProgramiv(shaderProgramT2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramT2, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderT1);
    glDeleteShader(fragmentShaderT2);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //activate shader
        glUseProgram(shaderProgramT1);

        // update the uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgramT1, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        
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