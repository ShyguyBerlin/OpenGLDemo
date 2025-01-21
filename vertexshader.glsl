#version 460 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Color;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 f_Color;
void main(void)
{
    fragPos = in_Position;
    gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
    f_Color = in_Color;
};