#pragma once

#include <cmath>

namespace math
{
class Euler;
class Quaternion;

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
};
} // namespace math