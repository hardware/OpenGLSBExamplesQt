#version 430 core

in vec3 vertexPosition;

out VS_OUT
{
    vec4 color;
} vs_out;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * vec4(vertexPosition, 1.0);
    vs_out.color = vec4(vertexPosition, 1.0) * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}
