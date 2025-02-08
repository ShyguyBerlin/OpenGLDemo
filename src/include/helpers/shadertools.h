#ifndef SHADERTOOLS_H
#define SHADERTOOLS_H

namespace helpers{

char* filetobuf(const char *file);

void create_and_compile_shader(unsigned int *shader_id, unsigned int shader_kind, char* shader_source);

void print_shader_program_status(unsigned int *shader_program_id);

// Returns 0 on success
int make_shader_program(unsigned int *shader_out, char* vert_src, char* frag_src);

}

#endif