#version 420 core
layout(location= 0) in vec3 fragPos;
layout(location= 1) in vec3 f_Color;
out vec4 FragColor;
void main(void)
{
  vec3 HorizonColor=vec3(0.7f,0.4f,0.1f);
  vec3 SkyColor= vec3(0.05f,0.2f,0.3f);
  FragColor = vec4(mix(HorizonColor,SkyColor,(pow(pow(fragPos.y+1.5f,2.f)+pow(abs(fragPos.x)/2.f,2.f),0.5f))/2.f),1.f);
}