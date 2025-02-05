#version 420 core
layout(location = 0) in vec3 worldPos;
layout(location = 1) in vec3 screenPos;
layout(location = 2) in vec3 color;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec3 camVec;

uniform vec3 light_src;
uniform float specular;
uniform float ambient;

out vec4 FragColor;
void main(void)
{
  float diffuse_f = dot(normalize(light_src-worldPos),normal);
  vec3 light_vec=-(light_src-worldPos);
  float specular_f = max(pow(dot(normalize(light_vec-2*dot(light_vec,normal)*normal),normalize(camVec-worldPos)),specular),0.f)*20.;
  float ambient_f= 0.f;ambient;

  float light_fac=diffuse_f+ambient_f+specular_f;
  vec3 col=color;
  //if(screenPos.x<0.3){col.xyz=vec3(1.0,1.0,1.0);}
  col*=light_fac;
  FragColor = vec4(col,1.0f);//0.5f*light_fac);
}