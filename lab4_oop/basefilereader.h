#ifndef BASEFILEREADER_H
#define BASEFILEREADER_H

#include "normalizationparameters.h"
#include "scene.h"
#include "FileReadingError.h"

class BaseFileReader
{
public:
    BaseFileReader(){};
    virtual Scene readScene(std::string path, NormalizationParameters normParams) = 0;
};

#endif // BASEFILEREADER_H
