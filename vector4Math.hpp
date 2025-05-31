#ifndef VECTOR_4_MATH_H
#define VECTOR_4_MATH_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Vector4 {
    private:
    vector<float> vec;
    
    public:
    // Default constructor
    Vector4(): vec(4, 0.0f) {}
    // Construct with individual values
    Vector4(const float x, const float y, const float z, const float w): vec() {
        vec.push_back(x);
        vec.push_back(y);
        vec.push_back(z);
        vec.push_back(w);
    }
    // Construct with array
    Vector4(const float arr[4]): vec(arr, arr + 4) {}
    // Contruct copy
    Vector4(const Vector4& vect): vec(vect.vec) {}
    // Scalar vector
    Vector4(const float scalar): vec(4, scalar) {}

    // Operator overloading
    // Loops aren't used to avoid the overhead of looping statements
    // (iteration variable, incrementation, condition checking)
    // The disadvantage is slightly bigger (compiled & uncompiled) code size
    Vector4 operator+(const Vector4& obj) {
        float res[4] = {};
        
        res[0] = vec.at(0) + obj.vec.at(0);
        res[1] = vec.at(1) + obj.vec.at(1);
        res[2] = vec.at(2) + obj.vec.at(2);
        res[3] = vec.at(3) + obj.vec.at(3);

        return Vector4(res);
    }

    Vector4 operator-(const Vector4& obj) {
        float res[4] = {};
        
        res[0] = vec.at(0) - obj.vec.at(0);
        res[1] = vec.at(1) - obj.vec.at(1);
        res[2] = vec.at(2) - obj.vec.at(2);
        res[3] = vec.at(3) - obj.vec.at(3);

        return Vector4(res);
    }

    Vector4 operator*(const Vector4& obj) {
        float res[4] = {};
        
        res[0] = vec.at(0) * obj.vec.at(0);
        res[1] = vec.at(1) * obj.vec.at(1);
        res[2] = vec.at(2) * obj.vec.at(2);
        res[3] = vec.at(3) * obj.vec.at(3);

        return Vector4(res);
    }

    Vector4 operator/(const Vector4& obj) {
        float res[4] = {};
        
        res[0] = vec.at(0) / obj.vec.at(0);
        res[1] = vec.at(1) / obj.vec.at(1);
        res[2] = vec.at(2) / obj.vec.at(2);
        res[3] = vec.at(3) / obj.vec.at(3);

        return Vector4(res);
    }

    void operator+=(const Vector4& obj) {
        
        vec.at(0) += obj.vec.at(0);
        vec.at(1) += obj.vec.at(1);
        vec.at(2) += obj.vec.at(2);
        vec.at(3) += obj.vec.at(3);
    }

    void operator-=(const Vector4& obj) {
        vec.at(0) -= obj.vec.at(0);
        vec.at(1) -= obj.vec.at(1);
        vec.at(2) -= obj.vec.at(2);
        vec.at(3) -= obj.vec.at(3);
    }

    void operator*=(const Vector4& obj) {
        vec.at(0) *= obj.vec.at(0);
        vec.at(1) *= obj.vec.at(1);
        vec.at(2) *= obj.vec.at(2);
        vec.at(3) *= obj.vec.at(3);
    }

    void operator/=(const Vector4& obj) {
        vec.at(0) /= obj.vec.at(0);
        vec.at(1) /= obj.vec.at(1);
        vec.at(2) /= obj.vec.at(2);
        vec.at(3) /= obj.vec.at(3);
    }


    // Special functions
    // These are unique to this class
    void normalise() {
        float magnitude = getMagnitude();

        if(magnitude != 0.0f) {
            vec.at(0) /= magnitude;
            vec.at(1) /= magnitude;
            vec.at(2) /= magnitude;
            vec.at(3) /= magnitude;
        }
    }

    inline float dot() const {
        return vec.at(0) * vec.at(0) + vec.at(1) * vec.at(1) + vec.at(2) * vec.at(2) + vec.at(3) * vec.at(3);
    }

    inline float dot(const Vector4& obj) const {
        return vec.at(0) * obj.vec.at(0) + vec.at(1) * obj.vec.at(1) + vec.at(2) * obj.vec.at(2) + vec.at(3) * obj.vec.at(3);
    }

    inline float getMagnitude() const {
        return sqrt(dot());
    }


    // Getters & setters
    void setEle(char i, float val) {
        if(0 <= i && i <= 3)
            vec.at(i) = val;
        else
            cout << "Invalid index\ni: " << i;
    }

    float getEle(char i) const {
        if(0 <= i && i <= 3)
            return vec.at(i);
        else {
            cout << "Invalid index\ni: " << i;
            return 0.0f;
        }
    }


    // toString()
    friend ostream& operator<< (ostream& os, const Vector4& obj) {
        for(const float ele: obj.vec)
            os << ele << ' ';

        return os;
    }
};

#endif