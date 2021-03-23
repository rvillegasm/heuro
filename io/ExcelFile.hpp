#pragma once

#include <xlnt/xlnt.hpp>

class ExcelFile
{
private:
    std::string m_Filename;
    xlnt::workbook m_Workbook;
    std::unordered_map<std::string, int> m_ActiveRowPerSheet;

public:
    ExcelFile(std::string filename, const std::string &defaultSheetTitle);
    ~ExcelFile();

    void addSheet(const std::string &title);
    void addValues(const std::string &sheetTitle, const std::vector<int> &values);
};


