#version 460 core
in vec3 fragPos;
in  vec3 f_Color;
out vec4 FragColor;
void main(void)
{
  vec3 col=f_Color;
  if(fragPos.x<0.3){col.xyz=vec3(1.0,1.0,1.0);}
  FragColor = vec4(col,1.0f);
}