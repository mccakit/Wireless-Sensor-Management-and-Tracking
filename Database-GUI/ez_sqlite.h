#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>
#include <vector>
#include "ez_cpp.h"

struct QueryResult
{
    arr<str> col{};
    arr<arr<str> > val{};
};

inline QueryResult query_result{};

inline void execute_query(const SQLite::Database& db, const str& query_text)
{
    SQLite::Statement query(db, query_text);
    query_result.val = {};
    query_result.col = {};
    for (int i {0}; i < query.getColumnCount(); ++i)
    {
        query_result.col.emplace_back(query.getColumnName(i));
    }
    while (query.executeStep())
    {
        arr<str> row{};
        for (int i {0}; i < query.getColumnCount(); ++i)
        {
            row.push_back(query.getColumn(i));
        }
        query_result.val.push_back(row);
    }
}

inline void print_query_result()
{
    arr<int> col_widths(query_result.col.size(), 0);
    for (int i = 0; i < query_result.col.size(); ++i)
    {
        col_widths[i] = cast<int>(query_result.col[i].length());
        for (const auto& row: query_result.val)
        {
            col_widths[i] = std::max(col_widths[i], cast<int>(row[i].length()));
        }
    }

    for (int i {0}; i < query_result.col.size(); ++i)
    {
        std::cout << std::left << std::setw(col_widths[i] + 2) << query_result.col[i];
    }
    std::cout << std::endl;

    for (const auto& row: query_result.val)
    {
        for (int i {0}; i < row.size(); ++i)
        {
            std::cout << std::left << std::setw(col_widths[i] + 2) << row[i];
        }
        std::cout << std::endl;
    }
}
