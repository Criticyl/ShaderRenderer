#include "Renderer.h"

Texture Renderer::CreateTexture(int width, int height)
{
    Texture texture;
    texture.Width = width;
    texture.Height = height;

    glCreateTextures(GL_TEXTURE_2D, 1, &texture.ID);
    glTextureStorage2D(texture.ID, 1, GL_RGBA32F, texture.Width, texture.Height);

    glTextureParameteri(texture.ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(texture.ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(texture.ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texture.ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return texture;
}

Framebuffer Renderer::GenerateFramebuffer(int width, int height)
{
    glDeleteTextures(1, &m_Framebuffer.Attatchment.ID);
    Framebuffer fb;
    Texture texture = CreateTexture(width, height);

    glCreateFramebuffers(1, &fb.ID);
    
    //Attatch Texture to framebuffer
    glNamedFramebufferTexture(fb.ID, GL_COLOR_ATTACHMENT0, texture.ID, 0);
    fb.Attatchment = texture;

    m_Framebuffer = fb;
    return fb;
}

void Renderer::BlitFramebufferSwapChain()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer.ID);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glBlitFramebuffer(0, 0,
        m_Framebuffer.Attatchment.Width, m_Framebuffer.Attatchment.Height,
        0, 0,
        m_Framebuffer.Attatchment.Width, m_Framebuffer.Attatchment.Height,
        GL_COLOR_BUFFER_BIT, GL_NEAREST);
}


