# Shader Renderer
A simple program that renders shader programs using a compute shader. (With the help from TheCherno's video).

Press R to reload shaders.

## Building the project

Build the project using CMake and following these steps:

1. Clone the repository:  
```
git clone https://github.com/Criticyl/ShaderRenderer.git
```
2. Navigate to the root directory
3. Create a build directory and navigate it
```
mkdir build  
cd build
```
4. Run CMake with the configuration you like (Example using Visual Studio 2022)
```
cmake .. -G "Visual Studio 17 2022"
```
5. Build the project:
```
cmakme --build
```

This should generate the executable inside the `bin` folder.

## External Dependencies

The project uses the following external dependencies:

* **stb_image**: Header library for loading images.
* **OpenGL**: The graphics library used for rendering
* **GLFW**: Library for creating window contexts using OpenGL
* **Glad**: Library for more Modern OpenGL functions
* **GLM**: C++ Maths library.

# Future Plans

Planning on adding a GUI to it (With ImGui) so that shader files can be imported and exported.
Eventually I do want to make this some kind of tool similar to Shadertoy where you can just mess around with making shaders.

I also plan on adding a lot more uniforms to this, currently the only uniform added is time.
