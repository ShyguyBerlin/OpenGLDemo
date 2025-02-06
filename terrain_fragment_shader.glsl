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

vec3 wave_dir=vec3(1.1f,10.f,0.4f);

void main(void)
{
  float diffuse_f = dot(normalize(light_src-worldPos),normal);
  vec3 light_vec=worldPos-light_src;
  vec3 local_camVec = camVec-worldPos;
  /*vec3 lightcam = normalize((-light_vec)+local_camVec);
  float specular_f = max(pow(dot(lightcam,normal),specular),0.f)*20.;*/ // blinn-phong model
  float specular_f = max(pow(dot(normalize(light_vec-2*dot(light_vec,normal)*normal),normalize(camVec-worldPos)),specular),0.f)*(specular+2.f)/(3.14159*2.f); // phong model
  float ambient_f= ambient;

  float light_fac=diffuse_f+ambient_f+specular_f;


  vec3 col=color;

  float wave_f=max(pow(1.f-(normal.y-0.8f)*5.f,1.f),0.f);

  col=(1.f-wave_f)*col+(wave_f*vec3(1.f,1.f,1.f));

  //if(screenPos.x<0.3){col.xyz=vec3(1.0,1.0,1.0);}
  col=col*light_fac;
  FragColor = vec4(col,1.0f);//0.5f*light_fac);
}