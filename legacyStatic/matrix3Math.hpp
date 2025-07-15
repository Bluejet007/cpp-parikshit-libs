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
            mat[i][i] = scalar;
        }
    }

    // Deconstruct matrix into normal arrays
    void toArray(float res[3][3]) {
        for(char i = 0; i < 3; i++)
            copy(mat[i].begin(), mat[i].end(), begin(res[i]));
    }

    // Operator overloading
    Matrix3 operator+(const Matrix3& obj) const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = mat[i][j] + obj.mat[i][j];

        return Matrix3(res);
    }

    // Unary plus forces pass-by-ref to be pass-by-value
    Matrix3 operator+() const {
        return Matrix3(*this);
    }

    Matrix3 operator-(const Matrix3& obj) const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = mat[i][j] - obj.mat[i][j];

        return Matrix3(res);
    }

    Matrix3 operator-() const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = -mat[i][j];

        return Matrix3(res);
    }

    Matrix3 operator*(const float scalar) const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = mat[i][j] * scalar;

        return Matrix3(res);
    }

    Matrix3 operator*(const Matrix3& obj) const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                for(char k = 0; k < 3; k++)
                    res[i][j] += mat[i][k] * obj.mat[k][j];

        return Matrix3(res);
    }

    // Operator overload delibrately doesn't support division by matrix.
    // Use "A * ~B"
    // Or "A * B.inverse()"
    inline Matrix3 operator/(const float scalar) const{
        static Matrix3 nullMat = Matrix3();
        
        if(scalar != 0.0f)
            return operator*(1.0f / scalar);
        else
            return nullMat;
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
                mat[i][j] += obj.mat[i][j];

        return *this;
    }

    Matrix3& operator-=(const Matrix3& obj) {
        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                mat[i][j] -= obj.mat[i][j];

        return *this;
    }

    Matrix3& operator*=(const float scalar) {
       for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                mat[i][j] *= scalar;

        return *this;
    }

    Matrix3& operator*=(const Matrix3& obj) {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++) {
            for(char j = 0; j < 3; j++)
                for(char k = 0; k < 3; k++)
                    res[i][j] += mat[i][k] * obj.mat[k][j];

            copy(begin(res[i]), end(res[i]), mat[i].begin());
        }

        return *this;
    }

    // Operator overload delibrately doesn't support division by matrix.
    // Use "A *= ~B"
    // Or "A *= B.inverse()"
    inline Matrix3& operator/=(const float scalar) {
        if(scalar != 0.0f)
            operator*=( 1.0f / scalar);

        return *this;
    }

    bool operator==(const Matrix3& obj) const {
        return (
            mat[0] == obj.mat[0] &&
            mat[1] == obj.mat[1] &&
            mat[2] == obj.mat[2]
        );
    }

    inline bool operator!=(const Matrix3& obj) const {
        return !operator==(obj);
    }

    // Inverse operator shorthand
    inline Matrix3 operator~() {
        return inverse();
    }

    // Special functions
    // These are unique to the class
    Matrix3 trans() const {
        float res[3][3] = {};

        for(char i = 0; i < 3; i++)
            for(char j = 0; j < 3; j++)
                res[i][j] = mat[j][i];

        return Matrix3(res);
    }

    float trace() const {
        float trace = 0.0f;

        for(char i = 0; i < 3; i++)
            trace += mat[i][i];

        return trace;
    }

    float det() const {
        float det = 0.0f;

        // Positive multiplication terms
        for(char i = 0; i < 3; i++)
            det += mat[i % 3][0] * mat[(i + 1) % 3][1] * mat[(i + 2) % 3][2];

        // Negative multiplication terms
        for(char i = 0; i < 3; i++)
            det -= mat[i % 3][2] * mat[(i + 1) % 3][1] * mat[(i + 2) % 3][0];

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
                            cof[iCof][jCof++] = mat[row][col];
                            
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
        static Matrix3 nullMat = Matrix3();

        Matrix3 invMat = adjoint();
        float determinant = det();

        if (determinant != 0.0f) {
            for(char i = 0; i < 3; i++) {
                invMat.mat[i][0] /= determinant;
                invMat.mat[i][1] /= determinant;
                invMat.mat[i][2] /= determinant;
            }

            return invMat;
        }
        else
            return nullMat;
    }

    // Getters & setters
    float& operator()(int i, int j) {
        return mat[i % 3][j % 3];
    }

    float operator()(int i, int j) const {
        return mat[i % 3][j % 3];
    }

    // toString()
    // "a b c\n"
    // "x y z\n"
    // "p q r\n"
    friend ostream& operator<< (ostream& os, const Matrix3& obj) {
        for(const vector<float>& row: obj.mat) {
            for(const float ele: row)
                os << ele << ' ';
            os << endl;
        }

        return os;
    }
};

// Additional overload to reflect commutative property of scalar multiplication
inline Matrix3 operator*(const float scalar, const Matrix3 obj) {
    return obj * scalar;
}

#endif