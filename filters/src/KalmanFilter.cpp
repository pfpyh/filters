#include "KalmanFilter.hpp"

namespace math::filters
{

KalmanFilter::KalmanFilter(Matrix<double>& A,
                           Matrix<double>& H,
                           Matrix<double>& Q,
                           Matrix<double>& R,
                           Matrix<double>& X,
                           Matrix<double>& P)
    : _A(A), _H(H), _Q(Q), _R(R), _X(X), _P(P) {};

//def EulerKalman(A, z) :
//    global firstRun
//    global Q, H, R
//    global x, P
//    if firstRun :
//        H = np.eye(4)
//        Q = 0.0001 * np.eye(4)
//        R = 10 * np.eye(4)
//        x = np.array([1, 0, 0, 0]).transpose()
//        P = np.eye(4)
//        firstRun = False
//    else:
//Xp = A @ x # Xp : State Variable Prediction
//Pp = A @ P @ A.T + Q # Error Covariance Prediction
//
//K = (Pp @ H.T) @ inv(H@Pp@H.T + R) # K : Kalman Gain
//
//x = Xp + K@(z - H@Xp) # Update State Variable Estimation
//P = Pp - K@H@Pp # Update Error Covariance Estimation
//
//phi = atan2(2 * (x[2] * x[3] + x[0] * x[1]), 1 - 2 * (x[1] * *2 + x[2] * *2))
//theta = -asin(2 * (x[1] * x[3] - x[0] * x[2]))
//psi = atan2(2 * (x[1] * x[2] + x[0] * x[3]), 1 - 2 * (x[2] * *2 + x[3] * *2))
//return phi, theta, psi

auto KalmanFilter::run() -> void
{
    Matrix<double> z(2, 2);

    // predict
    auto Xp = _A * _X;
    auto Pp = _A * _P * _A.transpose() + _Q;

    // kalman gain
    auto K = (Pp * _H) * util::inverse(_H * Pp + _R);

    // estimate
    _X = Xp + K * (z - _H * Xp);
    _P = Pp - K * _H * Pp;
};

} // namespace math::filters