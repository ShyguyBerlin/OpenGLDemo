#include <helpers/VBOhelper.h>
//#include <ostream>
#include <glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>

namespace helpers{

VBOhelper::VBOhelper(size_t attributes) : VA_ids(attributes){
    glGenVertexArrays(1, &VBO_id);
    
};

void VBOhelper::bind(){
    glBindVertexArray(VBO_id);
}

void VBOhelper::add_attributes_float(GLfloat* att_array, size_t size, int idx, int dim){
  bind();
  glGenBuffers(1, &VA_ids[idx]);
  glBindBuffer(GL_ARRAY_BUFFER, VA_ids[idx]);
  glBufferData(GL_ARRAY_BUFFER, size, att_array, GL_STATIC_DRAW);
  /* Specify that our coordinate data is going into attribute index 0, and contains two floats per vertex */
  glVertexAttribPointer(idx, dim, GL_FLOAT, GL_FALSE, 0, 0);
  /* Enable attribute index 0 as being used */
  glEnableVertexAttribArray(idx);

}

}