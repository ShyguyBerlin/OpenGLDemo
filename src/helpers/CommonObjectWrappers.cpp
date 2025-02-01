#include <helpers/CommonObjectWrappers.h>

namespace helpers{

Mesh3D::Mesh3D(size_t vertices) : vbo(3){
    vertex_count=vertices;
}

void Mesh3D::set_positions(GLfloat* arr){
    vbo.add_attributes_float(arr,sizeof(GLfloat)*9*vertex_count,0,3);
    //printf("calculated array size: %ul\n",sizeof(GLfloat)*9*vertex_count);
}

void Mesh3D::set_colors(GLfloat* arr){
    vbo.add_attributes_float(arr,sizeof(GLfloat)*9*vertex_count,1,3);
}

void Mesh3D::set_normals(GLfloat* arr){
    vbo.add_attributes_float(arr,sizeof(GLfloat)*9*vertex_count,2,3);
}

void Mesh3D::set_shader(GLuint _shader){
    shader=_shader;
}

void Mesh3D::draw(){
    glUseProgram(shader);
    vbo.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3*vertex_count);
}

}