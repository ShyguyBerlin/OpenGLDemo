#include <iostream>
#include <glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <helpers/statistics.h>
#include <helpers/shadertools.h>
#include <helpers/CommonObjectWrappers.h>
#include <helpers/loader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace helpers;

// #include <iostream>

void doCamMovement(void);

// define callbacks and functions
void errorCallback( int iError, const char* pcDescription);
void resizeCallback(GLFWwindow* pWindow, int width, int height );
void keyboardCallback( GLFWwindow* pWindow, int iKey, int iScancode, int iAction, int iMods);

// global variables :(
//RenderIf* g_pcRenderer = NULL;
bool camMov[]={false,false,false,false,false,false};

std::vector<float> camPos = {0.f,0.f,-3.f};

int main(int argc, char* argv[])
{

  const unsigned int uiWidth = 1440;
  const unsigned int uiHeight = 900;
  GLFWwindow* pWindow;

  glfwSetErrorCallback(errorCallback);                          // set a callback for GLFW errors

  if(!glfwInit()) return -1;                                    // initialize library

  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4);               // open a OpenGL 4.0 context
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);                 // switch to double buffering
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);                    // allow widow resizing
  glfwWindowHint(GLFW_SAMPLES, 4);                              // multisampling 

  pWindow = glfwCreateWindow( uiWidth, uiHeight, "OpenGL Demo", NULL, NULL); // opens the window
  if(!pWindow)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(pWindow);                              // make the render context current
  gladLoadGL();                                                 // load all the GL commands
  glfwSwapInterval(1);                                          // synchronize with display update


  // set callback functions
  glfwSetWindowSizeCallback(pWindow, resizeCallback);           // set the callback in case of window resizing
  glfwSetKeyCallback(pWindow, keyboardCallback);                // set the callback for key presses

  // load a .obj file
  //std::vector< glm::vec3 > obj_vertices;
  //std::vector< glm::vec2 > obj_uvs;
  //std::vector< glm::vec3 > obj_normals; // Won't be used at the moment.
  //bool res = loadOBJ("stanford-bunny.obj", obj_vertices, obj_uvs, obj_normals);

  //Load vertices

  GLfloat vertices[] = {
        1.f, 1.f, 0.f,//
        0.f, 1.f, 0.f,
        0.,  0.,  0.,
        1.,  1.,  0.,//
        0.,  0.,  0.,
        1.,  0.,  0.,
        1.,  0.,  0.,//
        0.,  0.,  0.,
        0., -1.,  0.,
        1.,  0.,  0.,//
        0., -1.,  0.,
        1., -1.,  0.,
        0.,  1.,  0.,//
       -1.,  1.,  0.,
       -1.,  0.,  0.,
        0.,  1.,  0.,//
       -1.,  0.,  0.,
        0.,  0.,  0.,
        0.,  0.,  0.,//
       -1.,  0.,  0.,
       -1., -1.,  0.,
        0.,  0.,  0.,//
       -1., -1.,  0.,
        0., -1.,  0.

  };

  const GLfloat colors[6][3] = {
    {  1.0,  0.0,  0.0  }, /* Red */
    {  0.0,  0.0,  1.0  }, /* Blue */
    {  0.0,  1.0,  0.0  }, /* Green */
    {  1.0,  0.0,  0.0  }, /* Red */
    {  0.0,  1.0,  0.0  }, /* Green */
    {  0.0,  0.0,  1.0  } }; /* Blue */

  Mesh3D mesh(8*3);

  mesh.set_positions(vertices);

  // Load Shader

  GLuint skyboxShader;
  make_shader_program(&skyboxShader,"background_vertex_shader.glsl","background_fragment_shader.glsl");
  mesh.set_shader(skyboxShader);

  // Imported Mesh

  std::vector <glm::vec3> vertices_dw;
  std::vector <glm::vec2> uv_dw;
  std::vector <glm::vec3> normals_dw;

  loadOBJ("asset/Driftwood.obj",vertices_dw,uv_dw,normals_dw);
  Mesh3D driftwood(vertices_dw.size());
  driftwood.set_positions(reinterpret_cast<GLfloat*>(vertices_dw.data()));
  driftwood.set_normals(reinterpret_cast<GLfloat*>(normals_dw.data()));
  driftwood.set_uv(reinterpret_cast<GLfloat*>(uv_dw.data()));

  GLuint basicShader;
  make_shader_program(&basicShader,"standard_vertex_shader.glsl","standard_texture_fragment_shader.glsl");
  driftwood.set_shader(basicShader);

  // https://learnopengl.com/Getting-started/Textures
  int width, height, nrChannels;
  unsigned char *image_data = stbi_load("asset/Driftwood.png", &width, &height, &nrChannels, 0); 
  if(!image_data){
    printf("error loading image data!\n");
  }
  GLuint material_texture;
  glGenTextures(1,&material_texture);
  
  glBindTexture(GL_TEXTURE_2D,material_texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,image_data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(image_data);

  GLint dw_timeLocation = glGetUniformLocation(basicShader, "time");
  GLint dw_camLocation = glGetUniformLocation(basicShader, "camPos");
  GLint dw_lightLocation = glGetUniformLocation(basicShader, "light_src");
  GLint dw_specularFactorLocation = glGetUniformLocation(basicShader, "specular");
  GLint dw_specularColorLocation = glGetUniformLocation(basicShader, "specular_color");
  GLint dw_ambientColorLocation = glGetUniformLocation(basicShader, "ambient_color");
  GLint dw_textureLocation = glGetUniformLocation(basicShader, "albedoTexture");

  // water plane

  TerrainObject water_plane(500,500,0.1f);
  GLuint waterShader;
  make_shader_program(&waterShader,"terrain_vertex_shader.glsl","terrain_fragment_shader.glsl");
  water_plane.mesh.set_shader(waterShader);

  GLint timeLocation = glGetUniformLocation(waterShader, "time");
  GLint camLocation = glGetUniformLocation(waterShader, "camPos");
  GLint lightLocation = glGetUniformLocation(waterShader, "light_src");
  GLint specularFactorLocation = glGetUniformLocation(waterShader, "specular");
  GLint specularColorLocation = glGetUniformLocation(waterShader, "specular_color");
  GLint ambientColorLocation = glGetUniformLocation(waterShader, "ambient_color");


  glEnable( GL_BLEND );
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
  //glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // main loop for rendering and message parsing
  while (!glfwWindowShouldClose(pWindow))                       // Loop until the user closes the window
  {
    float time=  glfwGetTime();

    // g_pcRenderer->render();                                     // render the triangle
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mesh.load_shader();
    mesh.draw();
    
    water_plane.mesh.load_shader();
    glUniform1f(timeLocation,time);
    glUniform3f(camLocation,camPos[0],camPos[1],camPos[2]);
    glUniform3f(lightLocation,4.f,6.f,30.f+sin(time/4.f)*30.f);//+time*8.f);
    glUniform1f(specularFactorLocation,128.f);
    glUniform3f(specularColorLocation,0.8f,0.7f,0.3f);
    glUniform3f(ambientColorLocation,0.005f,0.01f,0.02f);
    water_plane.draw();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,material_texture);
    driftwood.load_shader();
    glUniform1f(dw_timeLocation,time);
    glUniform3f(dw_camLocation,camPos[0],camPos[1],camPos[2]);
    glUniform3f(dw_lightLocation,4.f,6.f,20.f+sin(time/4.f)*30.f);//+time*8.f);
    glUniform1f(dw_specularFactorLocation,1.f);
    glUniform3f(dw_specularColorLocation,1.0f,1.0f,1.0f);
    glUniform3f(dw_ambientColorLocation,0.0f,0.0f,0.0f);
    glUniform1i(dw_textureLocation,0);
    driftwood.draw();

    glFlush();                                                  // process all comands in OpenGL pipeline

    fps_counter();

    glfwSwapBuffers(pWindow);                                   // swap front and back buffers

    glfwPollEvents();                                           // pull the process events
    doCamMovement();                                        
  }

  // free renderer
  // g_pcRenderer->uninitGL();
  // delete g_pcRenderer;
  glfwDestroyWindow(pWindow);

  glfwTerminate();                                              // end glfw library

  return 0;
}


