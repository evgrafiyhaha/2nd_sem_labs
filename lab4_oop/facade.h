#ifndef FACADE_H
#define FACADE_H

#include <string>
#include <map>

#include "normalizationparameters.h"
#include "basefilereader.h"
#include "scenedrawerbase.h"
#include "filereader.h"
#include "facadeoperationresult.h"
#include "transformmatrixbuilder.h"
#include "qtscenedrawer.h"
#include "scene.h"

#define NO_ERRORS "No errors. I promise"
#define NEGATIVE_SCALING_ERROR "You cannot scale with a negative value"

class Facade
{
    using MethodPtr = FacadeOperationResult (Facade::*)(double, double, double);
public:
    Facade();
    FacadeOperationResult DrawScene();
    FacadeOperationResult LoadScene(std::string filePath, NormalizationParameters normalParams);
    FacadeOperationResult MoveScene(double x, double y, double z);
    FacadeOperationResult RotateScene(double x, double y, double z);
    FacadeOperationResult ScaleScene(double x, double y, double z);
    FacadeOperationResult DoOPeration(std::string operation, double x, double y, double z);
    void setQTScene(QGraphicsScene* scene){_scene.setScene(scene);};

private:
    std::map<std::string,MethodPtr> operations;
    void initializeOperators();

    std::unique_ptr<BaseFileReader> _fileReader;
    std::unique_ptr<SceneDrawerBase> _sceneDrawer;
    Scene _scene;

};

#endif // FACADE_H
