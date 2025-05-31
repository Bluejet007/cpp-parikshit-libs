#include "matrix3Math.hpp"

void assert(const string name, const Matrix3& sub, const Matrix3& aim) {
    cout << name << " - ";

    if(sub == aim)
        cout << "SUCCESSFUL" << endl;
    else
        clog << "FAILED" << endl << '\t' << "Expected:" << endl << aim << endl << '\t' << "Result:" << endl << sub << endl << endl;
}

void assert(const string name, const float sub, const float aim) {
    cout << name << " - ";

    if(sub == aim)
        cout << "SUCCESSFUL" << endl;
    else
        clog << "FAILED" << endl << '\t' << "Expected:" << endl << aim << endl << '\t' << "Result:" << endl << sub << endl << endl;
}

int main() {
    float test1[3][3] = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}
    },
    test2[3][3] = {
        {-2.0f, 0.0f, 0.0f},
        {0.0f, -2.0f, 0.0f},
        {0.0f, 0.0f, -2.0f}
    },
    test3[3][3] = {
        {9.0f, 6.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {5.0f, 0.0f, 5.0f}
    };

    // Constructors
    cout << endl << "CONSTRUCTORS" << endl; {
        assert("Default", Matrix3(), test1);
        assert("Scalar", Matrix3(-2), test2);
        assert("Array", Matrix3(test3), test3);
    }

    // Unary & Subscript Operators
    cout << endl << "UNARY & SUBSCRIPT OPERATORS" << endl; {
        float T[3][3] = {
            {2.0f, 0.0f, 0.0f},
            {0.0f, 2.0f, 0.0f},
            {0.0f, 0.0f, 2.0f}
        };

        assert("Plus", +Matrix3(test3), test3);
        assert("Minus", -Matrix3(test2), T);
    }

    // Assignment Operators
    cout << endl << "ASSIGNMENT OPERATORS" << endl; {

    }

    // Binary Operators
    cout << endl << "BINARY OPERATORS" << endl; {

    }

    // Trace & Determinant
    cout << endl << "TRACE & DETERMINANT" << endl; {

    }

    // Transpose, Adjoint & Inverse
    cout << endl << "TRANSPOSE, ADJOINT & INVERSE" << endl; {

    }

    return 0;
}