#include "matrix3Math.h"
#include "vector3Math.h"

void quest(Vector3 *B1, Vector3 *B2, Vector3 *R1, Vector3 *R2, float w1, float w2);
void partialAltProfMatrix(float weight, Vector3 *bVec, Vector3 *rVec, Matrix3 *outMat);

void quest(Vector3 *B1, Vector3 *B2, Vector3 *R1, Vector3 *R2, float w1, float w2) {
    // Variables
    float sigma, a, b, c, d;
    Vector3 *b1, *b2, *r1, *r2;
    Matrix3 *B = zeroMatrix(), *S;

    // Temp variables
    Vector3 *tempVec;
    Matrix3 *tempMat;


    // Unit vectors
    b1 = normaliseVec(B1);
    b2 = normaliseVec(B2);
    r1 = normaliseVec(R1);
    r2 = normaliseVec(R2);


    // Attitude profile matrix
    partialAltProfMatrix(w1, b1, r1, B);
    partialAltProfMatrix(w2, b2, r2, B);


    // Different elements
    Vector3 t = {B -> mat[1][2] - B -> mat[2][1], B -> mat[2][0] - B -> mat[0][2], B -> mat[0][1] - B -> mat[1][0]};
    
    tempMat = getMatTranspose(B);
    S = addMatrix(B, tempMat);
    free(tempMat);

    sigma = getMatTrace(B);

    tempMat = getMatAdjoint(S);
    a = sigma * sigma - getMatTrace(tempMat);
    free(tempMat);

    b = sigma * sigma;
}

void partialAltProfMatrix(float weight, Vector3 *bVec, Vector3 *rVec, Matrix3 *outMat) {
    // B += w * transpose(b) * r
    for(char i = 0; i < 3; i++)
        for(char j = 0; j < 3; j++)
            outMat -> mat[i][j] += weight * bVec -> vec[i] * rVec -> vec[j];
}