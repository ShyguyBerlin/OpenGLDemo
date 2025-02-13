#ifndef VBO_HANDLE_H
#define VBO_HANDLE_H

#include <glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>

namespace helpers{


// Create this, then bind it, then call add_attributes_.. for each property you need
class VBOhelper{
    public:
    GLuint VBO_id;
    std::vector<GLuint> VA_ids;
    VBOhelper(size_t attributes);
    void bind();
    void add_attributes_float(GLfloat* att_array, size_t size, int idx, int dim);
};

};

#endif