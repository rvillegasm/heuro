#include "ExcelFile.hpp"

#include <utility>

ExcelFile::ExcelFile(std::string filename, const std::string &defaultSheetTitle)
    : m_Filename(std::move(filename))
{
    m_Workbook.active_sheet().title(defaultSheetTitle);
    m_ActiveRowPerSheet[defaultSheetTitle] = 0;
}

ExcelFile::~ExcelFile()
{
    m_Workbook.save(m_Filename);
}

void ExcelFile::addSheet(const std::string &title)
{
    m_Workbook.create_sheet().title(title);
    m_ActiveRowPerSheet[title] = 0;
}

void ExcelFile::addValues(const std::string &sheetTitle, const std::vector<int> &values)
{
    xlnt::worksheet ws = m_Workbook.sheet_by_title(sheetTitle);
    for (size_t i = 0; i < values.size(); ++i)
    {
        ws.cell(xlnt::cell_reference(i + 1, m_ActiveRowPerSheet[sheetTitle] + 1)).value(values[i]);
    }
    m_ActiveRowPerSheet[sheetTitle] += 1;
}

