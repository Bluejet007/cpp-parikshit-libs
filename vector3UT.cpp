#include "vector3Math.hpp"

void assert(const string name, const Vector3& sub, const Vector3& aim) {
    cout << name << " - ";

    if(sub == aim)
        cout << "SUCCESSFUL" << endl;
    else
        clog << "FAILED" << endl << '\t' << "Expected: " << aim << endl << '\t' << "Result: " << sub << endl << endl;
}

void assert(const string name, const float sub, const float aim) {
    cout << name << " - ";

    if(sub == aim)
        cout << "SUCCESSFUL" << endl;
    else
        clog << "FAILED" << endl << '\t' << "Expected: " << aim << endl << '\t' << "Result: " << sub << endl << endl;
}

int main() {
    // Constructors
    cout << endl<< "CONSTRUCTORS" << endl; {
    
        assert("Default", Vector3(), {0, 0, 0});
        assert("Scalar", Vector3(-2), {-2, -2, -2});
        assert("Individual values 1", Vector3(1, 2), {1, 2, 0});
        assert("Individual values 2", Vector3(1, 2, 3), {1, 2, 3});
        assert("Array", Vector3({9, 6, 3}), {9, 6, 3});
    }


    // Unary & Subscript Operators
    cout << endl << "UNARY & SUBSCRIPT OPERATORS" << endl; {
        Vector3 testA = Vector3(0, 21, -5);
        const Vector3 testB = Vector3(1, 2, 3);

        assert("Plus", +testA, {0, 21, -5});
        assert("Minus", -testA, {0, -21, 5});
        assert("Subscript 1", {testA(0), testA(1), testA(2)}, {0, 21, -5});
        testA(2) = testB(1);
        assert("Subscript 2", {testA(0), testA(1), testA(2)}, {0, 21, 2});
    }

    // Assignment Operators
    cout << endl << "ASSIGNMENT OPERATORS" << endl; {
        Vector3 testA = Vector3(-3, 1, 1), testB = Vector3(0, -0.5, 2);
        Vector3 res;

        res = testA;
        assert("Assignment", res, {-3, 1, 1});
        res += testB;
        assert("Add-assign", res, {-3, 0.5, 3});
        res -= testB;
        assert("Sub-assign", res, {-3, 1, 1});
        res *= testB;
        assert("Mul-assign", res, {0, -0.5, 2});
        res /= testB;
        assert("Div-assign", res, {0, 1, 1});
    }

    // Binary Operators
    cout << endl << "BINARY OPERATORS" << endl; {
        Vector3 testA = Vector3(-10, 2, 0), testB = Vector3(3, 0, -4);
        Vector3 res;

        res = testA + testB;
        assert("Addition", res, {-7, 2, -4});
        res = testA - testB;
        assert("Subtraction", res, {-13, 2, 4});
        res = testA * testB;
        assert("Multiplication", res, {-30, 0, 0});
        res = testA / testB;
        assert("Division", res, {-10.0f/3.0f, 0, 0});
    }

    // Dot Product
    cout << endl << "DOT PRODUCT" << endl; {
        Vector3 testA = Vector3(4, 1, -3), testB = Vector3(2, 0, 1);
        float res;

        res = testB.dot();
        assert("Dot 1", res, 5.0f);
        res = testA.dot(testB);
        assert("Dot 2", res, testB.dot(testA));
        res = testB ^ testA;
        assert("Dot 3", res, 5.0f);
    }

    // Normalise & Magnitude
    cout << endl << "NORMALISE & MAGNITUDE" << endl; {
        Vector3 test = Vector3();

        test = {2.0f, 0.0f, 0.0f};
        assert("Norm", test.normal(), {1.0f, 0, 0});
        assert("Mag", test.getMagnitude(), 2.0f);
        test = {2.0f, 0.0f, 2.0f};
        assert("Norm-Mag 1", test.normal(), {2.0f / test.getMagnitude(), 0, 2.0f / test.getMagnitude()});
        test = {2.0f, 3.0f, 5.0f};
        assert("Norm-Mag 2", test.normal(), {2.0f / test.getMagnitude(), 3.0f / test.getMagnitude(), 5.0f / test.getMagnitude()});
    }

    return 0;
}