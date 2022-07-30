#pragma once

#include <functional>
#include <stdint.h>

#define MATH_EXCEPTION_ENABLE

#if defined(MATH_EXCEPTION_ENABLE)
#include <iostream>
#include <string>
#include <stdexcept>
#endif

namespace math
{
/*************************************************************/
/******************* Forward declaration *********************/
/*************************************************************/
/*                          Class                            */
/*************************************************************/
#pragma region Class
template <typename T>
class Matrix
{
private :
    T** _mat = nullptr;

public :
    const int32_t _col;
    const int32_t _row;

public :
    Matrix(const int32_t col, const int32_t row);
    Matrix(const int32_t size);
    Matrix(const Matrix& mat);
    Matrix(Matrix&& mat) noexcept;
    ~Matrix();

public :
    T* operator[](const int32_t row) { return _mat[row]; };
    const T* operator[](const int32_t row) const { return _mat[row]; };
    Matrix operator=(const Matrix& mat)
    {
        if (_col != mat._col || _row != mat._row)
            throw std::out_of_range("Matrix size not matched.");

        traversal([this, &mat](const int32_t row, const int32_t col) {
            _mat[row][col] = mat[row][col];
        });
    };

    auto print() -> void;
    auto traversal(std::function<void(const int32_t row, const int32_t col)> func) -> void;
    auto traversal(std::function<void(const int32_t row, const int32_t col)> func) const -> void;
    auto traversal(std::function<void(const int32_t row, const int32_t col, const T& value)> func) -> void;
    auto traversal(std::function<void(const int32_t row, const int32_t col, const T& value)> func) const -> void;
    auto transpose()->Matrix;
    auto inverse()->Matrix;
};
#pragma endregion
/*************************************************************/
/*                           Operator                        */
/*************************************************************/
#pragma region Operator
template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const T& scalar);

template <typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& rhs);

template <typename T>
Matrix<T> operator/(const Matrix<T>& lhs, const Matrix<T>& rhs);
#pragma endregion
namespace util
{
/*************************************************************/
/*                         Commom util                       */
/*************************************************************/
#pragma region Util.Common
template <typename T>
auto eye(const int32_t col, const int32_t row) -> Matrix<T>;

template <typename T>
auto eye(const int32_t size) -> Matrix<T>;
#pragma endregion
/*************************************************************/
/*                         Inverse util                      */
/*************************************************************/
#pragma region Util.Inverse
template <typename T>
auto minor(const Matrix<T>& minor_mat, int32_t mat_size, Matrix<T>& new_minor_mat) -> void;

template <typename T>
auto determine(const Matrix<T>& minor_mat, int32_t size) -> T;

template <typename T>
auto cofactor(const Matrix<T>& minor_mat) -> Matrix<T>;

template <typename T>
auto inverse(const Matrix<T>& mat) -> Matrix<T>;
#pragma endregion
} // namespace util
/*************************************************************/
/********************** Implementation ***********************/
/*************************************************************/
/*                          Class                            */
/*************************************************************/
#pragma region Class
template <typename T>
Matrix<T>::Matrix<T>(const int32_t col, const int32_t row)
    : _col(col), _row(row)
{
    _mat = new T * [_row];
    for (int32_t x = 0; x < _row; ++x)
        _mat[x] = new T[_col];
};

template <typename T>
Matrix<T>::Matrix<T>(const int32_t size)
    : Matrix(size, size) {};

template <typename T>
Matrix<T>::Matrix<T>(const Matrix& mat)
    : _row(mat._row), _col(mat._col)
{
    _mat = new T * [_row];
    for (int32_t row = 0; row < _row; ++row)
    {
        _mat[row] = new T[_col];
        for (int32_t col = 0; col < _col; ++col)
            _mat[row][col] = mat[row][col];
    };
};

template <typename T>
Matrix<T>::Matrix<T>(Matrix&& mat) noexcept
    : _row(mat._row), _col(mat._col)
{
    _mat = new T * [_row];
    for (int32_t row = 0; row < _row; ++row)
    {
        _mat[row] = new T[_col];
        for (int32_t col = 0; col < _col; ++col)
            _mat[row][col] = std::move(mat[row][col]);
    };
}