void errorCallback(int iError, const char* pcDescription)
{
  std::cerr << pcDescription << std::endl;
}



void resizeCallback(GLFWwindow* pWindow, int width, int height )
{
  glViewport(0,0,width,height);
}

void doCamMovement(){
  glm::vec3 camVec[] = {glm::vec3(0.0,0.1,0.0),glm::vec3(0.0,-0.1,0.0),glm::vec3(0.1,0.0,0.0),glm::vec3(-0.1,0.0,0.0),glm::vec3(0.0,0.0,0.1),glm::vec3(0.0,0.0,-0.1)};

  for(int i=0;i<6;i++){
    if(camMov[i]){
      camPos[0]+=camVec[i].x;
      camPos[1]+=camVec[i].y;
      camPos[2]+=camVec[i].z;
    }
  }
}

void keyboardCallback( GLFWwindow* pWindow, int iKey, int iScancode, int iAction, int iMods)
{
  bool is_pressed=true;
  if(iAction==GLFW_RELEASE){is_pressed=false;}

  switch (iKey)
  {
  case GLFW_KEY_W:
    camMov[4]=is_pressed;
    break;

  case GLFW_KEY_A:
    camMov[3]=is_pressed;
    break;

  case GLFW_KEY_S:
   camMov[5]=is_pressed;
    break;

  case GLFW_KEY_D:
    camMov[2]=is_pressed;
    
    break;

  case GLFW_KEY_SPACE:
    camMov[0]=is_pressed;
    break;

  case GLFW_KEY_LEFT_SHIFT:
    camMov[1]=is_pressed;
    break;
  default:
    break;
  }

}