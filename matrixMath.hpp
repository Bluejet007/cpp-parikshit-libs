#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include <cstdint>

using namespace std;

class Matrix {
    private:
    vector<vector<float>> _mat;
    uint16_t _rows, _cols;

    public:
    // Construct matrix with given shape.
    Matrix(const uint16_t m, const uint16_t n): _mat(m, vector<float>(n)), _rows(m) , _cols(n) {}

    // Inline static initialisation. The shape must be passed with the array.
    Matrix(const initializer_list<initializer_list<float>> matrix): _mat(matrix.size()), _rows(matrix.size()) {
        _cols = matrix.size() != 0 ? matrix.begin() ->size() : 0;

        for(uint16_t i = 0; i < _rows; i++) {
            vector<float> vec = vector<float>(_cols);

            auto row = *(matrix.begin() + i);

            copy(row.begin(), row.end(), vec.begin());
            _mat[i] = vec;
        }
    }

    // Construct with values from a flat array. The shape must be passed with the array.
    Matrix(const uint16_t m, const uint16_t n, float* matrix): _mat(m, vector<float>(n)), _rows(m) , _cols(n) {
        for(uint16_t i = 0; i < m; i++) {
            float* ptr = matrix + i * n;

            copy(ptr, ptr + n, _mat[i].begin());
        }
    }

    // Construct with values from a dynamically allocated array. The shape must be passed with the array.
    Matrix(const uint16_t m, const uint16_t n, float** matrix): _mat(m, vector<float>(n)), _rows(m) , _cols(n) {
        for(uint16_t i = 0; i < m; i++)
            copy(matrix[i], matrix[i] + n, _mat[i].begin());
    }

    // Wrap a vector of vectors as a matrix.
    // Matrix(vector<vector<float>>& matrix): _mat(matrix), _rows(matrix.size()) {
    //     _cols = matrix.size() > 0 ? matrix[0].size() : 0;
    // }

    // Construct with values from a vector of vectors.
    Matrix(const vector<vector<float>>& matrix): _mat(matrix), _rows(matrix.size()) {
        _cols = matrix.size() > 0 ? matrix[0].size() : 0;
    }

    // Contruct a scalar matrix. The shape must be passed with the value, which can be non-square.
    Matrix(const uint16_t m, const uint16_t n, const float scalar): _mat(m, vector<float>(n, 0.0f)), _rows(m) , _cols(n) {
        uint16_t lim = min(n, m);
        
        for(uint16_t i = 0; i < lim; i++)
            _mat[i][i] = scalar;
    }

    // Deconstruct matrix into a flat array.
    void toArray(float*& res) {
        for(uint16_t i = 0; i < _rows; i++)
            copy(_mat[i].begin(), _mat[i].end(), res + i * _cols);
    }

    // Deconstruct matrix into a dynamically allocated array.
    void toArray(float**& res) const {
        for(uint16_t i = 0; i < _rows; i++) {
            copy(_mat[i].begin(), _mat[i].end(), res[i]);
        }
    }

    // Operator overloading

    Matrix operator+(const Matrix& obj) const {
        if(_rows != obj._rows || _cols != obj._cols)
            return Matrix(0, 0);

        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(_cols));

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                res[i][j] = _mat[i][j] + obj._mat[i][j];

