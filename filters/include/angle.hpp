#pragma once

#include <cmath>

namespace math
{
struct Euler;
struct Quaternion;

class Euler
{
public :
    double _x = 0.0;
    double _y = 0.0;
    double _z = 0.0;

    Euler();
    Euler(const double x, const double y, const double z);
    Euler(const Euler& e);

    auto to_quaternion()->Quaternion;
};

Euler::Euler() {};
Euler::Euler(const double x, const double y, const double z) : _x(x), _y(y), _z(z) {};
Euler::Euler(const Euler& e) : _x(e._x), _y(e._y), _z(e._z) {};

auto Euler::to_quaternion() -> Quaternion
{
    Quaternion q;

    const double sin_x = std::sin(_x / 2);
    const double cos_x = std::cos(_x / 2);
    const double sin_y = std::sin(_y / 2);
    const double cos_y = std::cos(_y / 2);
    const double sin_z = std::sin(_z / 2);
    const double cos_z = std::cos(_z / 2);

    q._x = (cos_x * cos_y * cos_z) + (sin_x * sin_y * sin_z);
    q._y = (sin_x * cos_y * cos_z) - (cos_x * sin_y * sin_z);
    q._z = (cos_x * sin_y * cos_z) + (sin_x * cos_y * sin_z);
    q._i = (cos_x * cos_y * sin_z) - (sin_x * sin_y * cos_z);

    return q;
};

class Quaternion
{
public:
    double _x = 0.0;
    double _y = 0.0;
    double _z = 0.0;
    double _i = 0.0;

    Quaternion();
    Quaternion(const double x, const double y, const double z, const double i);
    Quaternion(const Quaternion& q);

    auto to_euler()->Euler;
}

Quaternion::Quaternion() {};
Quaternion::Quaternion(const double x, const double y, const double z, const double i) : _x(x), _y(y), _z(z), _i(i) {};
Quaternion::Quaternion(const Quaternion& q) : _x(q._x), _y(q._y), _z(q._z), _i(q._i) {};

auto Quaternion::to_euler() -> Euler
{
    return Euler();
};

} // namespace math