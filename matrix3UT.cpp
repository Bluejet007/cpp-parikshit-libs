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
    },
    test4[3][3] = {
        {4.0f, -1.0f, 0.0f},
        {1.0f, 3.0f, -2.0f},
        {7.0f, 5.0f, 8.0f}
    };

    float sum7[3][3] = {
        {13.0f, 5.0f, 3.0f},
        {2.0f, 5.0f, 1.0f},
        {12.0f, 5.0f, 13.0f}
    };

    float mul6[3][3] = {
        {-8.0f, 2.0f, 0.0f},
        {-2.0f, -6.0f, 4.0f},
        {-14.0f, -10.0f, -16.0f}
    },
    mul34[3][3] = {
        {63.0f, 24.0f, 12.0f},
        {27.0f, 20.0f, 20.0f},
        {55.0f, 20.0f, 40.0f}
    },
    mul43[3][3] = {
        {35.0f, 22.0f, 9.0f},
        {2.0f, 12.0f, 2.0f},
        {108.0f, 52.0f, 76.0f}
    };

    // Constructors
    cout << endl << "CONSTRUCTORS" << endl; {
        assert("Default", Matrix3(), test1);
        assert("Scalar", Matrix3(-2), test2);
        assert("Array", Matrix3(test3), test3);
    }

    // Unary & Subscript Operators
    cout << endl << "UNARY & SUBSCRIPT OPERATORS" << endl; {
        float temp[3][3] = {
            {2.0f, 0.0f, 0.0f},
            {0.0f, 2.0f, 0.0f},
            {0.0f, 0.0f, 2.0f}
        };

        assert("Plus", +Matrix3(test3), test3);
        assert("Minus", -Matrix3(test2), temp);
    }

    // Assignment Operators
    cout << endl << "ASSIGNMENT OPERATORS" << endl; {
        Matrix3 temp;

        temp = Matrix3(test4);
        assert("Assignment", temp, test4);
        temp += Matrix3(test3);
        assert("Add-assign", temp, sum7);
        temp -= Matrix3(test3);
        assert("Sub-assign", temp, test4);
        temp *= Matrix3(test2);
        assert("Mul-assign", temp, mul6);
        temp /= -2.0f;
        assert("Div-assign", temp, test4);
        temp *= -2.0f;
        assert("Mul-assign Scalar", temp, mul6);
    }

    // Binary Operators
    cout << endl << "BINARY OPERATORS" << endl; {
        Matrix3 temp1 = Matrix3(test3), temp2 = Matrix3(test4);
        Matrix3 res;

        res = temp1 + temp2;
        assert("Addition", res, sum7);
        res = res - temp2;
        assert("Subtraction", res, test3);
        res = temp1 * temp2;
        assert("Multiplication 1", res, mul34);
        res = temp2 * temp1;
        assert("Multiplication 2", res, mul43);
        res = -2.0f * temp2;
        assert("Scalar multiplication 1", res, mul6);
        res = temp2 * -2.0f;
        assert("Scalar multiplication 2", res, mul6);
        res = res / -2.0f;
        assert("Scalar division", res, test4);
    }

    // Trace & Determinant
    cout << endl << "TRACE & DETERMINANT" << endl; {

    }

    // Transpose, Adjoint & Inverse
    cout << endl << "TRANSPOSE, ADJOINT & INVERSE" << endl; {

    }

    return 0;
}