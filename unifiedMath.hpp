#ifndef UNIFIED_MATH_H
#define UNIFIED_MATH_H

#include "matrix3Math.hpp"
#include "vector3Math.hpp"
#include "vector4Math.hpp"

// Multiplications between matrices and vectors
// (matrices who have a dimension equal to 1)
// automatically account the needed transpose

// Vector * matrix
Vector3 operator*(const Vector3& vec, const Matrix3& mat) {
    float res[3] = {};

    for(char i = 0; i < 3; i++) {
        float temp = vec.getEle(i);
        res[0] += temp * mat.getEle(i, 0);
        res[1] += temp * mat.getEle(i, 1);
        res[2] += temp * mat.getEle(i, 2);
    }

    return Vector3(res);
}

// Matrix * vector
Vector3 operator*(const Matrix3& mat, const Vector3& vec) {
    float res[3] = {};

    for(char i = 0; i < 3; i++) {
        float temp = vec.getEle(i);
        res[0] += mat.getEle(0, i) * temp;
        res[1] += mat.getEle(1, i) * temp;
        res[2] += mat.getEle(2, i) * temp;
    }

    return Vector3(res);
}

#endif