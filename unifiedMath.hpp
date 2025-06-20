#ifndef UNIFIED_MATH_H
#define UNIFIED_MATH_H

#define _USE_MATH_DEFINES
#include "matrix3Math.hpp"
#include "vector3Math.hpp"
#include "vector4Math.hpp"
#include <cmath>

// Constants
const float radToDeg = 180.0f / M_PI;
const float degToRad = 1.0f / radToDeg;


// Constructors for Matrix3 using three Vector3s.
// Missing parametres are zero filled.

// Each vector forms a row.
Matrix3 matrixFromRows(Vector3 rowA, Vector3 rowB = Vector3(), Vector3 rowC = Vector3()) {
    float mat[3][3] = {};

    for(char i = 0; i < 3; i++) {
        mat[0][i] = rowA[i];
        mat[1][i] = rowB[i];
        mat[2][i] = rowC[i];
    }

    return Matrix3(mat);
}

// Each vector forms a column.
Matrix3 matrixFromColumns(Vector3 colA, Vector3 colB = Vector3(), Vector3 colC = Vector3()) {
    float mat[3][3] = {};

    for(char i = 0; i < 3; i++) {
        mat[i][0] = colA[i];
        mat[i][1] = colB[i];
        mat[i][2] = colC[i];
    }

    return Matrix3(mat);
}


// Multiplications between matrices and vectors
// (matrices who have a dimension equal to 1)
// automatically account the needed transpose.

// Vector * matrix
Vector3 operator*(const Vector3& vec, const Matrix3& mat) {
    float res[3] = {};

    for(char i = 0; i < 3; i++) {
        float temp = vec[i];
        res[0] += temp * mat(i, 0);
        res[1] += temp * mat(i, 1);
        res[2] += temp * mat(i, 2);
    }

    return Vector3(res);
}

// Matrix * vector
Vector3 operator*(const Matrix3& mat, const Vector3& vec) {
    float res[3] = {};

    for(char i = 0; i < 3; i++) {
        float temp = vec[i];
        res[0] += mat(0, i) * temp;
        res[1] += mat(1, i) * temp;
        res[2] += mat(2, i) * temp;
    }

    return Vector3(res);
}

#endif