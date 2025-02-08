#version 420 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Color;
layout(location = 2) in vec3 in_Normal;

layout(location = 0) out vec3 worldPos;
layout(location = 1) out vec3 screenPos;
layout(location = 2) out vec3 color;
layout(location = 3) out vec3 normal;
layout(location = 4) out vec3 camVec;

uniform float time;
uniform vec3 camPos;

float RENDER_DISTANCE=40.;
float NOISE_GRAIN=0.4f;
float NOISE_HEIGHT=1.1f;

//http://byteblacksmith.com/improvements-to-the-canonical-one-liner-glsl-rand-for-opengl-es-2-0/
highp float rand(vec2 co)
{
    highp float a = 12.9898;
    highp float b = 78.233;
    highp float c = 43758.5453;
    highp float dt= dot(co.xy ,vec2(a,b));
    highp float sn= mod(dt,3.14);
    return fract(sin(sn) * c);
}

float fnoise(vec2 p){
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);
	
	float res = mix(
		mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
		mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return res;
}

// AI generated (chatgpt)
float noise(vec2 p) {
    float sum = 0.0;
    float amp = 0.5;
    float freq = 1.0;

    for (int i = 0; i < 8; i++) {
        sum += amp * fnoise(p * freq);
        amp *= 0.5;
        freq *= 1.5;
    }
    return sum;
}

/*float noise(vec2 seed)
{
    float x = (seed.x / 3.14159 + 4) * (seed.y / 13 + 4) * ((fract(time) + 1) * 10);
    return mod((mod(x, 13) + 1) * (mod(x, 123) + 1), 0.01) - 0.005;
}*/

float calculate_y_deformation(vec2 p){
    float height = noise(vec2(p.x*NOISE_GRAIN+time*NOISE_GRAIN*1.1,p.y*NOISE_GRAIN-time*NOISE_GRAIN*0.4));
    // Trying to add some steepness to waves
    //height = height + pow(max(0,height-0.2f),8)*64.;
    return NOISE_HEIGHT*height;
}

vec3 calculateNormal(vec3 p){
    float offset=0.005f;

    vec3 gradientX = vec3(offset*2.f,calculate_y_deformation(vec2(p.x+offset,p.z))-calculate_y_deformation(vec2(p.x-offset,p.z)),0.f);
    vec3 gradientZ = vec3(0.f,calculate_y_deformation(vec2(p.x,p.z+offset))-calculate_y_deformation(vec2(p.x,p.z-offset)),offset*2.f);
    return normalize(-cross(gradientX,gradientZ));
}

void main(void)
{
    worldPos=in_Position;
    normal=in_Normal;

    // World Space transformation on gl_Position

    worldPos.y-=3.f;
    worldPos.y+=calculate_y_deformation(worldPos.xz);
    normal=calculateNormal(worldPos);

    //worldPos=vec3(worldPos.x,worldPos.z,-worldPos.y);
    //normal=vec3(normal.x,normal.z,-normal.y);

    worldPos.y+=-3.f;
    worldPos.z+=16.f;

    // translate by cam position
    camVec=camPos - worldPos;
    gl_Position = vec4(worldPos - camPos, 1.0);
    float ratio_width=16./10.;
    float cam_dist=1.;

    gl_Position = vec4(gl_Position.x/gl_Position.z/cam_dist/ratio_width,gl_Position.y/gl_Position.z/cam_dist,gl_Position.z/(RENDER_DISTANCE/2.f),1);
    gl_Position.z-=1;
    
    // if trying to do rotation, rotate vertex here

    screenPos=gl_Position.xyz;
    color = vec3(0.1f,0.6f,0.8f);
}