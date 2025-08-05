#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#ifdef _USE_MATRIX_PRINT
    #include <iostream>
#endif

#include <vector>
#include <initializer_list>
#include <cstdint>

 // Conditional user defines:
 // _USE_MATRIX_PRINT       - Imports <iostream> and enables the print function.
 // _USE_MATRIX_SHORTHANDS  - Enables the shorthand operators "~A" for quick inverse and "+A" for quick copy.

class Matrix {
    private:
    std::vector<std::vector<float>> _mat;
    std::uint16_t _rows, _cols;

    public:
    /* Constructors */
    Matrix(const std::uint16_t m, const std::uint16_t n);
    Matrix(const std::initializer_list<std::initializer_list<float>> matrix);
    Matrix(const std::uint16_t m, const std::uint16_t n, float* matrix);
    Matrix(const std::uint16_t m, const std::uint16_t n, float** matrix);
    Matrix(const std::vector<std::vector<float>>& matrix);
    Matrix(const std::uint16_t m, const std::uint16_t n, const float scalar);

    /* Deconstructors */
    void toArray(float*& res) const;
    void toArray(float**& res) const;
    std::vector<std::vector<float>> toVectors() const;

    /* Arithmetic perators */
    Matrix operator+(const Matrix& otherMatrix) const;
    Matrix operator-(const Matrix& otherMatrix) const;
    Matrix operator-() const;
    friend Matrix operator*(const Matrix otherMatrix, const float scalar);
    Matrix operator*(const Matrix& otherMatrix) const;
    inline Matrix operator/(const float scalar);

    /* Assignment operators */
    Matrix& operator=(const Matrix& otherMatrix);
    Matrix& operator+=(const Matrix& otherMatrix);
    Matrix& operator-=(const Matrix& otherMatrix);
    Matrix& operator*=(const float scalar);
    Matrix& operator*=(const Matrix& otherMatrix);
    inline Matrix& operator/=(const float scalar);

    /* Equality operators */
    bool operator==(const Matrix& otherMatrix) const;
    inline bool operator!=(const Matrix& otherMatrix) const;

    /* Matrix operations */
    inline bool isSquare() const;
    float trace() const;
    float det() const;
    Matrix trans() const;
    Matrix inverse() const;
    Matrix adj() const;

    /* Getters & setters */
    inline std::uint16_t rows() const;
    inline std::uint16_t cols() const;
    float& operator()(std::uint16_t i, std::uint16_t j);
    float operator()(std::uint16_t i, std::uint16_t j) const;
    std::vector<float>& operator()(std::uint16_t i);
    std::vector<float> operator()(std::uint16_t i) const;

    /* toString() */
    #ifdef _USE_MATRIX_PRINT
    friend std::ostream& operator<<(std::ostream& os, const Matrix& otherMatrix);
    #endif

    /* Additional shorthand operators */
    #ifdef _USE_MATRIX_SHORTHANDS
    inline Matrix operator~();
    Matrix operator+() const;
    #endif
};


// Construct matrix with given shape.
Matrix::Matrix(const std::uint16_t m, const std::uint16_t n): _mat(m, std::vector<float>(n)), _rows(m) , _cols(n) {}

// Inline static initialisation. The shape must be passed with the array.
Matrix::Matrix(const std::initializer_list<std::initializer_list<float>> matrix): _mat(matrix.size()), _rows(matrix.size()) {
    _cols = matrix.size() != 0 ? matrix.begin() ->size() : 0;

    for(std::uint16_t i = 0; i < _rows; i++) {
        std::vector<float> vec = std::vector<float>(_cols);

        auto row = *(matrix.begin() + i);

        copy(row.begin(), row.end(), vec.begin());
        _mat[i] = vec;
    }
}

// Construct with values from a flat array. The shape must be passed with the array.
Matrix::Matrix(const std::uint16_t m, const std::uint16_t n, float* matrix): _mat(m, std::vector<float>(n)), _rows(m) , _cols(n) {
    for(std::uint16_t i = 0; i < m; i++) {
        float* ptr = matrix + i * n;

        copy(ptr, ptr + n, _mat[i].begin());
    }
}

