#ifndef TRANSFORMMATRIXBUILDER_H
#define TRANSFORMMATRIXBUILDER_H

#include "transformmatrix.h"

class TransformMatrixBuilder
{
public:
    static TransformMatrix createRotationMatrix(double x, double y, double z);
    static TransformMatrix createMoveMatrix(double x, double y, double z);
    static TransformMatrix createScaleMatrix(double x, double y, double z);
};

#endif // TRANSFORMMATRIXBUILDER_H
