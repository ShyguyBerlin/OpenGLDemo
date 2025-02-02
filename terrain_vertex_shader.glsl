#version 420 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Color;
layout(location = 2) in vec3 in_Normal;

layout(location = 0) out vec3 worldPos;
layout(location = 1) out vec3 screenPos;
layout(location = 2) out vec3 color;
layout(location = 3) out vec3 normal;
layout(location = 4) out vec3 camVec;

float RENDER_DISTANCE=40.;

void main(void)
{
    worldPos=in_Position;
    normal=in_Normal;
    vec3 camPos=vec3(0.,0.,-3.);

    // World Space transformation on gl_Position

    worldPos.y-=3.f;
    worldPos.y+=0.5f*sin(worldPos.x*0.89f+worldPos.z*4.1f);


    // translate by cam position
    camVec=camPos - worldPos;
    gl_Position = vec4(worldPos - camPos, 1.0);
    float ratio_width=16./10.;
    float cam_dist=1.;

    gl_Position = vec4(ratio_width*gl_Position.x/gl_Position.z/cam_dist,gl_Position.y/gl_Position.z/cam_dist,gl_Position.z/(RENDER_DISTANCE/2.),1);
    gl_Position.z-=1;
    
    // if trying to do rotation, rotate vertex here

    screenPos=gl_Position.xyz;
    color = vec3(gl_Position.x,gl_Position.y,0.8);
}