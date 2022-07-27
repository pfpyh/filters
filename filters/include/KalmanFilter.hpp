#pragma once

#include "matrix.hpp"
#include <stdint.h>

namespace math::filters
{
class KalmanFilter
{
private :
    Matrix<double>& _A;
    Matrix<double>& _H;
    Matrix<double>& _Q;
    Matrix<double>& _R;
    Matrix<double>& _X;
    Matrix<double>& _P;

public :
    KalmanFilter(Matrix<double>& A,
                 Matrix<double>& H,
                 Matrix<double>& Q,
                 Matrix<double>& R,
                 Matrix<double>& X,
                 Matrix<double>& P);

    auto run() -> void;
};
} // namespace math::filters    