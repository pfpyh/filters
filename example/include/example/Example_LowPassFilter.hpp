#pragma once

#include "LowPassFilter.hpp"
#include "CSV.hpp"

namespace math::example
{
constexpr char SONAR_ALT_CSV[] = "SonarAlt.csv";
constexpr char OUTPUT_1st_SONAR_ALT_CSV[] = "Output_1st_SonarAlt.csv";
constexpr char OUTPUT_2nd_SONAR_ALT_CSV[] = "Output_2nd_SonarAlt.csv";

auto example_lpf() -> void
{
    {
        constexpr double x0 = 0.0;
        constexpr double alpha = 0.4;
        filters::LowPassFilter<double> lpf(x0, alpha);

        constexpr uint32_t sample_count = 500;
        CSV csv(SONAR_ALT_CSV);
        auto sonar_map = csv.read(',');

        csv.open(OUTPUT_1st_SONAR_ALT_CSV, true);
        std::vector<std::string> write_buf;
        write_buf.push_back(std::string());
        for (uint32_t i = 0; i < sample_count; ++i)
        {
            auto sonar = std::stod(sonar_map[i][0]);
            auto filtered_sonar = lpf.run(sonar);
            write_buf[0] = std::to_string(filtered_sonar);
            csv.write(write_buf);
        }
    }
    {
        constexpr double x0 = 0.0;
        constexpr double alpha = 0.9;
        filters::LowPassFilter<double> lpf(x0, alpha);

        constexpr uint32_t sample_count = 500;
        CSV csv(SONAR_ALT_CSV);
        auto sonar_map = csv.read(',');

        csv.open(OUTPUT_2nd_SONAR_ALT_CSV, true);
        std::vector<std::string> write_buf;
        write_buf.push_back(std::string());
        for (uint32_t i = 0; i < sample_count; ++i)
        {
            auto sonar = std::stod(sonar_map[i][0]);
            auto filtered_sonar = lpf.run(sonar);
            write_buf[0] = std::to_string(filtered_sonar);
            csv.write(write_buf);
        }
    }
};
} // namespace math::example