#include <iostream>
#include "Renderer.hpp"

#include "Headers/ResourceManager/ResourceManager.hpp"
#include "Headers/Buffer/VertexBuffer/VertexBuffer.hpp"
#include "Headers/Buffer/VertexBuffer/VertexBufferLayout.hpp"
#include "Headers/Containers/VertexArray.hpp"

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void framebuffer_callback_size(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
}

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 400, "Test", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "FAILED TO CREATE GLFW WINDOW!\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_callback_size);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load OpenGL functions" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 400);

    // vertex data
    float positions[]
    {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    VertexArray VAO;
    VertexBuffer VBO(positions, sizeof(positions));
    VertexBufferLayout Layout;
    Layout.Push<float>(4);
    VAO.AddBuffer(VBO, Layout);

    Shader myShader = ResourceManager::LoadShaderFromFile("Resources/Sprite/Shaders/VertexShader.glsl",
        "Resources/Sprite/Shaders/FragmentShader.glsl",
        "SpriteShader");

    Texture myTexture = ResourceManager::LoadTextureFromFile("Resources/Sprite/Textures/soccer_ball.jpg", "SoccerBall");
    
    myShader.Bind();
    myShader.SetInteger("Sprite", 0);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myTexture.Bind();
        myShader.Bind();
        VAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}