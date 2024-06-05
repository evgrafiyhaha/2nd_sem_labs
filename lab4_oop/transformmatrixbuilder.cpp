#include "transformmatrixbuilder.h"

TransformMatrix TransformMatrixBuilder::createRotationMatrix(double x, double y, double z) {
    std::array<std::array<double, 4>, 4> matrix;
    if (y == 0 && z == 0) {
        double radians = x * M_PI / 180.0;
        matrix = {{
            {1.0, 0.0, 0.0, 0.0},
            {0.0, std::cos(radians), -std::sin(radians), 0.0},
            {0.0, std::sin(radians), std::cos(radians), 0.0},
            {0.0, 0.0, 0.0, 1.0}
        }};
    } else if (x == 0 && z == 0) {
        double radians = y * M_PI / 180.0;
        matrix = {{
            {std::cos(radians), 0.0, std::sin(radians), 0.0},
            {0.0, 1, 0, 0.0},
            {-std::sin(radians), 0, std::cos(radians), 0.0},
            {0.0, 0.0, 0.0, 1.0}
        }};
    } else if (x == 0 && y == 0) {
        double radians = z * M_PI / 180.0;
        matrix = {{
            {std::cos(radians), std::sin(radians),0, 0},
            {-std::sin(radians), std::cos(radians), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        }};
    }
    return TransformMatrix(matrix);
}

TransformMatrix TransformMatrixBuilder::createMoveMatrix(double x, double y, double z){
    std::array<std::array<double, 4>, 4> matrix;
    matrix = {{
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    }};
    return TransformMatrix(matrix);
}


TransformMatrix TransformMatrixBuilder::createScaleMatrix(double x, double y, double z) {
    std::array<std::array<double, 4>, 4> matrix;
    matrix = {{
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    }};
    return TransformMatrix(matrix);
}
