#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <stdfloat>
#include <thread>
#include <fstream>
#include <cmath>
#include <chrono>
#include <ranges>
#include <filesystem>

using flt = double;
using f64 = std::float64_t;
using f32 = std::float32_t;
using f16 = std::float16_t;
using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;


template<typename T>
class CustomVector : public std::vector<T>
{
public:
    using std::vector<T>::vector;

    [[nodiscard]] int size() const
    {
        return static_cast<int>(std::vector<T>::size());
    }
};

template<typename T>
using arr = CustomVector<T>;
using str = std::string;
using out = std::ostream;
using in = std::istream;
std::ostream& cout = std::cout;
std::istream& cin = std::cin;

template<typename T>
using ptr = std::unique_ptr<T>;

using thread = std::jthread;
using mutex = std::mutex;
using lock = std::scoped_lock<std::mutex>;

template <typename T>
constexpr T&& move(T& t)
{
    return static_cast<T &&>(t);
}

enum FileMode
{
    read = std::ios::in,
    write = std::ios::out,
    app = std::ios::app,
    truncate = std::ios::trunc
};

FileMode operator|(FileMode a, FileMode b)
{
    return static_cast<FileMode>(
        static_cast<int>(a) | static_cast<int>(b)
    );
}

class CustomFile : public std::fstream
{
public:
    using std::fstream::fstream;

    void open(const std::string& filename, FileMode mode)
    {
        std::fstream::open(filename, static_cast<std::ios::openmode>(mode));
    }
};

using file = CustomFile;
template<typename T, typename U>
T cast(const U& value) {
    if constexpr (std::is_same_v<T, int> && std::is_same_v<U, std::string>) {
        return std::atoi(value.c_str());
    } else if constexpr (std::is_same_v<T, double> && std::is_same_v<U, std::string>) {
        return std::atof(value.c_str());
    } else {
        return static_cast<T>(value);
    }
}

template<typename T>
using init_list = std::initializer_list<T>;

inline double sin_d(const double deg)
{
    return std::sin(deg * std::numbers::pi / 180);
}

inline double cos_d(const double deg)
{
    return std::cos(deg * std::numbers::pi / 180);
}
namespace fs = std::filesystem;
template <typename T>
std::vector<T> slice(const std::vector<T>& vec, const int start, const int end)
{
    return std::vector<T>(vec.begin() + start, vec.begin() + end);
}
