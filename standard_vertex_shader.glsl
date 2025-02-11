#version 420 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_Color;
layout(location = 2) in vec3 in_Normal;
layout(location = 3) in vec2 in_uv;

layout(location = 0) out vec3 worldPos;
layout(location = 1) out vec3 screenPos;
layout(location = 3) out vec3 normal;
layout(location = 4) out vec3 camVec;
layout(location = 5) out vec2 uv;

uniform float screen_ratio;

uniform float time;
uniform vec3 camPos;


float RENDER_DISTANCE=400.;
float NOISE_GRAIN=0.4f;
float NOISE_HEIGHT=1.1f;

void main(void)
{
    worldPos=in_Position;
    normal=in_Normal;
    uv=vec2(in_uv.x,-in_uv.y);
    // World Space transformation on gl_Position

    mat3 rot_y = mat3(
        cos(time),0.f,sin(time),
        0.f,1.f,0.f,
        -sin(time),0.f,cos(time)
    );

    worldPos=rot_y*worldPos; 
    normal=rot_y*normal;

    worldPos.y+=-5.5f;
    worldPos.z+=sin(time)*2.f;

    // translate by cam position
    camVec=camPos - worldPos;
    gl_Position = vec4(worldPos - camPos, 1.0);
    float ratio_width=21./9.;
    float cam_dist=1.;

    if(gl_Position.z<0.0f){
        //gl_Position.z=0.01f;
    }else{
        gl_Position = vec4(gl_Position.x/gl_Position.z/cam_dist/screen_ratio,gl_Position.y/gl_Position.z/cam_dist,gl_Position.z/(RENDER_DISTANCE/2.f),1);
    }
    gl_Position.z-=1;
    
    // if trying to do rotation, rotate vertex here

    screenPos=gl_Position.xyz;
    //gl_Position=vec4(uv.x,uv.y,gl_Position.z,1.0f);
}