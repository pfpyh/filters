#include "KalmanFilter.hpp"
#include "angle.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <math.h>

auto readFileIntoString(const std::string& path) -> std::string
{
    auto ss = std::ostringstream{};
    std::ifstream input_file(path);
    if (!input_file.is_open()) {

    }
    ss << input_file.rdbuf();
    return ss.str();
}

auto csvRead(const std::string& path) -> std::map<int, std::vector<std::string>>
{
    std::string file_contents;
    std::map<int, std::vector<std::string>> csv_contents;
    char delimiter = ',';

    file_contents = readFileIntoString(path);

    std::istringstream sstream(file_contents);
    std::vector<std::string> items;
    std::string record;

    int counter = 0;
    while (std::getline(sstream, record)) {
        std::istringstream line(record);
        while (std::getline(line, record, delimiter)) {
            record.erase(std::remove_if(record.begin(), record.end(), isspace), record.end());
            items.push_back(record);
        }

        csv_contents[counter] = items;
        items.clear();
        counter += 1;
    }
    return csv_contents;
};

void main()
{
    math::filters::EulerKalmanFilter k;

    constexpr uint32_t sample_count = 41500;
    auto gyr_map = csvRead("D:\\repo\\filters\\python\\ArsGyro.csv");
    auto acc_map = csvRead("D:\\repo\\filters\\python\\ArsAccel.csv");
    
    for (uint32_t i = 0; i < sample_count; ++i)
    {
        math::filters::EulerKalmanFilter::Data gyr;
        gyr._x = std::stod(gyr_map[i][0]);
        gyr._y = std::stod(gyr_map[i][1]);
        gyr._z = std::stod(gyr_map[i][2]);

        math::filters::EulerKalmanFilter::Data acc;
        acc._x = std::stod(acc_map[i][0]);
        acc._y = std::stod(acc_map[i][1]);
        acc._z = std::stod(acc_map[i][2]);

        auto e = k.run(gyr, acc);

        constexpr double df = 180 / 3.14;

        auto phi = e._x * df;
        auto theta = e._y * df;
        auto psi = e._z * df;

        std::cout << "roll=" << std::to_string(e._x);
        std::cout << "/pitch=" << std::to_string(e._y);
        std::cout << "/yaw=" << std::to_string(e._z) << "\n";
    }
};