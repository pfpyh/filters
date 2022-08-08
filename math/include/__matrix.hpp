//#pragma once
//#ifndef __DLL_EXPORT__
//#define __DLL_EXPORT__ extern "C" _declspec(dllexport)
//#endif
//
//#include "matrix.hpp"
//
//__DLL_EXPORT__ auto create_matrix_double(const int32_t col, const int32_t row) -> math::Matrix<double>;
//__DLL_EXPORT__ auto create_matrix_float(const int32_t col, const int32_t row) -> math::Matrix<float>;
//
//__DLL_EXPORT__ auto create_matrix_int32(const int32_t col, const int32_t row) -> math::Matrix<int32_t>;
//__DLL_EXPORT__ auto create_matrix_int16(const int32_t col, const int32_t row) -> math::Matrix<int16_t>;
//__DLL_EXPORT__ auto create_matrix_int8(const int32_t col, const int32_t row) -> math::Matrix<int8_t>;
//
//__DLL_EXPORT__ auto create_matrix_uint32(const int32_t col, const int32_t row) -> math::Matrix<uint32_t>;
//__DLL_EXPORT__ auto create_matrix_uint16(const int32_t col, const int32_t row) -> math::Matrix<uint16_t>;
//__DLL_EXPORT__ auto create_matrix_uint8(const int32_t col, const int32_t row) -> math::Matrix<uint8_t>;