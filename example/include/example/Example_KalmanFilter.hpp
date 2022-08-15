#pragma once
#include "KalmanFilter.hpp"
#include "CSV.hpp"
#include <cstdlib>

namespace math::example
{
class EulerKalmanFilter
{
public :
    struct Data { double _x = 0.0, _y = 0.0, _z = 0.0; };

private :
    filters::KalmanFilter<Matrix<double>>* _kf = nullptr;

public :
    EulerKalmanFilter()
    {
        auto H = util::eye<double>(4);
        auto Q = 0.0001 * util::eye<double>(4);
        auto R = 10.0 * util::eye<double>(4);
        Matrix<double> x(4, 1);
        x[0][0] = 1.0; x[1][0] = 0.0; x[2][0] = 0.0; x[3][0] = 0.0;
        auto P = util::eye<double>(4);

        _kf = new filters::KalmanFilter<Matrix<double>>(H, Q, R, x, P);
    };

    ~EulerKalmanFilter()
    {
        delete _kf;
    };

public :
    auto run(const Data& gyr, const Data& acc) -> Euler&&
    {
        Matrix<double> quat(4);
        quat[0][0] = 0;      quat[0][1] = (-1) * gyr._x; quat[0][2] = (-1) * gyr._y; quat[0][3] = (-1) * gyr._z;
        quat[1][0] = gyr._x; quat[1][1] = 0;             quat[1][2] = gyr._z;        quat[1][3] = (-1) * gyr._y;
        quat[2][0] = gyr._y; quat[2][1] = (-1) * gyr._z; quat[2][2] = 0;             quat[2][3] = gyr._x;
        quat[3][0] = gyr._z; quat[3][1] = gyr._y;        quat[3][2] = (-1) * gyr._x; quat[3][3] = 0;
        auto A = util::eye<double>(4) + (0.005 * quat);

        auto euler_z(Euler::from_acc(acc._x, acc._y));
        auto quat_z(euler_z.to_quaternion());
        auto z(quat_z.to_matrix());

        const auto& x = _kf->run(A, z);

        auto q(Quaternion::from_matrix(x));
        auto e(q.to_euler());
        std::cout << "phi=" << std::to_string(e._roll) << "/theta=" << std::to_string(e._pitch) << "/psi=" << std::to_string(e._yaw) << std::endl;
        return std::move(e);
    };
};

auto example_kf() -> void
{
    constexpr char ARS_GYRO[] = "ArsGyro.csv";
    constexpr char ARS_ACCEL[] = "ArsAccel.csv";
    constexpr char OUTPUT_CSV[] = "Output_EulerKF.csv";

    EulerKalmanFilter kf;

    constexpr uint32_t sample_count = 41500;
    CSV csv(ARS_GYRO);
    auto gyr_map = csv.read(',');
    csv.close();
    csv.open(ARS_ACCEL);
    auto acc_map = csv.read(',');
    csv.open(OUTPUT_CSV, true);

    for (uint32_t i = 0; i < sample_count; ++i)
    {
        EulerKalmanFilter::Data gyr;
        gyr._x = std::stod(gyr_map[i][0]);
        gyr._y = std::stod(gyr_map[i][1]);
        gyr._z = std::stod(gyr_map[i][2]);

        EulerKalmanFilter::Data acc;
        acc._x = std::stod(acc_map[i][0]);
        acc._y = std::stod(acc_map[i][1]);
        acc._z = std::stod(acc_map[i][2]);

        auto e(kf.run(gyr, acc));

        constexpr double df = 180 / 3.14;

        auto phi = e._roll * df;
        auto theta = e._pitch * df;
        auto psi = e._yaw * df;

        std::vector<std::string> output;
        output.push_back(std::to_string(phi));
        output.push_back(std::to_string(theta));
        output.push_back(std::to_string(psi));
        csv.write(output);
    }
    csv.close();
};
} // namespace math::example