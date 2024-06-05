#ifndef TRANSFORMMATRIXBUILDER_H
#define TRANSFORMMATRIXBUILDER_H

#include "transformmatrix.h"

class TransformMatrixBuilder
{
public:
    static TransformMatrix CreateRotationMatrix(double x, double y, double z);
    static TransformMatrix CreateMoveMatrix(double x, double y, double z);
    static TransformMatrix CreateScaleMatrix(double x, double y, double z);
};

#endif // TRANSFORMMATRIXBUILDER_H
