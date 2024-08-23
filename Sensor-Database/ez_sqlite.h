#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>
#include <vector>

struct Result
{
    std::vector<std::string> col{};
    std::vector<std::vector<std::string> > val{};
};

inline Result result{};

inline void execute_query(const SQLite::Database& db, const std::string& query_text)
{
    SQLite::Statement query(db, query_text);
    result.val = {};
    result.col = {};
    for (int i = 0; i < query.getColumnCount(); ++i)
    {
        result.col.emplace_back(query.getColumnName(i));
    }
    while (query.executeStep())
    {
        std::vector<std::string> row{};
        for (int i = 0; i < query.getColumnCount(); ++i)
        {
            row.push_back(query.getColumn(i));
        }
        result.val.push_back(row);
    }
}

inline void print_query_result()
{
    std::vector<int> col_widths(result.col.size(), 0);

    for (size_t i = 0; i < result.col.size(); ++i)
    {
        col_widths[i] = static_cast<int>(result.col[i].length());
        for (const auto& row: result.val)
        {
            col_widths[i] = std::max(col_widths[i], static_cast<int>(row[i].length()));
        }
    }

    for (size_t i = 0; i < result.col.size(); ++i)
    {
        std::cout << std::left << std::setw(col_widths[i] + 2) << result.col[i];
    }
    std::cout << std::endl;

    for (const auto& row: result.val)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            std::cout << std::left << std::setw(col_widths[i] + 2) << row[i];
        }
        std::cout << std::endl;
    }
}
