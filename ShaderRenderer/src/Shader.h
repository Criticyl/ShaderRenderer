#pragma once

#include <filesystem>

class Shader
{
public:
    void CreateShader(const::std::filesystem::path& path);
    void ReloadShader(const::std::filesystem::path& path);

    void uniformFloat(std::string id, float value);

    inline const std::uint32_t& GetProgram() { return m_ProgramID; }
private:
    std::uint32_t m_ProgramID;
};
