#include "CSV.hpp"
#include "configure.h"
#include <stdexcept>

namespace math::example
{
CSV::CSV() {};

CSV::CSV(const std::string& file_name,
         const bool write_mode /* = false */)
{
    open(file_name, write_mode);
};

CSV::~CSV()
{
    close();
}

auto CSV::open(const std::string& file_name,
               const bool write_mode /* = false */) -> bool
{
    if (write_mode)
    {
        std::string path(DATA_OUTPUT_PATH);
        path += "/";
        path += file_name;

        _write_file.open(path);
        if (!_write_file.is_open()) return false;
    }
    else
    {
        std::string path(DATA_PATH);
        path += "/";
        path += file_name;

        _read_file.open(path);
        if (!_read_file.is_open()) return false;
    }
    return true;
};

auto CSV::close() -> void
{
    if (_read_file.is_open()) _read_file.close();
    if (_write_file.is_open()) _write_file.close();
}

auto CSV::read(const char delim)->std::map<int32_t, std::vector<std::string>>
{
    if (!_read_file.is_open())
        throw std::invalid_argument("File is not open");

    auto ss = std::ostringstream();
    ss << _read_file.rdbuf();
    std::string contents(ss.str());

    std::istringstream sstream(contents);
    std::vector<std::string> items;
    std::string record;

    std::map<int32_t, std::vector<std::string>> csv_contents;
    int32_t count = 0;

    while (std::getline(sstream, record))
    {
        std::istringstream line(record);
        while (std::getline(line, record, delim))
        {
            record.erase(std::remove_if(record.begin(), record.end(), isspace), record.end());
            items.push_back(record);
        }

        csv_contents[count] = items;
        items.clear();
        count += 1;
    }
    return csv_contents;
};

auto CSV::write(const std::vector<std::string>& data) -> void
{
    if (!_write_file.is_open())
        throw std::invalid_argument("File is not open");

    auto ss = std::ostringstream();
    for (size_t i = 0; i < data.size(); ++i)
    {
        if (i + 1 != data.size())
        {
            const std::string buf(data[i] + ",");
            _write_file.write(buf.c_str(), buf.size());
        }
        else _write_file.write(data[i].c_str(), data[i].size());
    }
    _write_file.write("\n", 1);
};
} // namepsace math::example