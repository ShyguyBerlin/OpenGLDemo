#include <helpers/VBOhelper.h>
//#include <ostream>
#include <glad.h>

namespace helpers{

VBOhelper::VBOhelper(size_t attributes){
    glGenVertexArrays(1, &VBO_id);
};

}