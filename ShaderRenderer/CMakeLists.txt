set(SOURCE_DIR "src")

set(SOURCES
    src/Main.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/Renderer.h
    src/Shader.h
    vendor/stb/stb_image.h
    vendor/stb/stb_image.cpp
    vendor/glad/src/glad.c
)

add_executable(ShaderRenderer ${SOURCES})

target_link_libraries(ShaderRenderer
    PRIVATE
    glad
    glfw
    OpenGL::GL
    glm
    stb_image
)

target_include_directories(ShaderRenderer PRIVATE 
    vendor/stb
    vendor/glad/include
)
