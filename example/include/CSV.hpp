#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>

namespace math::example
{
class CSV
{
private:
    std::ifstream _read_file;
    std::ofstream _write_file;

public:
    CSV();
    CSV(const std::string& file_name, 
        const bool write_mode = false);
    ~CSV();

public:
    auto open(const std::string& file_name,
              const bool write_mode = false) -> bool;
    auto close() -> void;

    auto read(const char delim) -> std::map<int32_t, std::vector<std::string>>;
    auto write(const std::vector<std::string>& data) -> void;
};
} // namespace math::example