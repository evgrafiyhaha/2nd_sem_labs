#include "filereader.h"

FileReader::FileReader() {}


std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


Scene FileReader::ReadScene(std::string path, NormalizationParameters normParams) {
    std::fstream file(path, std::ios::in);
    if (!file) {
        throw FileReadingError(FILE_ERROR);
    }

    std::vector<std::shared_ptr<Figure>> figures;
    std::vector<std::shared_ptr<Vertex>> vertices;
    std::vector<std::shared_ptr<Edge>> edges;
    std::vector<std::string> currentTokenedLine;

    int lineCounter = 0;
    int lineLength = 0;
    std::string line;

    while (std::getline(file, line)) {
        currentTokenedLine = split(line, ',');
        if (currentTokenedLine.empty()) {
            continue;
        }
        int numberCounter = 0;
        for (auto& number : currentTokenedLine) {
            try {
                double value = std::stod(number);
                auto currentVertex = std::make_shared<Vertex>(numberCounter, lineCounter, value);
                vertices.push_back(currentVertex);

                if (numberCounter != 0) {
                    edges.push_back(std::make_shared<Edge>(currentVertex, vertices[vertices.size() - 2]));
                }

                if (lineCounter > 0) {
                    edges.push_back(std::make_shared<Edge>(currentVertex, vertices[vertices.size() - lineLength - 1]));
                }
            } catch (const std::exception& e) {
                throw FileReadingError(NOT_NUMBER_ERROR);

            }
            numberCounter++;
        }

        lineLength = numberCounter;
        lineCounter++;
    }
    if (normParams.max != 0 && normParams.min != 0) {
        if (normParams.max > normParams.min) {
            double minX = (*std::min_element(vertices.begin(), vertices.end(),Vertex::compareX))->GetPosition().X;
            double minY = (*std::min_element(vertices.begin(), vertices.end(),Vertex::compareY))->GetPosition().Y;
            double minZ = (*std::min_element(vertices.begin(), vertices.end(),Vertex::compareZ))->GetPosition().Z;
            double maxX = (*std::max_element(vertices.begin(), vertices.end(),Vertex::compareX))->GetPosition().X;
            double maxY = (*std::max_element(vertices.begin(), vertices.end(),Vertex::compareY))->GetPosition().Y;
            double maxZ = (*std::max_element(vertices.begin(), vertices.end(),Vertex::compareZ))->GetPosition().Z;
            for (auto& vertex : vertices) {
                double normedX = NormalizationParameters::normalValue(minX,maxX,vertex->GetPosition().X,normParams.min,normParams.max);
                double normedY = NormalizationParameters::normalValue(minY,maxY,vertex->GetPosition().Y,normParams.min,normParams.max);
                double normedZ = NormalizationParameters::normalValue(minZ,maxZ,vertex->GetPosition().Z,normParams.min,normParams.max);
                vertex->SetPosition(Point3D(normedX,normedY,normedZ));
            }
        }
    }

    figures.push_back(std::make_shared<Figure>(vertices, edges));
    return Scene(figures);
}