// Construct with values from a dynamically allocated array. The shape must be passed with the array.
Matrix::Matrix(const std::uint16_t m, const std::uint16_t n, float** matrix): _mat(m, std::vector<float>(n)), _rows(m) , _cols(n) {
    for(std::uint16_t i = 0; i < m; i++)
        copy(matrix[i], matrix[i] + n, _mat[i].begin());
}

// Construct with values from a vector of vectors.
Matrix::Matrix(const std::vector<std::vector<float>>& matrix): _mat(matrix), _rows(matrix.size()) {
    _cols = matrix.size() > 0 ? matrix[0].size() : 0;
}

// Contruct a scalar matrix. The shape must be passed with the value, which can be non-square.
Matrix::Matrix(const std::uint16_t m, const std::uint16_t n, const float scalar): _mat(m, std::vector<float>(n, 0.0f)), _rows(m) , _cols(n) {
    std::uint16_t lim = std::min(n, m);
    
    for(std::uint16_t i = 0; i < lim; i++)
        _mat[i][i] = scalar;
}

// Deconstruct matrix into a flat array.
void Matrix::toArray(float*& res) const {
    for(std::uint16_t i = 0; i < _rows; i++)
        copy(_mat[i].begin(), _mat[i].end(), res + i * _cols);
}

// Deconstruct matrix into a dynamically allocated array.
void Matrix::toArray(float**& res) const {
    for(std::uint16_t i = 0; i < _rows; i++) {
        copy(_mat[i].begin(), _mat[i].end(), res[i]);
    }
}

// Deconstruct matrix into a vector of vectors.
std::vector<std::vector<float>> Matrix::toVectors() const {
    return _mat;
}

/* Operator overloading */

// Element-wise addition.
Matrix Matrix::operator+(const Matrix& otherMatrix) const {
    if(_rows != otherMatrix._rows || _cols != otherMatrix._cols)
        return Matrix(0, 0);

    std::vector<std::vector<float>> res = std::vector<std::vector<float>>(_rows, std::vector<float>(_cols));

    for(std::uint16_t i = 0; i < _rows; i++)
        for(std::uint16_t j = 0; j < _cols; j++)
            res[i][j] = _mat[i][j] + otherMatrix._mat[i][j];

    return Matrix(res);
}

// Element-wise subtraction.
Matrix Matrix::operator-(const Matrix& otherMatrix) const {
    if(_rows != otherMatrix._rows || _cols != otherMatrix._cols)
        return Matrix(0, 0);

    std::vector<std::vector<float>> res = std::vector<std::vector<float>>(_rows, std::vector<float>(_cols));

    for(std::uint16_t i = 0; i < _rows; i++)
        for(std::uint16_t j = 0; j < _cols; j++)
            res[i][j] = _mat[i][j] - otherMatrix._mat[i][j];

    return Matrix(res);
}

// Shorthand to create a negated copy.
Matrix Matrix::operator-() const {
    std::vector<std::vector<float>> res = std::vector<std::vector<float>>(_rows, std::vector<float>(_cols));

    for(std::uint16_t i = 0; i < _rows; i++)
        for(std::uint16_t j = 0; j < _cols; j++)
            res[i][j] = -_mat[i][j];

    return Matrix(res);
}

// Scalar multiplication. Equivalent to "A * sI".
Matrix operator*(const Matrix otherMatrix, const float scalar) {
    std::vector<std::vector<float>> res = std::vector<std::vector<float>>(otherMatrix._rows, std::vector<float>(otherMatrix._cols));

    for(std::uint16_t i = 0; i < otherMatrix._rows; i++)
        for(std::uint16_t j = 0; j < otherMatrix._cols; j++)
            res[i][j] = otherMatrix._mat[i][j] * scalar;

    return Matrix(res);
}

// Matrix dot product.
Matrix Matrix::operator*(const Matrix& otherMatrix) const {
    if(_cols != otherMatrix._rows)
        return Matrix(0, 0);

    std::vector<std::vector<float>> res = std::vector<std::vector<float>>(_rows, std::vector<float>(otherMatrix._cols, 0.0f));

    for(std::uint16_t i = 0; i < _rows; i++)
        for(std::uint16_t j = 0; j < otherMatrix._cols; j++)
            for(std::uint16_t k = 0; k < _cols; k++)
                res[i][j] += _mat[i][k] * otherMatrix._mat[k][j];

    return Matrix(res);
}

