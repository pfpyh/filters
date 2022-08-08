#include "KalmanFilter.hpp"

namespace math::filters
{
auto do_filter(Matrix<double>& A,
               Matrix<double>& H,
               Matrix<double>& Q,
               Matrix<double>& R,
               Matrix<double>& X,
               Matrix<double>& P,
               Matrix<double>& z) -> void
{
    // predict
    auto Xp = A * X;

    auto tmp1 = A * P;
    auto t = A.transpose();
    auto tmp2 = tmp1 * t;
    auto tmp3 = tmp2 + Q;

    auto Pp = A * P * A.transpose() + Q;

    // kalman gain
    auto K = (Pp * H.transpose()) * util::inverse(H * Pp * H.transpose() + R);

    // estimate
    auto tmp = H * Xp;
    X = Xp + K * (z - (H * Xp));
    P = Pp - K * H * Pp;
};

EulerKalmanFilter::EulerKalmanFilter()
    : _A(util::eye<double>(4))
    , _H(util::eye<double>(4))
    , _Q(0.0001 * util::eye<double>(4))
    , _R((double)10 * util::eye<double>(4))
    , _X(4, 1)
    , _P(util::eye<double>(4))
{
    _X[0][0] = 1.0;
    _X[1][0] = 0.0;
    _X[2][0] = 0.0;
    _X[3][0] = 0.0;
};

auto EulerKalmanFilter::acc_to_euler(const Data& acc) -> Euler
{
    Euler e;
    e._y = std::asin(acc._x / 9.8);
    e._x = std::asin((-1) * acc._y / (9.8 * std::cos(e._y)));
    e._z = 0.0;
    return e;
};

auto EulerKalmanFilter::run(const Data& gyr, const Data& acc) -> Euler
{
    if (!_first)
    {
        _first = true;
        return Euler();
    }

    Matrix<double> quat(4);
    quat[0][0] = 0;      quat[0][1] = (-1) * gyr._x; quat[0][2] = (-1) * gyr._y; quat[0][3] = (-1) * gyr._z;
    quat[1][0] = gyr._x; quat[1][1] = 0;             quat[1][2] = gyr._z;        quat[1][3] = (-1) * gyr._y;
    quat[2][0] = gyr._y; quat[2][1] = (-1) * gyr._z; quat[2][2] = 0;             quat[2][3] = gyr._x;
    quat[3][0] = gyr._z; quat[3][1] = gyr._y;        quat[3][2] = (-1) * gyr._x; quat[3][3] = 0;

    auto tmp = 0.005 * quat;
    _A = util::eye<double>(4) + (0.005 * quat);

    auto e(acc_to_euler(acc));
    auto q(e.to_quaternion());
    auto z(q.to_matrix());

    do_filter(_A, _H, _Q, _R, _X, _P, z);

    auto rtn_q(Quaternion::from_matrix(_X));
    auto rtn_e(rtn_q.to_euler());
    return rtn_e;
};
} // namespace math::filters