#version 460 core
in vec3 in_Position;
in vec3 in_Color;
out vec3 fragPos;
out vec3 f_Color;
void main(void)
{
    fragPos = in_Position;
    gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
    f_Color = in_Color;
};