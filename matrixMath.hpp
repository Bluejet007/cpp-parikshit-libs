#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include <iostream>
#include <vector>

using namespace std;

static Matrix failMatrix = Matrix(0, 0);

class Matrix {
    private:
    vector<vector<float>> _mat;
    uint16_t _rows, _cols;

    public:
    // Construct with dimensions
    Matrix(const uint16_t m, const uint16_t n): _mat(m, vector<float>(n, 0.0f)), _rows(m) , _cols(n) {}

    // Construct with values from a flat array
    Matrix(const uint16_t m, const uint16_t n, float* matrix): _mat(m, vector<float>(n)), _rows(m) , _cols(n) {
        for(uint16_t i = 0; i < m; i++) {
            float* ptr = matrix + i * n;

            copy(ptr, ptr + n, _mat[i]);
        }
    }

    // Construct with values from a dynamically allocated array
    Matrix(const uint16_t m, const uint16_t n, const float** matrix): _mat(m, vector<float>(n)), _rows(m) , _cols(n) {
        for(uint16_t i = 0; i < m; i++)
            copy(matrix[i], matrix[i] + n, _mat[i].begin());
    }

    // Construct with values from a vector grid
    Matrix(vector<vector<float>>& matrix): _mat(matrix), _rows(matrix.size()) {
        _cols = matrix.size() > 0 ? matrix[0].size() : 0;
    }

    // Scalar matrix
    Matrix(const uint16_t m, const uint16_t n, const float scalar): _mat(m, vector<float>(n, 0.0f)), _rows(m) , _cols(n) {
        uint16_t lim = min(n, m);
        
        for(uint16_t i = 0; i < lim; i++)
            _mat[i][i] = scalar;
    }

    // Deconstruct matrix into a flat array
    void toArray(float* res) const {
        for(uint16_t i = 0; i < _rows; i++)
            copy(_mat[i].begin(), _mat[i].end(), res + i * _cols);
    }

    // Operator overloading
    Matrix operator+(const Matrix& obj) const {
        if(_rows != obj.rows() || _cols != obj.cols())
            return failMatrix;

        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(_cols));

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                res[i][j] = _mat[i][j] + obj._mat[i][j];

        return Matrix(res);
    }

    Matrix operator+() const {
        return Matrix(*this);
        // Unary plus forces pass-by-ref to be pass-by-value
    }

    Matrix operator-(const Matrix& obj) const {
        if(_rows != obj.rows() || _cols != obj.cols())
            return failMatrix;

        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(_cols));

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                res[i][j] = _mat[i][j] - obj._mat[i][j];

        return Matrix(res);
    }

    Matrix operator-() const {
        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(_cols));

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                res[i][j] = -_mat[i][j];

        return Matrix(res);
        // Unary minus forces pass-by-ref to be pass-by-value
    }

    friend Matrix operator*(const Matrix obj, const float scalar) {
        vector<vector<float>> res = vector<vector<float>>(obj.rows(), vector<float>(obj.cols()));

        for(uint16_t i = 0; i < obj._rows; i++)
            for(uint16_t j = 0; j < obj._cols; j++)
                res[i][j] = obj._mat[i][j] * scalar;

        return Matrix(res);
    }

    Matrix operator*(const Matrix& obj) const {
        if(_cols != obj.rows())
            return failMatrix;

        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(obj.cols(), 0.0f));

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < obj._cols; j++)
                for(uint16_t k = 0; k < _cols; k++)
                    res[i][j] += _mat[i][k] * obj._mat[k][j];

        return Matrix(res);
    }

    // Operator overload delibrately doesn't support division by matrix.
    // Use "A * ~B"
    // Or "A * B.inverse()"
    inline Matrix operator/(const float scalar) {
        if(scalar != 0.0f)
            return *this * (1.0f / scalar);
        else
            return failMatrix;
    }

    Matrix& operator=(const Matrix& obj) {
        if(this == &obj)
            return *this;

        _mat = obj._mat;
        _rows = obj._rows;
        _cols = obj._cols;

        return *this;
    }

    Matrix& operator+=(const Matrix& obj) {
        if(_rows != obj.rows() || _cols != obj.cols())
            return failMatrix;

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                _mat[i][j] += obj._mat[i][j];

        return *this;
    }

    Matrix& operator-=(const Matrix& obj) {
        if(_rows != obj.rows() || _cols != obj.cols())
            return failMatrix;

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                _mat[i][j] -= obj._mat[i][j];

        return *this;
    }

    Matrix& operator*=(const float scalar) {
        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                _mat[i][j] *= scalar;

        return *this;
    }

    Matrix& operator*=(const Matrix& obj) {
        if(_cols != obj.rows())
            return failMatrix;

        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(obj.cols()));

        for(uint16_t i = 0; i < _rows; i++) {
            for(uint16_t j = 0; j < obj._cols; j++)
                for(uint16_t k = 0; k < _cols; k++)
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
        if(_rows != obj.rows() || _cols != obj.cols())
            return false;
        else
            for(uint16_t i = 0; i < _rows; i++)
                if(_mat[i] != obj._mat[i])
                    return false;

        return true;
    }

    inline bool operator!=(const Matrix& obj) const {
        return !operator==(obj);
    }

    // Inverse operator shorthand
    /*inline Matrix operator~() {
        return inverse();
    }*/

    // Special functions
    // These are unique to the class
    inline bool isSquare() const {
        return _rows == _cols;
    }

    float trace() const {
        float trace = 0.0f;

        for(uint16_t i = 0; i < 3; i++)
            trace += _mat[i][i];

        return trace;
    }

    float det() const {
        if(!isSquare())
            return 0.0f;

        float det = 0.0f;
        Matrix tempMat = Matrix(*this);

        for (uint16_t i = 0; i < _rows; i++) {
            int pivot = i;
            for (uint16_t j = i + 1; j < _rows; j++) {
                if (abs(tempMat(j, i)) > abs(tempMat(pivot, i))) {
                    pivot = j;
                }
            }

            if (pivot != i) {
                vector<float> temp = tempMat._mat[i];
                tempMat._mat[i] = tempMat._mat[pivot];
                tempMat._mat[pivot] = temp;

                det *= -1.0f;
            }

            if (tempMat(i, i) == 0.0f)
                return 0.0f;

            det *= tempMat(i, i);
            for (uint16_t j = i + 1; j < _rows; j++) {
                double factor = tempMat(j, i) / tempMat(i, i);
                for (int k = i + 1; k < _rows; k++) {
                    tempMat(j, k) -= factor * tempMat(i, k);
                }
            }
        }

        return det;
    }

    Matrix trans() const {
        vector<vector<float>> res = vector<vector<float>>(_cols, vector<float>(_rows));

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                res[j][i] = _mat[i][j];

        return Matrix(res);
    }

    /*Matrix adjoint() const {
        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(_cols));
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
        static Matrix nullMat = Matrix(_rows, _cols);

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
    }*/

    // Getters & setters
    inline uint16_t rows() const {
        return _rows;
    }

    inline uint16_t cols() const {
        return _cols;
    }

    float& operator()(int i, int j) {
        return _mat[i % _rows][j % _cols];
    }

    float operator()(int i, int j) const {
        return _mat[i % _rows][j % _cols];
    }

    vector<float>& operator()(int i) {
        return _mat[i % _rows];
    }

    vector<float> operator()(int i) const {
        return _mat[i % _rows];
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

#endif