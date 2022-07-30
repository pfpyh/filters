#include "KalmanFilter.hpp"
#include "angle.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <math.h>

struct IMU
{
    double _x = 0.0;
    double _y = 0.0;
    double _z = 0.0;

    IMU() {};
    IMU(const double x, const double y, const double z)
        : _x(x), _y(y), _z(z) {};
};

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

auto acc_to_euler(const IMU& acc) -> math::Euler
{
    math::Euler e;
    e._y = std::asin(acc._x / 9.8);
    e._x = std::asin((-1) * acc._y / (9.8 * std::cos(e._y)));
    e._z = 0.0;
    return e;
};

//def EulerAccel(ax, ay, az) :
//    g = 9.8
//    theta = asin(ax / g)
//    phi = asin(-ay / (g * cos(theta)))
//    return phi, theta

void main()
{
    auto H(math::util::eye<double>(4));
    auto Q(0.0001 * math::util::eye<double>(4));
    auto R((double)10 * math::util::eye<double>(4));
    math::Matrix<double> X(1, 4);
    X[0][0] = 1;
    auto P(math::util::eye<double>(4));
    auto A(math::util::eye<double>(4));

    constexpr uint32_t sample_count = 41500;

    auto gyr_map = csvRead("D:\\repo\\filters\\python\\ArsGyro.csv");
    auto acc_map = csvRead("D:\\repo\\filters\\python\\ArsAccel.csv");
    
    for (uint32_t i = 0; i < sample_count; ++i)
    {
        IMU gyro(std::stod(gyr_map[i][0]), std::stod(gyr_map[i][1]), std::stod(gyr_map[i][2]));

        math::Matrix<double> quat(4);
        quat[0][0] = 0; quat[0][1] = (-1) * gyro._x; quat[0][2] = (-1) * gyro._y; quat[0][3] = (-1) * gyro._z;
        quat[1][0] = gyro._x; quat[1][1] = 0; quat[1][2] = gyro._z; quat[1][3] = (-1) * gyro._y;
        quat[2][0] = gyro._y; quat[2][1] = (-1) * gyro._z; quat[2][2] = 0; quat[2][3] = (-1) * gyro._x;
        quat[3][0] = gyro._z; quat[3][1] = gyro._y; quat[3][2] = (-1) * gyro._x; quat[3][3] = 0;

        A = math::util::eye<double>(4) + 0.4 * (1 / 2) * quat;

        IMU acc(std::stod(acc_map[i][0]), std::stod(acc_map[i][1]), std::stod(acc_map[i][2]));
        auto e = acc_to_euler(acc);
        auto q = e.to_quaternion();
    }

    /*for k in range(Nsamples) :
        p, q, r = GetGyro(k)
        A = np.eye(4) + dt * (1 / 2) * np.array([[0, -p, -q, -r], [p, 0, r, -q], [q, -r, 0, p], [r, q, -p, 0]] )
        ax, ay, az = GetAccel(k)
        phi, theta = EulerAccel(ax, ay, az)
        z = EulerToQuaternion(phi, theta, 0) #State variable as Quaternion form

        phi, theta, psi = EulerKalman(A, z)
        EulerSaved[k] = [phi, theta, psi]*/

};