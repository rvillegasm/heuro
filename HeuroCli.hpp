#pragma once

#include "io/ExcelFile.hpp"
#include <Heuro.hpp>

class HeuroCli
{
private:
    ExcelFile m_OutputFile;

    void evaluateFile(const std::string &inputFileName);

public:
    explicit HeuroCli(const std::string &outputFilename);

    void run();
};


