cmake_minimum_required(VERSION 3.0.0)
project(opengl_project VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)
list(APPEND CMAKE_PREFIX_PATH "C:/msys64/mingw64/lib/cmake/glfw3")

find_package(OpenGL REQUIRED)

include_directories(src/include)

# Linux uses slightly older version and can import automatically 
# so we only set this on windoof
if (WIN32)
    find_package(glfw3 3.4 REQUIRED)
endif()

add_executable(opengl_project 
    src/main.cpp
    src/glad/glad.c
    src/helpers/CommonObjectWrappers.cpp
    src/helpers/TerrainObject.cpp
    src/helpers/shadertools.cpp
    src/helpers/VBOhelper.cpp
)

target_link_libraries(opengl_project 
    glfw
    OpenGL::GL
)