#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QGraphicsScene>

#include "figure.h"
#include "transformmatrix.h"
#include "NoFiguresError.h"


class Scene
{
public:
    Scene();
    Scene(std::vector<std::shared_ptr<Figure>> figures): _figures(figures), scene(new QGraphicsScene){};
    std::vector<std::shared_ptr<Figure>> getFigures();
    void transformFigures(TransformMatrix matrix);
    QGraphicsScene* getScene(){return scene;};
    void setScene(QGraphicsScene* _scene){scene = _scene;};
private:
    std::vector<std::shared_ptr<Figure>> _figures;
    QGraphicsScene* scene;
};

#endif // SCENE_H
