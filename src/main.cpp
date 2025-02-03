#include <iostream>
#include <glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#include <helpers/shadertools.h>
#include <helpers/CommonObjectWrappers.h>

using namespace helpers;

// #include <iostream>

// define callbacks and functions
void errorCallback( int iError, const char* pcDescription);
//void resizeCallback(GLFWwindow* pWindow, int width, int height );
//void keyboardCallback( GLFWwindow* pWindow, int iKey, int iScancode, int iAction, int iMods);

// global variables :(
//RenderIf* g_pcRenderer = NULL;

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
  // glfwSetWindowSizeCallback(pWindow, resizeCallback);           // set the callback in case of window resizing
  // glfwSetKeyCallback(pWindow, keyboardCallback);                // set the callback for key presses


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

  GLuint basicShader;
  make_shader_program(&basicShader,"vertexshader.glsl","fragshader.frag");
  mesh.set_shader(basicShader);

  TerrainObject water_plane(125,125,0.24f);
  GLuint waterShader;
  make_shader_program(&waterShader,"terrain_vertex_shader.glsl","terrain_fragment_shader.glsl");
  water_plane.mesh.set_shader(waterShader);

  GLint timeLocation = glGetUniformLocation(waterShader, "time");

  glEnable( GL_BLEND );
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

  
  // main loop for rendering and message parsing
  while (!glfwWindowShouldClose(pWindow))                       // Loop until the user closes the window
  {
    float time=  glfwGetTime();
    glUniform1f(timeLocation,time);

    // g_pcRenderer->render();                                     // render the triangle
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mesh.draw();
    water_plane.draw();
    glFlush();                                                  // process all comands in OpenGL pipeline

    glfwSwapBuffers(pWindow);                                   // swap front and back buffers

    glfwPollEvents();                                           // pull the process events
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


/*
void resizeCallback(GLFWwindow* pWindow, int width, int height )
{
  g_pcRenderer->setWindowSize( width, height );
}
*/

/*
void keyboardCallback( GLFWwindow* pWindow, int iKey, int iScancode, int iAction, int iMods)
{
  switch (iKey)
  {
  case GLFW_KEY_Q:
    glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
    break;

  case GLFW_KEY_K:
    g_pcRenderer->rotY( 2.0f );
    break;

  case GLFW_KEY_L:
    g_pcRenderer->rotY( -2.0f );
    break;

  case GLFW_KEY_A:
    g_pcRenderer->rotX(2.0f);
    break;

  case GLFW_KEY_Z:
    g_pcRenderer->rotX(-2.0f);
    break;

  default:
    g_pcRenderer->keyPressed(iKey);
    break;
  }

  g_pcRenderer->renderCamera();
}*/