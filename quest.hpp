#ifndef QUEST_H
#define QUEST_H

#define _USE_MATH_DEFINES
#include "unifiedMath.hpp"
#include <cmath>

using namespace std;

void quest(Vector3 B1, Vector3 B2, Vector3 R1, Vector3 R2, float w1, float w2);
void partialAltProfMatrix(float const weight, Vector3 const& bVec, Vector3 const& rVec, Matrix3& resMat);

const float radToDeg = 180 / M_PI;

void quest(Vector3 B1, Vector3 B2, Vector3 R1, Vector3 R2, float w1, float w2) {
    // Variables
    float sigma, a, b, c, d;
    float lamn, lama;
    float alpha, beta, g, y, E;
    float R11, R21, R32, R33, R13;
    float phi, theta, psi;
    Matrix3 B, S;
    Vector3 t, X;
    Vector4 P;

    // Normalise vectors
    B1.normalise();
    B2.normalise();
    R1.normalise();
    R2.normalise();


    // Attitude profile matrix
    partialAltProfMatrix(w1, B1, R1, B);
    partialAltProfMatrix(w2, B2, R2, B);


    // Different elements
    t = {B.getEle(1, 2) - B.getEle(2, 1), B.getEle(2, 0) - B.getEle(0, 2), B.getEle(0, 1) - B.getEle(1, 0)};
    
    S = B + B.trans();
    sigma = B.trace();

    a = sigma * sigma - S.adjoint().trace();
    b = sigma * sigma + t.dot();
    c = S.det() + (t * S).dot(t);
    d = (t * S * S).dot(t);

    // Newton-Raphson Method for lambda
    lama = w1 + w2;
    lamn = 0;
    while(abs(lama - lamn) > 0.000001) {
        lamn = lama;
        lama = lama - (lama * lama * lama * lama - (a + b) * lama * lama - c * lama + (a * b + c * sigma - d)) / (4 * lama * lama * lama - 2 * (a + b) * lama - c);
    }

    // Equations for Qopt
    alpha = lama * lama - sigma * sigma + S.adjoint().trace();
    beta = lama - sigma;
    y = (lama + sigma) * alpha - S.det();
    X = (Matrix3(alpha) + S * beta + S * S) * t;
    g = X.getMagnitude();
    E = 1 / sqrt(y * y + g * g);

    // Optimal Quaternion (x, y, z, w)
    P = Vector4(E * X.getEle(0), E * X.getEle(1), E * X.getEle(2), E * y);


    cout << P << endl;

    // DCM
    R11 = 1 - 2 * (P[1] * P[1] + P[2] * P[2]);
    R21 = 2 * P[0] * P[1] + P[3] * P[2];
    R32 = 2 * P[1] * P[2] + P[3] * P[0];
    R33 = 1 - 2 * (P[0] * P[0] + P[1] * P[1]);
    R13 = 2 * P[0] * P[2] - P[3] * P[1];

    // Euler angles
    phi = atan2(R32, R33) * radToDeg;
    theta = atan(-R13) * radToDeg;
    psi = atan2(R21, R11) * radToDeg;

    cout << "φ: " << phi << "\n";
    cout << "θ: " << theta << "\n";
    cout << "Ψ: " << psi << "\n";
}

void partialAltProfMatrix(float const weight, Vector3 const& bVec, Vector3 const& rVec, Matrix3& resMat) {
    float res[3][3] = {};
    
    // B += w * transpose(b) * r
    for(char i = 0; i < 3; i++)
        for(char j = 0; j < 3; j++)
            res[i][j] = weight * bVec.getEle(i) * rVec.getEle(j);

    resMat += Matrix3(res);
}

#endif