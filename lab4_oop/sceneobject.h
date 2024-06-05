#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "transformmatrix.h"

class SceneObject
{
public:
    virtual void transform(TransformMatrix& matrix) = 0;
};

#endif // SCENEOBJECT_H
