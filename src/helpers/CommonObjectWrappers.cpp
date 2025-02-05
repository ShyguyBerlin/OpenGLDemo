#include <helpers/CommonObjectWrappers.h>

#include <stdio.h>

namespace helpers{

Mesh3D::Mesh3D(size_t vertices) : vbo(3){
    vertex_count=vertices;
}

void Mesh3D::set_positions(GLfloat* arr){
    /* Use the following for debugging
    printf("Setting positions! %d\n",3*vertex_count);
    for(int i=4998*3;i<3*vertex_count;i++){
        printf("\nx: %f y: %f z: %f\n",arr[i++],arr[i++],arr[i]);
    }*/

    vbo.add_attributes_float(arr,sizeof(GLfloat)*3*vertex_count,0,3);
    //printf("calculated array size: %ul\n",sizeof(GLfloat)*9*vertex_count);
}

void Mesh3D::set_colors(GLfloat* arr){
    vbo.add_attributes_float(arr,sizeof(GLfloat)*3*vertex_count,1,3);
}

void Mesh3D::set_normals(GLfloat* arr){
    vbo.add_attributes_float(arr,sizeof(GLfloat)*3*vertex_count,2,3);
}

void Mesh3D::set_shader(GLuint _shader){
    shader=_shader;
}

void Mesh3D::load_shader(){
    glUseProgram(shader);
}

void Mesh3D::draw(){
    vbo.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void Mesh3D::draw_strip(GLint from, GLsizei to){
    vbo.bind();
    glDrawArrays(GL_TRIANGLE_STRIP, from, to);
}

// Terrain Object

TerrainObject::TerrainObject(unsigned int size_X, unsigned int size_Y,float grid_dist) : mesh((1+size_X)*size_Y*2){
    cols=size_X;
    rows=size_Y;

    size_t vertex_count = rows*2*(cols+1); // Formula is so weird, because we use triangle strips

    // 0-2-4 
    // |/|/|
    // 1-3-5

    // Each rect is 2 triangles which are 3 vertices.
    std::vector<glm::vec3> positions(vertex_count);
    std::vector<glm::vec3> colors   (vertex_count);
    std::vector<glm::vec3> normals  (vertex_count);

    glm::vec3 offset(-((float)size_X)*grid_dist/2.f,0.f,-((float)size_Y)*grid_dist/2.f);
    int c=0;
    for(int y=0;y<rows;y++){

        positions[c]=glm::vec3(0.f,0.f,(float)y*grid_dist)+offset;
        colors[c]=glm::vec3(0.f,0.f,0.f);
        normals[c++]=glm::vec3(0.f,1.f,0.f);
        if(y==rows-1){
            printf("\nx: %lf z: %lf",positions[c-1].x,positions[c-1].z);
        }
        positions[c]=glm::vec3(0.f,0.f,(float)(y+1)*grid_dist)+offset;
        colors[c]=glm::vec3(0.f,0.f,0.f);
        normals[c++]=glm::vec3(0.f,1.f,0.f);
        for(int x=0;x<cols;x++){
            positions[c]=glm::vec3((float)(x+1)*grid_dist,0.f,(float)y*grid_dist)+offset;
            colors[c]=glm::vec3(0.f,0.f,0.f);
            normals[c++]=glm::vec3(0.f,1.f,0.f);
            positions[c]=glm::vec3((float)(x+1)*grid_dist,0.f,(float)(y+1)*grid_dist)+offset;
            colors[c]=glm::vec3(0.f,0.f,0.f);
            normals[c++]=glm::vec3(0.f,1.f,0.f);
        }
    }

    mesh.set_positions(reinterpret_cast<GLfloat*>(positions.data())); // this is dangerous lol
    mesh.set_colors(reinterpret_cast<GLfloat*>(colors.data()));
    mesh.set_normals(reinterpret_cast<GLfloat*>(normals.data()));

}

void TerrainObject::draw(){
    for(int i=0;i<rows;i++){
        mesh.draw_strip(i*2*(cols+1),2*(cols+1));
    }
}

}