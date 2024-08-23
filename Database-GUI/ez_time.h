#pragma once
#include <string>
#include <chrono>

inline std::string get_current_date()
{
    using namespace std::chrono;
    const auto now = system_clock::now();
    const auto now_c = system_clock::to_time_t(now);
    const std::tm now_tm = *std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d");
    return oss.str();
}

inline std::string get_current_time()
{
    using namespace std::chrono;
    const auto now = system_clock::now();
    const auto now_c = system_clock::to_time_t(now);
    const std::tm now_tm = *std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%H:%M:%S");
    return oss.str();
}
