#pragma once

#include <string>
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Texture
{
    std::uint32_t ID = 0;
    std::uint32_t Width = 0;
    std::uint32_t Height = 0;
};

struct Framebuffer
{
    std::uint32_t ID = 0;
    Texture Attatchment;
};

class Renderer
{
public:
    Framebuffer GenerateFramebuffer(int width, int height);
    void BlitFramebufferSwapChain();
private:
    Texture CreateTexture(int width, int height);
private:
    Framebuffer m_Framebuffer;
};