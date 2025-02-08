#version 420 core
layout(location = 0) in vec3 worldPos;
layout(location = 1) in vec3 screenPos;
layout(location = 2) in vec3 color;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec3 camVec;

uniform vec3 light_src;

//uniform vec3 diffuse_color; // also called "albedo" lmao // this is the color vec3
uniform vec3 specular_color;
uniform vec3 ambient_color;

uniform float specular;

out vec4 FragColor;

vec3 wave_dir=vec3(1.1f,10.f,0.4f);

void main(void)
{

  vec3 albedo=color;

  float wave_f=max(pow(1.f-(normal.y-0.8f)*5.f,1.f),0.f)*0.5f;

  //albedo=(1.f-wave_f)*albedo+(wave_f*vec3(1.f,1.f,1.f));

  float diffuse_f = dot(normalize(light_src-worldPos),normal);
  vec3 light_vec=worldPos-light_src;
  vec3 local_camVec = camVec-worldPos;

  // blinn-phong model
  /*vec3 lightcam = normalize((-light_vec)+local_camVec);
  float specular_f = max(pow(dot(lightcam,normal),specular),0.f)*20.;*/ 

  // phong model
  float specular_f = max(pow(dot(normalize(light_vec-2*dot(light_vec,normal)*normal),normalize(camVec-worldPos)),specular),0.f)*(specular+2.f)/(3.14159*2.f);
  float ambient_f = 1.0;

  vec3 resulting_color=(albedo*diffuse_f) + (specular_color*specular_f) + (ambient_color*ambient_f);

  FragColor = vec4(resulting_color,1.0f);//0.5f*light_fac);
}