template <typename T>
Matrix<T>::~Matrix<T>()
{
    if (_row > 0)
    {
        for (int32_t row = 0; row < _row; ++row)
            delete[] _mat[row];
        delete[] _mat;
    }
};

template <typename T>
auto Matrix<T>::print() -> void
{
    std::string output;
    for (int32_t row = 0; row < _row; ++row)
    {
        for (int32_t col = 0; col < _col; ++col)
        {
            output += std::to_string(_mat[row][col]) + "\t";
        }
        output += "\n";
    }
    std::cout << output;
};

template <typename T>
auto Matrix<T>::traversal(std::function<void(const int32_t row, const int32_t col)> func) -> void
{
    for (int32_t __row = 0; __row < _row; ++__row)
        for (int32_t __col = 0; __col < _col; ++__col)
            func(__row, __col);
}

template <typename T>
auto Matrix<T>::traversal(std::function<void(const int32_t row, const int32_t col)> func) const -> void
{
    for (int32_t __row = 0; __row < _row; ++__row)
        for (int32_t __col = 0; __col < _col; ++__col)
            func(__row, __col);
}

template <typename T>
auto Matrix<T>::traversal(std::function<void(const int32_t row, const int32_t col, const T& value)> func) -> void
{
    for (int32_t __row = 0; __row < _row; ++__row)
        for (int32_t __col = 0; __col < _col; ++__col)
            func(__row, __col, _mat[__row][__col]);
}

template <typename T>
auto Matrix<T>::traversal(std::function<void(const int32_t row, const int32_t col, const T& value)> func) const -> void
{
    for (int32_t __row = 0; __row < _row; ++__row)
        for (int32_t __col = 0; __col < _col; ++__col)
            func(__row, __col, _mat[__row][__col]);
}

template <typename T>
auto Matrix<T>::transpose() -> Matrix<T>
{
    Matrix<T> rtn(_col, _row);
    traversal([&rtn, this](const int32_t row, const int32_t col, const T& value) {
        rtn[col][row] = value;
    });
    return rtn;
};

template <typename T>
auto Matrix<T>::inverse() -> Matrix<T>
{
    return util::inverse((*this));
};
#pragma endregion
/*************************************************************/
/*                           Operator                        */
/*************************************************************/
#pragma region Operator
template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
#if defined(MATH_EXCEPTION_ENABLE)
    if (lhs._row != rhs._row || lhs._col != rhs._col)
        throw std::out_of_range("Size not matched.");
#endif
    Matrix<T> rtn(lhs._row, lhs._col);
    rtn.traversal([&rtn, &lhs, &rhs](const int32_t row, const int32_t col) -> void {
        rtn[row][col] = lhs[row][col] + rhs[row][col];
    });
    return rtn;
};

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
#if defined(MATH_EXCEPTION_ENABLE)
    if (lhs._row != rhs._row || lhs._col != rhs._col)
        throw std::out_of_range("Size not matched.");
#endif
    Matrix<T> rtn(lhs._row, lhs._col);
    rtn.traversal([&rtn, &lhs, &rhs](const int32_t row, const int32_t col)
    {
        rtn[row][col] = lhs[row][col] - rhs[row][col];
    });
    return rtn;
};

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
#if defined(MATH_EXCEPTION_ENABLE)
    if (lhs._row != rhs._col || lhs._col != rhs._row)
        throw std::out_of_range("Size not matched.");
#endif
    Matrix<T> rtn(lhs._row, rhs._col);
    for (int32_t row = 0; row < lhs._row; ++row)
    {
        for (int32_t col = 0; col < rhs._col; ++col)
        {
            T sum = lhs[row][0] * rhs[0][col];
            for (int32_t x = 1; x < lhs._col; ++x)
            {
                sum += lhs[row][x] * rhs[x][col];
                int32_t t = 0;
            }
            rtn[row][col] = sum;
        }
        
    }
    return rtn;
};

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const T& scalar)
{
    Matrix<T> rtn(lhs._col, lhs._mat);
    lhs.traversal([&rtn, &scalar](const int32_t row, const int32_t col, const T& value) {
        rtn[row][col] = value * scalar;
    });
    return rtn;
};

