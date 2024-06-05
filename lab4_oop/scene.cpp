#include "scene.h"

Scene::Scene() {}

std::vector<std::shared_ptr<Figure>> Scene::getFigures() {
    return _figures;
}


void Scene::transformFigures(TransformMatrix matrix) {
    if (_figures.empty()) {
        throw NoFiguresError(NO_FIGURES_ERROR);
    }
    for (const auto& figure : _figures) {
        for (const auto& vertex : figure->getVertices()) {
            vertex->transform(matrix);
        }
    }
}
