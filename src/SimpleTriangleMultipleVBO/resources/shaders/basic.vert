#version 430 core

in vec4 vertexPosition;
in vec4 vertexColor;

out VS_OUT
{
    vec4 color;
} vs_out;

void main()
{
    gl_Position = vertexPosition;
    vs_out.color = vertexColor;
}
