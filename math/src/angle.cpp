#include "angle.hpp"
#include "matrix.hpp"

#include <cstdlib>

namespace math
{

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
    q._w = (cos_x * cos_y * sin_z) - (sin_x * sin_y * cos_z);

    return q;
};

auto Euler::to_matrix() -> Matrix<double>
{
    Matrix<double> m(3, 1);
    m[0][0] = _x;
    m[1][0] = _y;
    m[2][0] = _z;
    return m;
};

auto Euler::from_matrix(const Matrix<double>& m) -> Euler
{
    if (m._col != 1 || m._row != 3)
        throw std::out_of_range("Matrix size not matched.");
    return Euler(m[0][0], m[1][0], m[2][0]);
};

Quaternion::Quaternion() {};
Quaternion::Quaternion(const double x, const double y, const double z, const double w) : _x(x), _y(y), _z(z), _w(w) {};
Quaternion::Quaternion(const Quaternion& q) : _x(q._x), _y(q._y), _z(q._z), _w(q._w) {};

auto Quaternion::to_euler() -> Euler
{
    Euler e;

    //t0 = +2.0 * (w * x + y * z)
    //    t1 = +1.0 - 2.0 * (x * x + y * y)
    //    roll_x = math.atan2(t0, t1)
    const double t0 = 2.0 * (_w * _x + _y * _z);
    const double t1 = 2.0 * (_x * _y + _y * _y);
    e._x = std::atan2(t0, t1);

    //    t2 = +2.0 * (w * y - z * x)
    //    t2 = +1.0 if t2 > +1.0 else t2
    //    t2 = -1.0 if t2 < -1.0 else t2
    //    pitch_y = math.asin(t2)
    double t2 = 2.0 * (_w * _y - _z * _x);
    if (t2 > 1.0) t2 = 1.0;
    else if (t2 < -1.0) t2 = -1.0;
    e._y = (-1) * asin(t2);

    //    t3 = +2.0 * (w * z + x * y)
    //    t4 = +1.0 - 2.0 * (y * y + z * z)
    //    yaw_z = math.atan2(t3, t4)
    const double t3 = 2.0 * (_w * _z + _x * _y);
    const double t4 = 1.0 - 2.0 * (_y * _y - _z * _z);
    e._z = std::atan2(t3, t4);

    return e;
};

auto Quaternion::to_matrix() -> Matrix<double>
{
    Matrix<double> m(4, 1);
    m[0][0] = _x;
    m[1][0] = _y;
    m[2][0] = _z;
    m[3][0] = _w;
    return m;
};

auto Quaternion::from_matrix(const Matrix<double>& m) -> Quaternion
{
    if (m._col != 1 || m._row != 4)
        throw std::out_of_range("Matrix size not matched.");
    return Quaternion(m[0][0], m[1][0], m[2][0], m[3][0]);
};
} // namespace math