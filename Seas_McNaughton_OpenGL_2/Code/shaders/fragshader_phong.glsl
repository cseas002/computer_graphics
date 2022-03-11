#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertColor;
in vec4 position;
in vec2 uv;

// Specify the Uniforms of the fragment shaders
uniform mat4 modelViewTransform;
uniform vec3 lightPosition;
uniform float materialAmbient;
uniform float materialDiffuse;
uniform float materialSpecular;
uniform float materialSpecularExponent;
uniform vec3 lightColor;
uniform sampler2D samplerUniform;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    vec3 normal = normalize(vertColor);
    vec3 light = vec3(modelViewTransform * vec4(lightPosition, 1.));
    vec3 light_dir = normalize(light - position.xyz);
    vec3 reflect_dir = normalize(2 * dot(light_dir, normal) * normal - light_dir);
    vec3 camera_dir = vec3(0.,0.,1.);

    float color = materialAmbient +
            materialDiffuse * dot(light_dir, normal) +
            materialSpecular * dot(reflect_dir, camera_dir);

    vec4 textureColor = texture(samplerUniform, uv);
    fColor = vec4(color * lightColor, 1.0F) * textureColor * 3.;
}
