#define _USE_MATRIX_PRINT
#include "matrixMath.hpp"

using namespace std;


int main() {
    Matrix squ = Matrix({{1, 2, 3}, {8, 7, 6}, {4, 5, 9}});

    squ *= 3.0f;

    cout << endl << squ.adj();

    return 0;
}