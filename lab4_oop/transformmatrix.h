#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "point3d.h"
#include <iostream>
#include <vector>
#include <array>


class TransformMatrix
{
public:
    TransformMatrix() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                _matr[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }
    TransformMatrix(std::array<std::array<double, 4>, 4> matrix): _matr(matrix) {};


    //TransformMatrix operator *(TransformMatrix matrix);

    Point3D TransformPoint(Point3D& point) {
        Point3D result;
        result.X = point.X * _matr[0][0] + point.Y * _matr[0][1] + point.Z * _matr[0][2] + _matr[0][3];
        result.Y = point.X * _matr[1][0] + point.Y * _matr[1][1] + point.Z * _matr[1][2] + _matr[1][3];
        result.Z = point.X * _matr[2][0] + point.Y * _matr[2][1] + point.Z * _matr[2][2] + _matr[2][3];
        return result;
    }
private:
    std::array<std::array<double, 4>, 4> _matr;
};

#endif // TRANSFORMMATRIX_H