        return Matrix(res);
    }

    // Shorthand to create a copy.
    Matrix operator+() const {
        return Matrix(*this);
    }

    Matrix operator-(const Matrix& obj) const {
        if(_rows != obj._rows || _cols != obj._cols)
            return Matrix(0, 0);

        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(_cols));

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                res[i][j] = _mat[i][j] - obj._mat[i][j];

        return Matrix(res);
    }

    // Shorthand to create a negated copy.
    Matrix operator-() const {
        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(_cols));

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < _cols; j++)
                res[i][j] = -_mat[i][j];

        return Matrix(res);
    }

    friend Matrix operator*(const Matrix obj, const float scalar) {
        vector<vector<float>> res = vector<vector<float>>(obj._rows, vector<float>(obj._cols));

        for(uint16_t i = 0; i < obj._rows; i++)
            for(uint16_t j = 0; j < obj._cols; j++)
                res[i][j] = obj._mat[i][j] * scalar;

        return Matrix(res);
    }

    Matrix operator*(const Matrix& obj) const {
        if(_cols != obj._rows)
            return Matrix(0, 0);

        vector<vector<float>> res = vector<vector<float>>(_rows, vector<float>(obj._cols, 0.0f));

        for(uint16_t i = 0; i < _rows; i++)
            for(uint16_t j = 0; j < obj._cols; j++)
                for(uint16_t k = 0; k < _cols; k++)
                    res[i][j] += _mat[i][k] * obj._mat[k][j];

        return Matrix(res);
    }

    // Operator overload delibrately doesn't support division by matrix.
    // Use "A * B.inverse()"
    inline Matrix operator/(const float scalar) {
        if(scalar != 0.0f)
            return *this * (1.0f / scalar);
        else
            return Matrix(0, 0);
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
        if(_rows == obj._rows || _cols == obj._cols)
            for(uint16_t i = 0; i < _rows; i++)
                for(uint16_t j = 0; j < _cols; j++)
                    _mat[i][j] += obj._mat[i][j];

        return *this;
    }

    Matrix& operator-=(const Matrix& obj) {
        if(_rows == obj._rows || _cols == obj._cols)
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
        if(_cols == obj._rows) {
            vector<float> resRow = vector<float>(obj._cols);

            for(uint16_t i = 0; i < _rows; i++) {
                fill(resRow.begin(), resRow.end(), 0.0f);

                for(uint16_t j = 0; j < obj._cols; j++)
                    for(uint16_t k = 0; k < _cols; k++)
                        resRow[j] += _mat[i][k] * obj._mat[k][j];

                _mat[i].resize(obj._cols);
                copy(resRow.begin(), resRow.end(), _mat[i].begin());
            }

        }

        _cols = obj._cols;

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
        if(_rows != obj._rows || _cols != obj._cols)
            return false;
        else
            return _mat == obj._mat;
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

        float det = 1.0f;
        Matrix tempMat = Matrix(*this);

        for(uint16_t i = 0; i < _rows; i++) {
            int pivot = i;
            for(uint16_t j = i + 1; j < _rows; j++) {
                if (abs(tempMat._mat[j][i]) > abs(tempMat._mat[pivot][i])) {
                    pivot = j;
                }
            }

            if(pivot != i) {
                vector<float> temp = tempMat._mat[i];
                tempMat._mat[i] = tempMat._mat[pivot];
                tempMat._mat[pivot] = temp;

                det *= -1.0f;
            }

            if(tempMat._mat[i][i] == 0.0f)
                return 0.0f;

            det *= tempMat._mat[i][i];
            for(uint16_t j = i + 1; j < _rows; j++) {
                double factor = tempMat._mat[j][i] / tempMat._mat[i][i];

                for (int k = i + 1; k < _rows; k++) {
                    tempMat._mat[j][k] -= factor * tempMat._mat[i][k];
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

    Matrix inverse() const {
        if(!isSquare())
            return Matrix(0, 0);

        Matrix adjMat = Matrix(_rows, _cols, 1);
        Matrix tempMat = Matrix(*this);

        for(uint16_t i = 0; i < _rows; i++) {
            int pivot = i;
            for(uint16_t j = i + 1; j < _rows; j++) {
                if (abs(tempMat._mat[j][i]) > abs(tempMat._mat[pivot][i])) {
                    pivot = j;
                }
            }

            if(pivot != i) {
                swap(tempMat._mat[i], tempMat._mat[pivot]);
                swap(adjMat._mat[i], adjMat._mat[pivot]);
            }

            if(tempMat._mat[i][i] == 0.0f)
                return Matrix(0, 0);


            float factor = tempMat._mat[i][i];
            for(uint16_t k = 0; k < _cols; k++) {
                    if(k >= i) tempMat._mat[i][k] /= factor;
                    adjMat._mat[i][k] /= factor;
            }

            for(uint16_t j = 0; j < _rows; j++) {
                if(j == i)
                    continue;

                factor = tempMat._mat[j][i];

                for (uint16_t k = 0; k < _cols; k++) {
                    if(k >= i) tempMat._mat[j][k] -= factor * tempMat._mat[i][k];
                    adjMat._mat[j][k] -= factor * adjMat._mat[i][k];
                }
            }
        }

        return adjMat;
    }

    Matrix adj() const {
        float determinant = det();

        return inverse() * determinant;
    }

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