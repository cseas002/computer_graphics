#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertColor_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelTransform;
uniform mat4 projectTransform;

// Specify the output of the vertex stage
out vec3 vertColor;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
<<<<<<< HEAD
=======
    // Currently without any transformation
>>>>>>> 4eb9ba93318fd2f4e8f41e718f4317fcb251e8fd
    gl_Position = projectTransform * modelTransform * vec4(vertCoordinates_in, 1.0F);
    vertColor = vertColor_in;
}