// Scalar division. Equivalent to "A * (1/s)I"
inline Matrix Matrix::operator/(const float scalar) {
    if(scalar != 0.0f)
        return *this * (1.0f / scalar);
    else
        return Matrix(0, 0);
}

// Standard assignment.
Matrix& Matrix::operator=(const Matrix& otherMatrix) {
    if(this == &otherMatrix)
        return *this;

    _mat = otherMatrix._mat;
    _rows = otherMatrix._rows;
    _cols = otherMatrix._cols;

    return *this;
}

// In-place addition. Doesn't use extra memory.
Matrix& Matrix::operator+=(const Matrix& otherMatrix) {
    if(_rows == otherMatrix._rows || _cols == otherMatrix._cols)
        for(std::uint16_t i = 0; i < _rows; i++)
            for(std::uint16_t j = 0; j < _cols; j++)
                _mat[i][j] += otherMatrix._mat[i][j];

    return *this;
}

// In-place subtraction. Doesn't use extra memory.
Matrix& Matrix::operator-=(const Matrix& otherMatrix) {
    if(_rows == otherMatrix._rows || _cols == otherMatrix._cols)
        for(std::uint16_t i = 0; i < _rows; i++)
            for(std::uint16_t j = 0; j < _cols; j++)
                _mat[i][j] -= otherMatrix._mat[i][j];

    return *this;
}

// In-place scalar multiplication. Equivalent to "A * sI". Doesn't use extra memory.
Matrix& Matrix::operator*=(const float scalar) {
    for(std::uint16_t i = 0; i < _rows; i++)
        for(std::uint16_t j = 0; j < _cols; j++)
            _mat[i][j] *= scalar;

    return *this;
}

// Perform dot product & assign. Uses reduced extra memory.
Matrix& Matrix::operator*=(const Matrix& otherMatrix) {
    if(_cols == otherMatrix._rows) {
        std::vector<float> resRow = std::vector<float>(otherMatrix._cols);

        for(std::uint16_t i = 0; i < _rows; i++) {
            fill(resRow.begin(), resRow.end(), 0.0f);

            for(std::uint16_t j = 0; j < otherMatrix._cols; j++)
                for(std::uint16_t k = 0; k < _cols; k++)
                    resRow[j] += _mat[i][k] * otherMatrix._mat[k][j];

            _mat[i].resize(otherMatrix._cols);
            copy(resRow.begin(), resRow.end(), _mat[i].begin());
        }

    }

    _cols = otherMatrix._cols;

    return *this;
}

// In-place scalar multiplication. Equivalent to "A * (1/s)I". Doesn't use extra memory.
inline Matrix& Matrix::operator/=(const float scalar) {
    if(scalar != 0.0f)
        operator*=( 1.0f / scalar);

    return *this;
}

// Check whether dimensions and all elements are equal.
bool Matrix::operator==(const Matrix& otherMatrix) const {
    if(_rows != otherMatrix._rows || _cols != otherMatrix._cols)
        return false;
    else
        return _mat == otherMatrix._mat;
}

// Check whether any dimension or elements is unequal.
inline bool Matrix::operator!=(const Matrix& otherMatrix) const {
    return !operator==(otherMatrix);
}

// Returns true if the number of rows is equal to the number of columns.
inline bool Matrix::isSquare() const {
    return _rows == _cols;
}

// Returns the sum of the pincipal diagonal. The matrix can be non-square.
float Matrix::trace() const {
    std::uint16_t lim = std::min(_cols, _rows);
    float trace = 0.0f;

    for(std::uint16_t i = 0; i < lim; i++)
        trace += _mat[i][i];

    return trace;
}

