#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include <iostream>
#include <vector>

using namespace std;

class Matrix {
    private:
    vector<vector<float>> _mat;
    uint16_t _m, _n;

    public:
    // Default contructor
    Matrix(const uint16_t m, const uint16_t n): _mat(m, vector<float>(n, 0.0f)) {}

    // Construct with values
    Matrix(const uint16_t m, const uint16_t n, float* matrix): _mat(m, vector<float>(n)) {
        for(uint16_t i = 0; i < m; i++) {
            float* ptr = matrix + i * n;

            copy(ptr, ptr + n, _mat[i]);
        }
    }

    Matrix(const uint16_t m, const uint16_t n, const float** matrix): _mat(m, vector<float>(n)) {
        for(uint16_t i = 0; i < m; i++)
            copy(matrix[i], matrix[i] + n, _mat[i].begin());
    }

    // In place constructor
    Matrix(vector<vector<float>>& matrix) {
        _mat = matrix;
    }

    // Scalar matrix
    Matrix(const uint16_t m, const uint16_t n, const float scalar): _mat(m, vector<float>(n, 0.0f)) {
        uint16_t lim = min(n, m);
        
        for(uint16_t i = 0; i < lim; i++)
            _mat[i][i] = scalar;
    }

    // Deconstruct matrix into a flat array
    void toArray(float* res) const {
        for(uint16_t i = 0; i < 3; i++)
            copy(_mat[i].begin(), _mat[i].end(), res + i * _n);
    }

    // Operator overloading
    Matrix operator+(const Matrix& obj) const {
        vector<vector<float>> res = vector<vector<float>>(obj.M(), vector<float>(obj.N()));

        for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++)
                res[i][j] = _mat[i][j] + obj._mat[i][j];

