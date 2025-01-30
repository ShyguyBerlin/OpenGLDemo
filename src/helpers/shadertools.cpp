#include <helpers/shadertools.h>
#include <glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

namespace helpers{

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

}