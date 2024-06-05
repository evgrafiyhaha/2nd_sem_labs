#ifndef SCENEDRAWERBASE_H
#define SCENEDRAWERBASE_H

#include "scene.h"
#include "DrawingError.h"

class SceneDrawerBase
{
public:
    SceneDrawerBase(){};
    virtual void drawScene(Scene scene) = 0;
};

#endif // SCENEDRAWERBASE_H