// Returns the determinant of the matrix, which must be square.
float Matrix::det() const {
    if(!isSquare())
        return 0.0f;

    float det = 1.0f;
    Matrix tempMat = Matrix(*this);

    for(std::uint16_t i = 0; i < _rows; i++) {
        int pivot = i;
        for(std::uint16_t j = i + 1; j < _rows; j++) {
            if (abs(tempMat._mat[j][i]) > abs(tempMat._mat[pivot][i])) {
                pivot = j;
            }
        }

        if(pivot != i) {
            std::vector<float> temp = tempMat._mat[i];
            tempMat._mat[i] = tempMat._mat[pivot];
            tempMat._mat[pivot] = temp;

            det *= -1.0f;
        }

        if(tempMat._mat[i][i] == 0.0f)
            return 0.0f;

        det *= tempMat._mat[i][i];
        for(std::uint16_t j = i + 1; j < _rows; j++) {
            double factor = tempMat._mat[j][i] / tempMat._mat[i][i];

            for (int k = i + 1; k < _rows; k++) {
                tempMat._mat[j][k] -= factor * tempMat._mat[i][k];
            }
        }
    }

    return det;
}

// Create the transpose of the matrix.
Matrix Matrix::trans() const {
    std::vector<std::vector<float>> res = std::vector<std::vector<float>>(_cols, std::vector<float>(_rows));

    for(std::uint16_t i = 0; i < _rows; i++)
        for(std::uint16_t j = 0; j < _cols; j++)
            res[j][i] = _mat[i][j];

    return Matrix(res);
}

// Returns the inverse of the matrix, which must be square.
Matrix Matrix::inverse() const {
    if(!isSquare())
        return Matrix(0, 0);

    Matrix adjMat = Matrix(_rows, _cols, 1);
    Matrix tempMat = Matrix(*this);

    for(std::uint16_t i = 0; i < _rows; i++) {
        int pivot = i;
        for(std::uint16_t j = i + 1; j < _rows; j++) {
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
        for(std::uint16_t k = 0; k < _cols; k++) {
                if(k >= i) tempMat._mat[i][k] /= factor;
                adjMat._mat[i][k] /= factor;
        }

        for(std::uint16_t j = 0; j < _rows; j++) {
            if(j == i)
                continue;

            factor = tempMat._mat[j][i];

            for (std::uint16_t k = 0; k < _cols; k++) {
                if(k >= i) tempMat._mat[j][k] -= factor * tempMat._mat[i][k];
                adjMat._mat[j][k] -= factor * adjMat._mat[i][k];
            }
        }
    }

    return adjMat;
}

// Returns the adjoint (or adjugate) of the matrix. Shorthand for "A.inverse() * A.det()".
Matrix Matrix::adj() const {
    float determinant = det();

    return inverse() * determinant;
}

// Returns the number of rows.
inline std::uint16_t Matrix::rows() const {
    return _rows;
}

// Returns the number of columns.
inline std::uint16_t Matrix::cols() const {
    return _cols;
}

// Returns a modifiable reference to the value at (i, j).
float& Matrix::operator()(std::uint16_t i, std::uint16_t j) {
    return _mat[i % _rows][j % _cols];
}

// Returns the value at (i, j).
float Matrix::operator()(std::uint16_t i, std::uint16_t j) const {
    return _mat[i % _rows][j % _cols];
}

// Returns a modifiable reference to the ith row.
std::vector<float>& Matrix::operator()(std::uint16_t i) {
    return _mat[i % _rows];
}

// Returns the ith row.
std::vector<float> Matrix::operator()(std::uint16_t i) const {
    return _mat[i % _rows];
}

#ifdef _USE_MATRIX_PRINT
    // toString(). Enable with "#define _USE_MATRIX_SHORTHANDS"
    // "a b c\n"
    // "d e f\n"
    // "g h i\n"
    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for(const std::vector<float>& row: matrix._mat) {
            for(const float ele: row)
                os << ele << ' ';
            os << std::endl;
        }

        return os;
    }
#endif

#ifdef _USE_MATRIX_SHORTHANDS
    // Shorthand  to invert matrix. Enable with "#define _USE_MATRIX_SHORTHANDS"
    inline Matrix Matrix::operator~() {
        return inverse();
    }

    // Shorthand to create a copy. Enable with "#define _USE_MATRIX_SHORTHANDS"
    Matrix Matrix::operator+() const {
        return Matrix(*this);
    }
#endif

#ifdef _USE_MATRIX_PRINT
    #undef _USE_MATRIX_PRINT
#endif

#ifdef _USE_MATRIX_SHORTHANDS
    #undef _USE_MATRIX_SHORTHANDS
#endif

#endif