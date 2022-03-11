#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertColor_in;
layout (location = 2) in vec2 uv_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelViewTransform;
uniform mat4 projectionTransform;
uniform mat3 normalTransform;
uniform vec3 lightPosition;
uniform float materialAmbient;
uniform float materialDiffuse;
uniform float materialSpecular;
uniform float materialSpecularExponent;
uniform vec3 lightColor;

// Specify the output of the vertex stage
out vec3 vertColor;
out vec2 uv;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = projectionTransform * modelViewTransform * vec4(vertCoordinates_in, 1.0F);
    vec3 normal = normalize(normalTransform * vertColor_in);
    vec3 light = vec3(modelViewTransform * vec4(lightPosition, 1.));
    vec3 light_dir = normalize(light - gl_Position.xyz);
    vec3 reflect_dir = normalize(2 * dot(light_dir, normal) * normal - light_dir);
    vec3 camera_dir = vec3(0.,0.,1.);

    float color = materialAmbient +
            materialDiffuse * dot(light_dir, normal) +
            materialSpecular * dot(reflect_dir, camera_dir);

    vertColor = color * lightColor;
    uv = uv_in;

    if(color != color) vertColor = vec3(0. ,0.,1.);
}
