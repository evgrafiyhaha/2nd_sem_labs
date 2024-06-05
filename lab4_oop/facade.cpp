#include "facade.h"

Facade::Facade(): _fileReader(std::make_unique<FileReader>()),_sceneDrawer(std::make_unique<QtSceneDrawer>()), _scene() {
    initializeOperators();
}


FacadeOperationResult Facade::DoOPeration(std::string operation, double x, double y, double z) {
    auto it = operations.find(operation);
    if (it != operations.end()) {
        return (this->*(it->second))(x,y,z);
    }
}

void Facade::initializeOperators() {
    operations["Scale"] = &Facade::ScaleScene;
    operations["Move"] = &Facade::MoveScene;
    operations["Rotate"] = &Facade::RotateScene;
}

FacadeOperationResult Facade::LoadScene(std::string filePath, NormalizationParameters normalParams) {
    std::string errorText = NO_ERRORS;
    bool isSuccess = true;

    try {
        _scene = _fileReader->ReadScene(filePath,normalParams);
    } catch (const std::exception &e) {
        errorText = e.what();
        isSuccess = false;
    }
    _scene = _fileReader->ReadScene(filePath,normalParams);
    return FacadeOperationResult(errorText,isSuccess);
}

FacadeOperationResult Facade::DrawScene() {
    std::string errorText = NO_ERRORS;
    bool isSuccess = true;

    try {
        _sceneDrawer->drawScene(_scene);
    } catch (const std::exception &e) {
        errorText = e.what();
        isSuccess = false;
    }

    return FacadeOperationResult(errorText,isSuccess);
}


FacadeOperationResult Facade::MoveScene(double x, double y, double z) {

    TransformMatrix moveMatrix = TransformMatrixBuilder::CreateMoveMatrix(x,y,z);
    try {
        _scene.transformFigures(moveMatrix);
    } catch(const std::exception &e) {
        return FacadeOperationResult(e.what(),false);
    }

    return DrawScene();
}

FacadeOperationResult Facade::RotateScene(double x, double y, double z) {
    try {
        if (x != 0) {
            TransformMatrix RotateX = TransformMatrixBuilder::CreateRotationMatrix(x,0,0);
            _scene.transformFigures(RotateX);
        }
        if (y != 0) {
            TransformMatrix RotateY = TransformMatrixBuilder::CreateRotationMatrix(0,y,0);
            _scene.transformFigures(RotateY);
        }
        if (z != 0) {
            TransformMatrix RotateZ = TransformMatrixBuilder::CreateRotationMatrix(0,0,z);
            _scene.transformFigures(RotateZ);
        }
    } catch(const std::exception &e) {
        return FacadeOperationResult(e.what(),false);
    }

    return DrawScene();
}

FacadeOperationResult Facade::ScaleScene(double x, double y, double z) {
    if (x <= 0 || y <= 0 || z <= 0) {
        return FacadeOperationResult(NEGATIVE_SCALING_ERROR,false);
    } else {
        TransformMatrix scaleMatrix = TransformMatrixBuilder::CreateScaleMatrix(x,y,z);
        try {
            _scene.transformFigures(scaleMatrix);
        } catch(const std::exception &e) {
            return FacadeOperationResult(e.what(),false);
        }

        return DrawScene();
    }
}
