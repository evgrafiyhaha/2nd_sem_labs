#ifndef VERTEX_H
#define VERTEX_H

#include "point3d.h"
#include "transformmatrix.h"
#include "sceneobject.h"

class Vertex: public SceneObject
{
public:
    Vertex(double x, double y, double z) : _position(x, y, z) {}

    Point3D GetPosition(){
        return _position;
    }

    void SetPosition(Point3D point){
        _position = point;
    }

    void Transform(TransformMatrix& matrix) override {
        _position = matrix.TransformPoint(_position);
    }

    static bool compareX(std::shared_ptr<Vertex>& a, std::shared_ptr<Vertex>& b) {
        return a->GetPosition().X < b->GetPosition().X;
    }
    static bool compareY(std::shared_ptr<Vertex>& a, std::shared_ptr<Vertex>& b) {
        return a->GetPosition().Y < b->GetPosition().Y;
    }
    static bool compareZ(std::shared_ptr<Vertex>& a, std::shared_ptr<Vertex>& b) {
        return a->GetPosition().Z < b->GetPosition().Z;
    }
private:
    Point3D _position;
};

#endif // VERTEX_H
