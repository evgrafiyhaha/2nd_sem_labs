#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <sstream>

#include "basefilereader.h"

class FileReader: public BaseFileReader
{
public:
    FileReader();
    Scene readScene(std::string path, NormalizationParameters normParams) override;
};

#endif // FILEREADER_H
