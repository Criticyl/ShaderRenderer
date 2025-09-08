set(SOURCE_DIR "src")

set(SOURCES
    src/Main.cpp
    vendor/stb/stb_image.h
    vendor/stb/stb_image.cpp
)

add_executable(ShaderRenderer ${SOURCES})

target_link_libraries(ShaderRenderer glfw)
target_link_libraries(ShaderRenderer glad)
target_link_libraries(ShaderRenderer glm)

target_include_directories(ShaderRenderer PRIVATE vendor/stb)