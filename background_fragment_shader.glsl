#version 420 core
layout(location= 0) in vec3 fragPos;
layout(location= 1) in vec3 f_Color;
out vec4 FragColor;

vec3 get_sky_color(vec2 screen_uv){
  vec3 HorizonColor=vec3(0.7f,0.4f,0.1f);
  vec3 SkyColor= vec3(0.034f,0.13f,0.15f);

  return mix(HorizonColor,SkyColor,(pow(pow(screen_uv.y+1.8f,2.f)+pow(abs(screen_uv.x)/2.f,2.f),0.5f))/2.f);
}

void main(void)
{

  FragColor = vec4(get_sky_color(fragPos.xy),1.f);
}