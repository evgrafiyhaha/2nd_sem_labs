#include "qtscenedrawer.h"


void QtSceneDrawer::drawScene(Scene scene) {
    if (scene.getFigures().empty()) {
        throw DrawingError(NO_FIGURES_ERROR);
    }
    scene.getScene()->clear();
    QPen pen = QPen(Qt::white);
    for (auto& figure : scene.getFigures()) {
        for (auto& edge : figure.get()->getEdges()) {
            Point3D firstP = edge->getBegin()->getPosition();
            Point3D secondP = edge->getEnd()->getPosition();
            double firstYPerspective = (firstP.Y * DISTANCE)/(firstP.X + DISTANCE);
            double firstZPerspective = -(firstP.Z * DISTANCE)/(firstP.X + DISTANCE);
            double secondYPerspective = (secondP.Y * DISTANCE)/(secondP.X + DISTANCE);
            double secondZPerspective = -(secondP.Z * DISTANCE)/(secondP.X + DISTANCE);
            scene.getScene()->addLine(firstYPerspective * CELL_SIZE, firstZPerspective * CELL_SIZE, secondYPerspective * CELL_SIZE, secondZPerspective * CELL_SIZE, pen);
        }
    }
}
