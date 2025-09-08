#include "Shader.h"

#include <iostream>
#include <fstream>

#include <glad/glad.h>

void Shader::CreateShader(const::std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << path.string() << std::endl;
        m_ProgramID = -1;
        return;
    }

    std::ostringstream stream;
    stream << file.rdbuf();
    std::string shaderSrc = stream.str();

    std::uint32_t shader = glCreateShader(GL_COMPUTE_SHADER);
    const GLchar* cShader = (const GLchar*)shaderSrc.c_str();
    glShaderSource(shader, 1, &cShader, 0);

    glCompileShader(shader);

    int status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        int length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        std::vector<char> log(length);
        glGetShaderInfoLog(shader, length, &length, &log[0]);

        std::cerr << "Error compiling shader: " << log.data() << std::endl;
        glDeleteShader(shader);
        m_ProgramID = -1;
        return;
    }

    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, shader);
    glLinkProgram(m_ProgramID);

    status = 0;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        int length = 0;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);

        std::vector<char> log(length);
        glGetShaderInfoLog(shader, length, &length, &log[0]);

        std::cerr << "Error compiling shader: " << log.data() << std::endl;
        glDeleteProgram(m_ProgramID);
        glDeleteShader(shader);
        m_ProgramID = -1;
        return;
    }

    glDetachShader(m_ProgramID, shader);
}

void Shader::ReloadShader(const::std::filesystem::path& path)
{
    std::cout << "Reloading shaders!" << std::endl;
    CreateShader(path);
    if (m_ProgramID == -1)
    {
        return;
    }

    glDeleteProgram(m_ProgramID);

}
