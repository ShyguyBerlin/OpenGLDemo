#version 420 core

layout(location = 0) in vec3 in_Position;
//layout(location = 1) in vec3 in_Color;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 f_Color;

float RENDER_DISTANCE=40.;

void main(void)
{

    vec3 camPos=vec3(0.,0.,-10.);

    // translate by cam position

    gl_Position = vec4(in_Position - camPos, 1.0);
    float ratio_width=16./10.;
    float cam_dist=1.;

    gl_Position = vec4(ratio_width*gl_Position.x/gl_Position.z/cam_dist,gl_Position.y/gl_Position.z/cam_dist,gl_Position.z/(RENDER_DISTANCE/2.),1);
    gl_Position.z-=1;
    // if trying to do rotation, rotate vertex here

    fragPos = gl_Position.xyz;
    // gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
    f_Color = vec3(gl_Position.x,gl_Position.y,0.8);
}