#ifndef VERTEX_H
#define VERTEX_H

#include "point3d.h"
#include "transformmatrix.h"
#include "sceneobject.h"

class Vertex: public SceneObject
{
public:
    Vertex(double x, double y, double z) : _position(x, y, z) {}

    Point3D getPosition(){
        return _position;
    }

    void setPosition(Point3D point){
        _position = point;
    }

    void transform(TransformMatrix& matrix) override {
        _position = matrix.transformPoint(_position);
    }

    static bool compareX(std::shared_ptr<Vertex>& a, std::shared_ptr<Vertex>& b) {
        return a->getPosition().X < b->getPosition().X;
    }
    static bool compareY(std::shared_ptr<Vertex>& a, std::shared_ptr<Vertex>& b) {
        return a->getPosition().Y < b->getPosition().Y;
    }
    static bool compareZ(std::shared_ptr<Vertex>& a, std::shared_ptr<Vertex>& b) {
        return a->getPosition().Z < b->getPosition().Z;
    }
private:
    Point3D _position;
};

#endif // VERTEX_H
