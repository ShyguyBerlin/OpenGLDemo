#ifndef COMMON_OBJECT_WRAPPERS_H
#define COMMON_OBJECT_WRAPPERS_H

#include <glad.h>
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <helpers/VBOhelper.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace helpers{

// provides a easier to use wrapper for the VBOhelper, so that the VBO uses
// 0: Position, 1: Color, 2: Normals
class Mesh3D{
    private:
    glm::mat4 transform; // TODO
    VBOhelper vbo;
    size_t vertex_count;
    GLuint shader;
    public:
    Mesh3D(size_t vertices);
    void set_positions(GLfloat *arr);
    void set_colors(GLfloat *arr);
    void set_normals(GLfloat *arr);
    void set_shader(GLuint _shader);
    void draw();
    void draw_strip(GLint from, GLsizei to);
    void translate(); // TODO
    void rotate_X(); // TODO
    void rotate_Y(); // TODO
    void rotate_Z(); // TODO
};

// To use this, create with constructer, set the sizes you want, then call obj.mesh.set_shader() and then obj.draw()
class TerrainObject{
    public:
    Mesh3D mesh;
    GLint rows;
    GLint cols;
    TerrainObject(unsigned int size_X, unsigned int size_Y,float grid_dist);
    void draw();
};

}

#endif