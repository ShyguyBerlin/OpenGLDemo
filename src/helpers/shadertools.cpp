#include <helpers/shadertools.h>
#include <glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

namespace helpers{

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

void create_and_compile_shader(unsigned int *shader_id, unsigned int shader_kind, char* source){
    *shader_id = glCreateShader(shader_kind);
    glShaderSource(*shader_id, 1, &source, NULL);
    glCompileShader(*shader_id);
    {
        int success;
        char infoLog[512];
        glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            printf("%s\n",source);
            glGetShaderInfoLog(*shader_id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
        }
    }
}

void print_shader_program_status(unsigned int *shader_program_id){
    {
        int success;
        char infoLog[512];
        glGetProgramiv(*shader_program_id, GL_LINK_STATUS, &success);
        if(!success) {
        glGetProgramInfoLog(*shader_program_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
        }
    }
}

// This is not generic enough, by far
int make_shader_program(unsigned int *shader_out, char *vert_src, char *frag_src){
    const char *vertfname =vert_src;
    char *vertexShaderSource = filetobuf(vertfname);
    unsigned int vertexShader;
    create_and_compile_shader(&vertexShader,GL_VERTEX_SHADER,vertexShaderSource);

    const char *fragfname =frag_src;
    char *fragShaderSource = filetobuf(fragfname);
    unsigned int fragShader;
    create_and_compile_shader(&fragShader,GL_FRAGMENT_SHADER,fragShaderSource);

    // Linking the shaders

    *shader_out = glCreateProgram();

    glAttachShader(*shader_out, vertexShader);
    glAttachShader(*shader_out, fragShader);

    //glBindAttribLocation(*shader_out, 0, "in_Position");
    //glBindAttribLocation(shaderProgram, 1, "in_Color");

    glLinkProgram(*shader_out);

    print_shader_program_status(shader_out);

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    return 0;
}

}