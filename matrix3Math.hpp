#ifndef MATRIX_3_MATH_H
#define MATRIX_3_MATH_H

#include <iostream>
#include <vector>

using namespace std;

class Matrix3 {
    private:
    vector<vector<float>> mat;

    public:
    // Default contructor
    Matrix3(): mat(3, vector<float>(3, 0.0f)) {}
    // Construct with values
    Matrix3(float matrix[3][3]) {
        for(char i = 0; i < 3; i++) {
            vector<float> row(3);
            copy(begin(matrix[i]), end(matrix[i]), row.begin());
            mat.push_back(row);
        }
    }
    // Scalar matrix
    Matrix3(float scalar) {
        for(char i = 0; i < 3; i++) {
            mat.push_back(vector<float>(3, 0));
            mat.at(i).at(i) = scalar;
        }    
    }

    // Operator overloading
    Matrix3 operator+(const Matrix3& obj) const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = mat.at(i).at(j) + obj.mat.at(i).at(j);

        return Matrix3(res);
    }

    Matrix3 operator+() const {
        return Matrix3(*this);
    }

    Matrix3 operator-(const Matrix3& obj) const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = mat.at(i).at(j) - obj.mat.at(i).at(j);

        return Matrix3(res);
    }

    Matrix3 operator-() const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = -mat.at(i).at(j);

        return Matrix3(res);
    }

    Matrix3 operator*(const float scalar) const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = mat.at(i).at(j) * scalar;

        return Matrix3(res);
    }

    Matrix3 operator*(const Matrix3& obj) const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                for(char k = 0; k < 3; k++)
                    res[i][j] += mat.at(i).at(k) * obj.mat.at(k).at(j);

        return Matrix3(res);
    }

    Matrix3& operator=(const Matrix3& obj) {
        mat = obj.mat;

        return *this;
    }

    Matrix3& operator=(const float obj[3][3]) {
        for(char i = 0; i < 3; i++) {
            vector<float> row(3);
            copy(begin(obj[i]), end(obj[i]), row.begin());
            mat.push_back(row);
        }

        return *this;
    }

    Matrix3& operator+=(const Matrix3& obj) {
        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                mat.at(i).at(j) += obj.mat.at(i).at(j);

        return *this;
    }

    Matrix3& operator-=(const Matrix3& obj) {
        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                mat.at(i).at(j) -= obj.mat.at(i).at(j);

        return *this;
    }

    Matrix3& operator*=(const float scalar) {
       for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                mat.at(i).at(j) *= scalar;

        return *this;
    }

    Matrix3& operator*=(const Matrix3& obj) {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++) {
            for(char j = 0; j < 3; j++)
                for(char k = 0; k < 3; k++)
                    res[i][j] += mat.at(i).at(k) * obj.mat.at(k).at(j);

            copy(begin(res[i]), end(res[i]), mat.at(i).begin());
        }

        return *this;
    }

    bool operator==(const Matrix3& obj) const {
        return (
            mat.at(0) == obj.mat.at(0) &&
            mat.at(1) == obj.mat.at(1) &&
            mat.at(2) == obj.mat.at(2)
        );
    }

    // Special functions
    // These are unique to the class
    Matrix3 trans() const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = mat.at(j).at(i);

        return Matrix3(res);
    }

    float trace() const {
        float trace = 0.0f;

        for(char i = 0; i < 3; i++)
            trace += mat.at(i).at(i);

        return trace;
    }

    float det() const {
        float det = 0.0f;

        // Positive multiplication terms
        for(char i = 0; i < 3; i++)
            det += mat.at(i % 3).at(0) * mat.at((i + 1) % 3).at(1) * mat.at((i + 2) % 3).at(2);

        // Negative multiplication terms
        for(char i = 0; i < 3; i++)
            det -= mat.at(i % 3).at(2) * mat.at((i + 1) % 3).at(1) * mat.at((i + 2) % 3).at(0);

        return det;
    }

    Matrix3 adjoint() const {
        float res[3][3] = {}, cof[2][2] = {};
        int iCof, jCof;

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++) {
                iCof = jCof = 0;

                //Cofactor matrix
                for(char row = 0; row < 3; row++)
                    for(char col = 0; col < 3; col++)
                        if(row != i && col != j) {
                            cof[iCof][jCof++] = mat.at(row).at(col);
                            
                            if(jCof == 2) {
                                jCof = 0;
                                iCof++;
                            }
                        }

                //Determinant
                res[i][j] = cof[0][0] * cof[1][1] - cof[0][1] * cof[1][0];
            }

        return Matrix3(res);
    }

    Matrix3 inverse() const {
        Matrix3 invMat = adjoint();
        float determinant = det();

        for(char i = 0; i < 3; i++) {
            invMat.mat[i][0] /= determinant;
            invMat.mat[i][1] /= determinant;
            invMat.mat[i][2] /= determinant;
        }

        return invMat;
    }

    // Getters & setters
    float& operator()(int i, int j) {
        return mat.at(i % 3).at(j % 3);
    }

    float operator()(int i, int j) const {
        return mat.at(i % 3).at(j % 3);
    }

    // toString()
    friend ostream& operator<< (ostream& os, const Matrix3& obj) {
        for(const vector<float>& row: obj.mat) {
            for(const float ele: row)
                os << ele << ' ';
            os << endl;
        }

        return os;
    }
};

#endif