#version 330 core

in vec3 interpolatedColor;
out vec4 rgbaColor;
void main()
{
    rgbaColor = vec4(interpolatedColor, 1); // a = 1 (opaque) (a = alpha = transparency)
}
