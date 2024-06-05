#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

class Edge
{
public:
    Edge(std::shared_ptr<Vertex> begin, std::shared_ptr<Vertex> end)
        : _begin(begin), _end(end) {}

    std::shared_ptr<Vertex> GetBegin() {
        return _begin;
    }

    std::shared_ptr<Vertex> GetEnd() {
        return _end;
    }
private:
    std::shared_ptr<Vertex> _begin;
    std::shared_ptr<Vertex> _end;
};

#endif // EDGE_H
