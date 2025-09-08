#version 460 core

layout (rgba32f, binding = 0) uniform writeonly image2D outImg;

layout (local_size_x = 16, local_size_y = 16) in;

uniform float time;

//This is an example shader. Original shader came from:
//http://glslsandbox.com/e#23237.0
//
//Code from: https://www.shadertoy.com/view/llS3RK

//Calculate the squared length of a vector
float length2(vec2 p){
    return dot(p,p);
}

//Generate some noise to scatter points.
float noise(vec2 p){
	return fract(sin(fract(sin(p.x) * (43.13311)) + p.y) * 31.0011);
}

float worley(vec2 p) {
    //Set our distance to infinity
	float d = 1e30;
    //For the 9 surrounding grid points
	for (int xo = -1; xo <= 1; ++xo) {
		for (int yo = -1; yo <= 1; ++yo) {
            //Floor our vec2 and add an offset to create our point
			vec2 tp = floor(p) + vec2(xo, yo);
            //Calculate the minimum distance for this grid point
            //Mix in the noise value too!
			d = min(d, length2(p - tp - noise(tp)));
		}
	}
	return 3.0*exp(-4.0*abs(2.5*d - 1.0));
}

float fworley(vec2 p) {
    //Stack noise layers 
	return sqrt(sqrt(sqrt(
		worley(p*5.0 + 0.05*time) *
		sqrt(worley(p * 50.0 + 0.12 + -0.1*time)) *
		sqrt(sqrt(worley(p * -10.0 + 0.03*time))))));
}

// Edit Shader Main code here, do not delete function as its required in the main function.
vec4 shaderCode(ivec2 texCoord)
{
    vec2 iResolution = vec2(1280, 720);
    vec2 uv = texCoord.xy / iResolution.xy;
    //Calculate an intensity
    float t = fworley(uv * iResolution.xy / 1500.0);
    //Add some gradient
    t*=exp(-length2(abs(0.7*uv - 1.0)));	
    //Make it blue!
    return vec4(t * vec3(0.1, 1.1*t, pow(t, 0.5-t)), 1.0);
}


// ----------------- DO NOT DELETE ---------------
void main()
{
    ivec2 texCoord = ivec2(gl_GlobalInvocationID.xy);
    vec4 O = shaderCode(texCoord);
    imageStore(outImg, texCoord, O);
}