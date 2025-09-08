#version 460 core

layout (rgba32f, binding = 0) uniform writeonly image2D outImg;

layout (local_size_x = 16, local_size_y = 16) in;

// Shader Code goes here vvv
vec4 shaderCode()
{
    vec4 colour = vec4(1.0, 0.0, 1.0, 1.0);
    return colour;
}

void main()
{
    ivec2 texCoord = ivec2(gl_GlobalInvocationID.xy);
    vec4 O = shaderCode();
    imageStore(outImg, texCoord, O);
}