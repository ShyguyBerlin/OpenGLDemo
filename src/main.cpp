#include <iostream>
#include <glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <fstream>

#include <helpers/VBOhelper.h>
#include <helpers/shadertools.h>

using namespace helpers;

// #include <iostream>

// define callbacks and functions
void errorCallback( int iError, const char* pcDescription);
//void resizeCallback(GLFWwindow* pWindow, int width, int height );
//void keyboardCallback( GLFWwindow* pWindow, int iKey, int iScancode, int iAction, int iMods);

char* filetobuf(const char *file)
{
    char *buffer;
    std::ifstream t;
    int length;
    t.open(file);      // open input file
    t.seekg(0, std::ios::end);    // go to the end
    length = t.tellg();           // report location (this is the length)
    t.seekg(0, std::ios::beg);    // go back to the beginning
    buffer = (char*)malloc(length+1);    // allocate memory for a buffer of appropriate dimension
    t.read(buffer, length);       // read the whole file into the buffer
    buffer[length]='\0';
    t.close();
    return buffer;    
}

// global variables :(
//RenderIf* g_pcRenderer = NULL;

int main(int argc, char* argv[])
{

  const unsigned int uiWidth = 800;
  const unsigned int uiHeight = 600;
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

  GLuint VertexArrayID;
  GLuint ColorArrayID;
  GLuint VertexOjectID;



  glGenBuffers(1, &VertexArrayID);
  glBindBuffer(GL_ARRAY_BUFFER, VertexArrayID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  /* Specify that our coordinate data is going into attribute index 0, and contains two floats per vertex */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  /* Enable attribute index 0 as being used */
  glEnableVertexAttribArray(0);

  //glGenBuffers(1, &ColorArrayID);
  //glBindBuffer(GL_ARRAY_BUFFER, ColorArrayID);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  /* Specify that our coordinate data is going into attribute index 1, and contains two floats per vertex */
  //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  /* Enable attribute index 0 as being used */
  //glEnableVertexAttribArray(1);

  // Load Shader

  const char *vertfname ="vertexshader.glsl";
  char *vertexShaderSource = filetobuf(vertfname);
  unsigned int vertexShader;
  create_and_compile_shader(&vertexShader,GL_VERTEX_SHADER,vertexShaderSource);

  const char *fragfname ="fragshader.frag";
  char *fragShaderSource = filetobuf(fragfname);
  unsigned int fragShader;
  create_and_compile_shader(&fragShader,GL_FRAGMENT_SHADER,fragShaderSource);

  // Linking the shaders

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragShader);

  glBindAttribLocation(shaderProgram, 0, "in_Position");
  //glBindAttribLocation(shaderProgram, 1, "in_Color");

  glLinkProgram(shaderProgram);

  print_shader_program_status(&shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  glClearColor(0.0, 0.3, 0.3, 1.0);



  // main loop for rendering and message parsing
  while (!glfwWindowShouldClose(pWindow))                       // Loop until the user closes the window
  {
    float time= (float)clock() / CLOCKS_PER_SEC;

    // g_pcRenderer->render();                                     // render the triangle
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VertexOjectID);
    glDrawArrays(GL_TRIANGLES, 0, 3*8);

    glFlush();                                                  // process all comands in OpenGL pipeline

    glfwSwapBuffers(pWindow);                                   // swap front and back buffers

    glfwWaitEvents();                                           // pull the process events
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