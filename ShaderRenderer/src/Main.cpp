#include <iostream>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Renderer.h"

Shader shader;
Renderer renderer;
static std::uint32_t s_ComputeShader = shader.GetProgram();
static const std::filesystem::path s_ShaderPath = "Shaders/main.glsl";

static void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R)
    {
        shader.ReloadShader(s_ShaderPath);
    }
}

int main()
{
    int WIDTH = 1280;
    int HEIGHT = 720;

    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    shader.CreateShader(s_ShaderPath);
    s_ComputeShader = shader.GetProgram();

    if (s_ComputeShader == -1)
    {
        std::cerr << "Compute shader failed to load!" << std::endl;
        return -1;
    }

    Framebuffer fb = renderer.GenerateFramebuffer(WIDTH, HEIGHT);

    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);

        if (WIDTH != fb.Attatchment.Width || HEIGHT != fb.Attatchment.Height)
        {
            renderer.GenerateFramebuffer(WIDTH, HEIGHT);

        }

        {
            glUseProgram(s_ComputeShader);
            glBindImageTexture(0, fb.Attatchment.ID, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

            const std::uint32_t groupSizeX = 16;
            const std::uint32_t groupSizeY = 16;

            std::uint32_t numGroupsX = (WIDTH + groupSizeX - 1) / groupSizeX;
            std::uint32_t numGroupsY = (WIDTH + groupSizeY - 1) / groupSizeY;

            glDispatchCompute(numGroupsX, numGroupsY, 1);

            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
        }

        {
            renderer.BlitFramebufferSwapChain();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}