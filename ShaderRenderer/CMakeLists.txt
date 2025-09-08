set(SOURCE_DIR "src")

set(SOURCES
    src/Main.cpp
    src/Renderer.cpp
    src/Shader.cpp
)

add_executable(ShaderRenderer ${SOURCES})

target_link_libraries(ShaderRenderer PRIVATE
    glad
    glfw
    OpenGL::GL
    glm
    stb_image
)

add_library(glad STATIC
    vendor/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    vendor/glad/include
)

add_library(stb_image STATIC
    vendor/stb/stb_image.cpp
)
target_include_directories(stb_image PUBLIC
    vendor/stb
)

target_include_directories(ShaderRenderer PRIVATE 
    .
)