        return Matrix(res);
    }

    Matrix operator+() const {
        return Matrix(*this);
        // Unary plus forces pass-by-ref to be pass-by-value
    }

    Matrix operator-(const Matrix& obj) const {
        vector<vector<float>> res = vector<vector<float>>(obj.M(), vector<float>(obj.N()));

        for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++)
                res[i][j] = _mat[i][j] - obj._mat[i][j];

        return Matrix(res);
    }

    Matrix operator-() const {
        vector<vector<float>> res = vector<vector<float>>(M(), vector<float>(N()));

        for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++)
                res[i][j] = -_mat[i][j];

        return Matrix(res);
        // Unary minus forces pass-by-ref to be pass-by-value
    }

    Matrix operator*(const float scalar) const {
        vector<vector<float>> res = vector<vector<float>>(M(), vector<float>(N()));

        for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++)
                res[i][j] = _mat[i][j] * scalar;

        return Matrix(res);
    }

    Matrix operator*(const Matrix& obj) const {
        vector<vector<float>> res = vector<vector<float>>(obj.M(), vector<float>(obj.N()));

        for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++)
                for(uint16_t k = 0; k < 3; k++)
                    res[i][j] += _mat[i][k] * obj._mat[k][j];

        return Matrix(res);
    }

    // Operator overload delibrately doesn't support division by matrix.
    // Use "A * ~B"
    // Or "A * B.inverse()"
    inline Matrix operator/(const float scalar) const{
        static Matrix nullMat = Matrix(M(), N());
        
        if(scalar != 0.0f)
            return operator*(1.0f / scalar);
        else
            return nullMat;
    }

    Matrix& operator=(const Matrix& obj) {
        _mat = obj._mat;

        return *this;
    }

    Matrix& operator=(const float obj[3][3]) {
        for(uint16_t i = 0; i < 3; i++) {
            vector<float> row(3);
            copy(begin(obj[i]), end(obj[i]), row.begin());
            _mat.push_back(row);
        }

        return *this;
    }

    Matrix& operator+=(const Matrix& obj) {
        for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++)
                _mat[i][j] += obj._mat[i][j];

        return *this;
    }

    Matrix& operator-=(const Matrix& obj) {
        for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++)
                _mat[i][j] -= obj._mat[i][j];

        return *this;
    }

    Matrix& operator*=(const float scalar) {
       for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++)
                _mat[i][j] *= scalar;

        return *this;
    }

    Matrix& operator*=(const Matrix& obj) {
        vector<vector<float>> res = vector<vector<float>>(obj.M(), vector<float>(obj.N()));

        for(uint16_t i = 0; i < 3; i++) {
            for(uint16_t j = 0; j < 3; j++)
                for(uint16_t k = 0; k < 3; k++)
                    res[i][j] += _mat[i][k] * obj._mat[k][j];

            copy(begin(res[i]), end(res[i]), _mat[i].begin());
        }

        return *this;
    }

    // Operator overload delibrately doesn't support division by matrix.
    // Use "A *= ~B"
    // Or "A *= B.inverse()"
    inline Matrix& operator/=(const float scalar) {
        if(scalar != 0.0f)
            operator*=( 1.0f / scalar);

        return *this;
    }

    bool operator==(const Matrix& obj) const {
        return (
            _mat[0] == obj._mat[0] &&
            _mat[1] == obj._mat[1] &&
            _mat[2] == obj._mat[2]
        );
    }

    inline bool operator!=(const Matrix& obj) const {
        return !operator==(obj);
    }

    // Inverse operator shorthand
    inline Matrix operator~() {
        return inverse();
    }

    // Special functions
    // These are unique to the class
    inline bool isSquare() const {
        return _m == _n;
    }

    float trace() const {
        float trace = 0.0f;

        for(uint16_t i = 0; i < 3; i++)
            trace += _mat[i][i];

        return trace;
    }

    float det() const {
        float det = 0.0f;

        // Positive multiplication terms
        for(uint16_t i = 0; i < 3; i++)
            det += _mat[i % 3][0] * _mat[(i + 1) % 3][1] * _mat[(i + 2) % 3][2];

        // Negative multiplication terms
        for(uint16_t i = 0; i < 3; i++)
            det -= _mat[i % 3][2] * _mat[(i + 1) % 3][1] * _mat[(i + 2) % 3][0];

        return det;
    }

    Matrix trans() const {
        vector<vector<float>> res = vector<vector<float>>(M(), vector<float>(N()));

        for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++)
                res[i][j] = _mat[j][i];

        return Matrix(res);
    }

    Matrix adjoint() const {
        vector<vector<float>> res = vector<vector<float>>(M(), vector<float>(N()));
        float cof[2][2] = {};
        int iCof, jCof;

        for(uint16_t i = 0; i < 3; i++)
            for(uint16_t j = 0; j < 3; j++) {
                iCof = jCof = 0;

                //Cofactor matrix
                for(uint16_t row = 0; row < 3; row++)
                    for(uint16_t col = 0; col < 3; col++)
                        if(row != i && col != j) {
                            cof[iCof][jCof++] = _mat[row][col];
                            
                            if(jCof == 2) {
                                jCof = 0;
                                iCof++;
                            }
                        }

                //Determinant
                res[i][j] = cof[0][0] * cof[1][1] - cof[0][1] * cof[1][0];
            }

        return Matrix(res);
    }

    Matrix inverse() const {
        static Matrix nullMat = Matrix(M(), N());

        Matrix invMat = adjoint();
        float determinant = det();

        if (determinant != 0.0f) {
            for(uint16_t i = 0; i < 3; i++) {
                invMat._mat[i][0] /= determinant;
                invMat._mat[i][1] /= determinant;
                invMat._mat[i][2] /= determinant;
            }

            return invMat;
        }
        else
            return nullMat;
    }

    // Getters & setters
    float& operator()(int i, int j) {
        return _mat[i % 3][j % 3];
    }

    float operator()(int i, int j) const {
        return _mat[i % 3][j % 3];
    }

    inline uint16_t M() const {
        return _m;
    }

    inline uint16_t N() const {
        return _n;
    }

    // toString()
    // "a b c\n"
    // "x y z\n"
    // "p q r\n"
    friend ostream& operator<< (ostream& os, const Matrix& obj) {
        for(const vector<float>& row: obj._mat) {
            for(const float ele: row)
                os << ele << ' ';
            os << endl;
        }

        return os;
    }
};

// Additional overload to reflect commutative property of scalar multiplication
inline Matrix operator*(const float scalar, const Matrix obj) {
    return obj * scalar;
}

#endif