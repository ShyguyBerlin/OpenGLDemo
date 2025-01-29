cmake_minimum_required(VERSION 3.0.0)
project(opengl_project VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)
list(APPEND CMAKE_PREFIX_PATH "C:/msys64/mingw64/lib/cmake/glfw3")

find_package(OpenGL REQUIRED)
<<<<<<< HEAD

include_directories(src/include)
=======
find_package(glfw3 3.4 REQUIRED)
>>>>>>> d264e63f192080c887369577d31bd6269f9fe5a6

add_executable(opengl_project 
    src/main.cpp
    src/glad/glad.c
    src/include/glad.h
    src/include/helpers/VBOhelper.h
    src/helpers/VBOhelper.cpp
)

target_link_libraries(opengl_project 
    glfw
    OpenGL::GL
)