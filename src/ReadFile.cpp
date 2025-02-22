#include "ReadFile.h"

std::string readFile(std::string path) {
    // Reading Files
    std::string content;
    std::ifstream file;

    file.exceptions(std::ifstream::badbit);
    try {
        file.open(path);
        std::stringstream stream;

        stream << file.rdbuf();

        file.close();

        content = stream.str();
    }
    catch(std::ifstream::failure& e) {
        std::cerr << "Error reading file!" << std::endl;
        return "";
    }
    return content;
}