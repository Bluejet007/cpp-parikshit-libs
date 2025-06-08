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
    Vector4(const float x, const float y, const float z = 0.0f, const float w = 0.0f): vec() {
        vec.push_back(x);
        vec.push_back(y);
        vec.push_back(z);
        vec.push_back(w);
    }
    // Construct with array
    Vector4(const float arr[4]): vec(arr, arr + 4) {}
    // Scalar vector
    Vector4(const float scalar): vec(4, scalar) {}

    // Operator overloading
    // Loops aren't used to avoid the overhead of looping statements
    // (iteration variable, incrementation, condition checking)
    // The disadvantage is slightly bigger (compiled & uncompiled) code size
    Vector4 operator+(const Vector4& obj) const {
        float res[4] = {};
        
        res[0] = vec.at(0) + obj.vec.at(0);
        res[1] = vec.at(1) + obj.vec.at(1);
        res[2] = vec.at(2) + obj.vec.at(2);
        res[3] = vec.at(3) + obj.vec.at(3);

        return Vector4(res);
    }

    Vector4 operator+() const {
        return Vector4(*this);
    }

    Vector4 operator-(const Vector4& obj) const {
        float res[4] = {};
        
        res[0] = vec.at(0) - obj.vec.at(0);
        res[1] = vec.at(1) - obj.vec.at(1);
        res[2] = vec.at(2) - obj.vec.at(2);
        res[3] = vec.at(3) - obj.vec.at(3);

        return Vector4(res);
    }

    Vector4 operator-() const {
        float res[4] = {};

        res[0] = -vec.at(0);
        res[1] = -vec.at(1);
        res[2] = -vec.at(2);
        res[3] = -vec.at(3);

        return Vector4(res);
    }

    Vector4 operator*(const Vector4& obj) const {
        float res[4] = {};
        
        res[0] = vec.at(0) * obj.vec.at(0);
        res[1] = vec.at(1) * obj.vec.at(1);
        res[2] = vec.at(2) * obj.vec.at(2);
        res[3] = vec.at(3) * obj.vec.at(3);

        return Vector4(res);
    }

    Vector4 operator/(const Vector4& obj) const {
        float res[4] = {};
        
        if(obj.vec.at(0) != 0)
            res[0] = vec.at(0) / obj.vec.at(0);
        if(obj.vec.at(1) != 0)
            res[1] = vec.at(1) / obj.vec.at(1);
        if(obj.vec.at(2) != 0)
            res[2] = vec.at(2) / obj.vec.at(2);
        if(obj.vec.at(3) != 0)
            res[3] = vec.at(3) / obj.vec.at(3);

        return Vector4(res);
    }

    Vector4& operator=(const Vector4& obj) {
        vec = obj.vec;

        return *this;
    }

    Vector4 operator+=(const Vector4& obj) {
        
        vec.at(0) += obj.vec.at(0);
        vec.at(1) += obj.vec.at(1);
        vec.at(2) += obj.vec.at(2);
        vec.at(3) += obj.vec.at(3);

        return *this;
    }

    Vector4 operator-=(const Vector4& obj) {
        vec.at(0) -= obj.vec.at(0);
        vec.at(1) -= obj.vec.at(1);
        vec.at(2) -= obj.vec.at(2);
        vec.at(3) -= obj.vec.at(3);

        return *this;
    }

    Vector4 operator*=(const Vector4& obj) {
        vec.at(0) *= obj.vec.at(0);
        vec.at(1) *= obj.vec.at(1);
        vec.at(2) *= obj.vec.at(2);
        vec.at(3) *= obj.vec.at(3);

        return *this;
    }

    Vector4 operator/=(const Vector4& obj) {
        if(obj.vec.at(0) != 0)
            vec.at(0) /= obj.vec.at(0);
        else
            vec.at(0) = 0;

        if(obj.vec.at(1) != 0)
            vec.at(1) /= obj.vec.at(1);
        else
            vec.at(1) = 0;

        if(obj.vec.at(2) != 0)
            vec.at(2) /= obj.vec.at(2);
        else
            vec.at(2) = 0;

        if(obj.vec.at(3) != 0)
            vec.at(3) /= obj.vec.at(3);
        else
            vec.at(3) = 0;

        return *this;
    }

    bool operator==(const Vector4& obj) const {
        return vec == obj.vec;
    }

    bool operator==(const float obj[4]) const {
        return (
            vec.at(0) == obj[0] &&
            vec.at(1) == obj[1] &&
            vec.at(2) == obj[2] &&
            vec.at(3) == obj[3]
        );
    }

    inline float operator^(const Vector4& obj) const {
        return dot(obj);
    }


    // Special functions
    // These are unique to this class
    Vector4 normal() {
        float res[4] = {};
        float magnitude = getMagnitude();

        if(magnitude != 0.0f) {
            res[0] = vec.at(0) / magnitude;
            res[1] = vec.at(1) / magnitude;
            res[2] = vec.at(2) / magnitude;
            res[3] = vec.at(3) / magnitude;
        }

        return Vector4(res);
    }

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
    float& operator()(int i) {
        return vec.at(i % 4);
    }

    float operator()(int i) const {
        return vec.at(i % 4);
    }


    // toString()
    friend ostream& operator<< (ostream& os, const Vector4& obj) {
        for(const float ele: obj.vec)
            os << ele << ' ';

        return os;
    }
};

#endif