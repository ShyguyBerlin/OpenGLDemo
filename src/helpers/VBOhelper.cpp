#include <helpers/VBOhelper.h>
//#include <ostream>

namespace helpers{

VBOhelper::VBOhelper(size_t attributes){
    glGenVertexArrays(1, &VBO_id);
};

}