template <typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& rhs)
{
    Matrix<T> rtn(rhs._col, rhs._row);
    rhs.traversal([&rtn, &scalar](const int32_t row, const int32_t col, const T& value) {
        rtn[row][col] = value * scalar;
    });
    return rtn;
}

template <typename T>
Matrix<T> operator/(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    throw "Not implemented";
};
#pragma endregion
namespace util
{
/*************************************************************/
/*                         Commom util                       */
/*************************************************************/
#pragma region Util.Common
template <typename T>
auto eye(const int32_t col, const int32_t row) -> Matrix<T>
{
    Matrix<T> rtn(col, row);
    rtn.traversal([&rtn](const int32_t row, const int32_t col) {
        if (row == col) rtn[row][col] = 1;
        else rtn[row][col] = 0;
    });
    return rtn;
};

template <typename T>
auto eye(const int32_t size) -> Matrix<T>
{
    Matrix<T> rtn(size, size);
    rtn.traversal([&rtn](const int32_t row, const int32_t col) {
        if (row == col) rtn[row][col] = 1;
        else rtn[row][col] = 0;
    });
    return rtn;
};
#pragma endregion
/*************************************************************/
/*                         Inverse util                      */
/*************************************************************/
#pragma region Util.Inverse
template <typename T>
auto minor(const Matrix<T>& minor_mat, int32_t mat_size, Matrix<T>& new_minor_mat) -> void
{
    int32_t x = 0, y = 0;
    for (int32_t row = 1; row < minor_mat._row; row++)
    {
        for (int32_t col = 0; col < minor_mat._col; col++)
        {
            if (col == mat_size) continue;

            new_minor_mat[x][y] = minor_mat[row][col];
            y++;
            if (y == (minor_mat._col - 1))
            {
                x++;
                y = 0;
            }
        }
    }
};

template <typename T>
auto determine(const Matrix<T>& minor_mat, int32_t size) -> T
{
    T sum = 0;
    Matrix<T> new_minor_mat(minor_mat._col, minor_mat._row);
    if (size == 1)
        return minor_mat[0][0];
    else if (size == 2)
        return (minor_mat[0][0] * minor_mat[1][1] - minor_mat[0][1] * minor_mat[1][0]);
    else {
        for (int32_t col = 0; col < size; col++)
        {
            minor(minor_mat, col, new_minor_mat);	// function
            sum += static_cast<T>((minor_mat[0][col] * pow(-1, col) * determine(new_minor_mat, (size - 1))));
        }
    }
    return sum;
};

template <typename T>
auto cofactor(const Matrix<T>& minor_mat) -> Matrix<T>
{
    Matrix<T> new_minor_mat(minor_mat._col, minor_mat._row);
    Matrix<T> cofactor_mat(minor_mat._col, minor_mat._row);

    for (int32_t row3 = 0; row3 < minor_mat._row; row3++)
    {
        for (int32_t col3 = 0; col3 < minor_mat._col; col3++)
        {
            int32_t row2 = 0;
            int32_t col2 = 0;
            for (int32_t row = 0; row < minor_mat._row; row++)
            {
                for (int32_t col = 0; col < minor_mat._col; col++)
                {
                    if (row != row3 && col != col3)
                    {
                        new_minor_mat[row2][col2] = minor_mat[row][col];
                        if (col2 < (minor_mat._col - 2))
                            col2++;
                        else
                        {
                            col2 = 0;
                            row2++;
                        }
                    }
                }
            }
            cofactor_mat[row3][col3] = pow(-1, (row3 + col3)) * determine(new_minor_mat, (minor_mat._row - 1));
        }
    }
    auto t_cofactor_mat(cofactor_mat.transpose());	// function
    return t_cofactor_mat;
};

template <typename T>
auto inverse(const Matrix<T>& mat) -> Matrix<T>
{
    const auto determinate = determine(mat, mat._row);
    if (determinate == 0)
    {
#if defined(MATH_EXCEPTION_ENABLE)
        throw std::out_of_range("Has no inverse");
#else
        return (*this);
#endif
    }
    else if (determinate == 1)
    {
        Matrix<T> rnt(mat);
        rnt[0][0] = 1;
        return rnt;
    }
    else
    {
        return cofactor(mat);
    }
};
} // namespace util
#pragma endregion
} // namespace math