#version 430 core

layout (location = 1) in vec4 offset;
layout (location = 2) in vec4 color;

out VS_OUT
{
    vec4 color;
} vs_out;

void main()
{
    const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),
                                     vec4(-0.25, -0.25, 0.5, 1.0),
                                     vec4( 0.25,  0.25, 0.5, 1.0));

    gl_Position  = vertices[gl_VertexID] + offset;
    vs_out.color = color;
}
