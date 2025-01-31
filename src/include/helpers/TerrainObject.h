#ifndef TERRAINOBJECT_H
#define TERRAINOBJECT_H

#include <helpers/VBOhelper.h>
#include <helpers/CommonObjectWrappers.h>

namespace helpers{

class TerrainObject{
    public:
    Mesh3D mesh;
    TerrainObject(unsigned int size_X, unsigned int size_Y);

};

}

#endif