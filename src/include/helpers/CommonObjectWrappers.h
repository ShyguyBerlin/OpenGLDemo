#ifndef COMMON_OBJECT_WRAPPERS_H
#define COMMON_OBJECT_WRAPPERS_H

#include <glad.h>
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <helpers/VBOhelper.h>

namespace helpers{

// provides a easier to use wrapper for the VBOhelper, so that the VBO uses
// 0: Position, 1: Color, 2: Normals
class Mesh3D{
    private:
    size_t vertex_count;
    GLuint shader;
    public:
    Mesh3D(size_t vertices);
    void set_positions(GLfloat *arr);
    void set_colors(GLfloat *arr);
    void set_normals(GLfloat *arr);
    void set_shader(GLfloat *arr);
    void draw();
};

}

#endif