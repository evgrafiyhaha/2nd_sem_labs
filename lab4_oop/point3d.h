#ifndef POINT3D_H
#define POINT3D_H

class Point3D
{
public:
    Point3D(double _x, double _y, double _z): X(_x), Y(_y), Z(_z) {};
    Point3D GetPosition() const {
        return *this;
    }
    Point3D() : X(0), Y(0), Z(0) {}
    double X;
    double Y;
    double Z;
};

#endif // POINT3D_H
