#ifndef FIGURE_H
#define FIGURE_H

#include "vertex.h"
#include "edge.h"

class Figure: public SceneObject
{
public:
    Figure(){};

    Figure(std::vector<std::shared_ptr<Vertex>> vertices,std::vector<std::shared_ptr<Edge>> edges): _vertices(vertices), _edges(edges) {};

    void AddVertex(double x, double y, double z) {
        _vertices.push_back(std::make_shared<Vertex>(x, y, z));
    }

    void AddEdge(std::shared_ptr<Vertex> begin, std::shared_ptr<Vertex> end) {
        _edges.push_back(std::make_shared<Edge>(begin, end));
    }

    std::vector<std::shared_ptr<Vertex>> GetVertices() {
        return _vertices;
    }

    std::vector<std::shared_ptr<Edge>> GetEdges() {
        return _edges;
    }
    void Transform(TransformMatrix& matrix) override {
        for (auto& vertex : _vertices) {
            vertex->Transform(matrix);
        }
    }
private:
    std::vector<std::shared_ptr<Vertex>> _vertices;
    std::vector<std::shared_ptr<Edge>> _edges;
};

#endif // FIGURE_H
