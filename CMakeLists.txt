cmake_minimum_required(VERSION 3.0.0)
project(opengl_project VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)


add_executable(opengl_project 
    src/main.cpp
    src/glad/glad.c
    src/glad/glad.h
)

target_link_libraries(opengl_project 
    glfw
    OpenGL::GL
)