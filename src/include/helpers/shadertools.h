#ifndef shadertools_h
#define shadertools_h

namespace helpers{

void create_and_compile_shader(unsigned int *shader_id, unsigned int shader_kind, char* shader_source);

void print_shader_program_status(unsigned int *shader_program_id);

}

#endif