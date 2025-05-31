#include <math.h>
#include <stdlib.h>

typedef struct mat_3_3 {
    float mat[3][3];
} Matrix3;

// Initialising functions
Matrix3* newMatrix();
Matrix3* zeroMatrix();

// Matrix operations
Matrix3* addMatrix(Matrix3 *aMat, Matrix3 *bMat);
Matrix3* multiplyMatrix(Matrix3 *aMat, Matrix3 *bMat);

// Matrix properties
Matrix3* getMatTranspose(Matrix3 *inMat);
Matrix3* getMatAdjoint(Matrix3 *inMat);
float getMatTrace(Matrix3 *inMat);
float getMatDet(Matrix3 *inMat);

Matrix3* newMatrix() {
    return (Matrix3*) malloc(sizeof(Matrix3));
}

Matrix3* zeroMatrix() {
    return (Matrix3*) calloc(1, sizeof(Matrix3));
}

Matrix3* addMatrix(Matrix3 *aMat, Matrix3 *bMat) {
    Matrix3 *outMat = newMatrix();
    
    for(char i = 0; i < 3; i++)
        for(char j = 0; j < 3; j++)
            outMat -> mat[i][j] = aMat -> mat[i][j] * bMat -> mat[i][j];

    return outMat;
}

Matrix3* multiplyMatrix(Matrix3 *aMat, Matrix3 *bMat) {
    Matrix3 *outMat = newMatrix();
    
    for(char i = 0; i < 3; i++)
        for(char j = 0; j < 3; j++)
            for(char k = 0; k < 3; k++)
                outMat -> mat[i][j] = aMat -> mat[i][k] * bMat -> mat[k][j];

    return outMat;
}

Matrix3* getMatTranspose(Matrix3 *inMat) {
    Matrix3 *outMat = newMatrix();
    
    for(char i = 0; i < 3; i++)
        for(char j = 0; j < 3; j++)
            outMat -> mat[j][i] = inMat -> mat[i][j];

    return outMat;
}

Matrix3* getMatAdjoint(Matrix3 *inMat) {
    Matrix3 *outMat = newMatrix();

    // Add miserable code here

    return outMat;
}

float getMatTrace(Matrix3 *inMat) {
    float trace = 0.0f;
    
    for(char i = 0; i < 3; i++)
        trace += inMat -> mat[i][i];

    return trace;
}

float getMatDet(Matrix3 *inMat) {
    float det = 0.0f;

    // Positive multiplication terms
    for(char i = 0; i < 3; i++)
        det += inMat -> mat[i % 3][0] * inMat -> mat[(i + 1) % 3][1] * inMat -> mat[(i + 2) % 3][2];

    // Negative multiplication terms
    for(char i = 0; i < 3; i++)
        det -= inMat -> mat[i % 3][2] * inMat -> mat[(i + 1) % 3][1] * inMat -> mat[(i + 2) % 3][0];

    return det;
}