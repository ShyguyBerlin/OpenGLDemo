#version 420 core
layout(location = 0) in vec3 worldPos;
layout(location = 1) in vec3 screenPos;
layout(location = 2) in vec3 color;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec3 camVec;


out vec4 FragColor;
void main(void)
{
  float light_fac=dot(normalize(camVec),normal);
  vec3 col=color;
  //if(screenPos.x<0.3){col.xyz=vec3(1.0,1.0,1.0);}
  col*=light_fac;
  FragColor = vec4(col,0.5f*light_fac);
}