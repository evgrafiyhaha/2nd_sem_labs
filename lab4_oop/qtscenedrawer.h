#ifndef QTSCENEDRAWER_H
#define QTSCENEDRAWER_H


#include "scenedrawerbase.h"

#define DISTANCE 100
#define CELL_SIZE 30

class QtSceneDrawer: public SceneDrawerBase
{
public:
    void drawScene(Scene scene) override;
};

#endif // QTSCENEDRAWER_H
