#include <iostream>
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// #include <iostream>

// define callbacks and functions
void errorCallback( int iError, const char* pcDescription);
//void resizeCallback(GLFWwindow* pWindow, int width, int height );
//void keyboardCallback( GLFWwindow* pWindow, int iKey, int iScancode, int iAction, int iMods);

// global variables :(
//RenderIf* g_pcRenderer = NULL;

int main(int argc, char* argv[])
{
  const unsigned int uiWidth = 800;
  const unsigned int uiHeight = 600;
  GLFWwindow* pWindow;

  glfwSetErrorCallback(errorCallback);                          // set a callback for GLFW errors

  if(!glfwInit()) return -1;                                    // initialize library

  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4);               // open a OpenGL 3.2 context
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);                 // switch to double buffering
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);                    // allow widow resizing
  glfwWindowHint(GLFW_SAMPLES, 4);                              // multisampling 

  pWindow = glfwCreateWindow( uiWidth, uiHeight, "OpenGL example", NULL, NULL); // opens the window
  if(!pWindow)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(pWindow);                              // make the render context current
  gladLoadGL();                                                 // load all the GL commands
  glfwSwapInterval(1);                                          // synchronize with display update


  // setup the renderer
  // g_pcRenderer = new RenderTriangle;
  // g_pcRenderer->setWindowSize(uiWidth, uiHeight);
  // g_pcRenderer->initGL();                                       // initialize the scene and OpenGL state

  // set callback functions
  // glfwSetWindowSizeCallback(pWindow, resizeCallback);           // set the callback in case of window resizing
  // glfwSetKeyCallback(pWindow, keyboardCallback);                // set the callback for key presses

  std::cout << "press q to quit" << std::endl;
  std::cout << "press k to turn left" << std::endl;
  std::cout << "press l to turn right" << std::endl;
  std::cout << "press a to turn forward" << std::endl;
  std::cout << "press y to turn backward" << std::endl;


  // main loop for rendering and message parsing
  while (!glfwWindowShouldClose(pWindow))                       // Loop until the user closes the window
  {
    // g_pcRenderer->render();                                     // render the triangle

    glFlush();                                                  // process all comands in OpenGL pipeline

    glfwSwapBuffers(pWindow);                                   // swap front and back buffers

    glfwWaitEvents();                                           // pull the process events
  }

  // free renderer
  // g_pcRenderer->uninitGL();
  // delete g_pcRenderer;

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