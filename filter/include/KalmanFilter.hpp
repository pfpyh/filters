#pragma once

#include "matrix.hpp"
#include "angle.hpp"

#include <stdint.h>

namespace math::filters
{
class EulerKalmanFilter
{
public :
    struct Data
    {
        double _x = 0.0;
        double _y = 0.0;
        double _z = 0.0;
    };

private :
    Matrix<double> _A;
    Matrix<double> _H;
    Matrix<double> _Q;
    Matrix<double> _R;
    Matrix<double> _X;
    Matrix<double> _P;

    bool _first = false;

private:
    auto acc_to_euler(const Data& acc)->Euler;

public :
    EulerKalmanFilter();
    auto run(const Data& gyr, const Data& acc)->Euler;
};
} // namespace math::filters