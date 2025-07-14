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

    // Deconstruct vector into normal array
    void toArray(float arr[4]) {
        copy(vec.begin(), vec.end(), arr);
    }

    // Operator overloading
    // Loops aren't used to avoid the overhead of looping statements
    // (iteration variable, incrementation, condition checking)
    // The disadvantage is slightly bigger (compiled & uncompiled) code size
    Vector4 operator+(const Vector4& obj) const {
        float res[4] = {};
        
        res[0] = vec[0] + obj.vec[0];
        res[1] = vec[1] + obj.vec[1];
        res[2] = vec[2] + obj.vec[2];
        res[3] = vec[3] + obj.vec[3];

        return Vector4(res);
    }

    Vector4 operator+() const {
        return Vector4(*this);
    }

    Vector4 operator-(const Vector4& obj) const {
        float res[4] = {};
        
        res[0] = vec[0] - obj.vec[0];
        res[1] = vec[1] - obj.vec[1];
        res[2] = vec[2] - obj.vec[2];
        res[3] = vec[3] - obj.vec[3];

        return Vector4(res);
    }

    Vector4 operator-() const {
        float res[4] = {};

        res[0] = -vec[0];
        res[1] = -vec[1];
        res[2] = -vec[2];
        res[3] = -vec[3];

        return Vector4(res);
    }

    Vector4 operator*(const Vector4& obj) const {
        float res[4] = {};
        
        res[0] = vec[0] * obj.vec[0];
        res[1] = vec[1] * obj.vec[1];
        res[2] = vec[2] * obj.vec[2];
        res[3] = vec[3] * obj.vec[3];

        return Vector4(res);
    }

    Vector4 operator/(const Vector4& obj) const {
        float res[4] = {INFINITY, INFINITY, INFINITY, INFINITY};
        
        if(obj.vec[0] != 0)
            res[0] = vec[0] / obj.vec[0];
        if(obj.vec[1] != 0)
            res[1] = vec[1] / obj.vec[1];
        if(obj.vec[2] != 0)
            res[2] = vec[2] / obj.vec[2];
        if(obj.vec[3] != 0)
            res[3] = vec[3] / obj.vec[3];

        return Vector4(res);
    }

    Vector4& operator=(const Vector4& obj) {
        vec = obj.vec;

        return *this;
    }

    Vector4 operator+=(const Vector4& obj) {
        
        vec[0] += obj.vec[0];
        vec[1] += obj.vec[1];
        vec[2] += obj.vec[2];
        vec[3] += obj.vec[3];

        return *this;
    }

    Vector4 operator-=(const Vector4& obj) {
        vec[0] -= obj.vec[0];
        vec[1] -= obj.vec[1];
        vec[2] -= obj.vec[2];
        vec[3] -= obj.vec[3];

        return *this;
    }

    Vector4 operator*=(const Vector4& obj) {
        vec[0] *= obj.vec[0];
        vec[1] *= obj.vec[1];
        vec[2] *= obj.vec[2];
        vec[3] *= obj.vec[3];

        return *this;
    }

    Vector4 operator/=(const Vector4& obj) {
        if(obj.vec[0] != 0)
            vec[0] /= obj.vec[0];
        else
            vec[0] = INFINITY;

        if(obj.vec[1] != 0)
            vec[1] /= obj.vec[1];
        else
            vec[1] = INFINITY;

        if(obj.vec[2] != 0)
            vec[2] /= obj.vec[2];
        else
            vec[2] = INFINITY;

        if(obj.vec[3] != 0)
            vec[3] /= obj.vec[3];
        else
            vec[3] = INFINITY;

        return *this;
    }
    
    bool operator==(const Vector4& obj) const {
        return vec == obj.vec;
    }
    
    bool operator==(const float obj[4]) const {
        return (
            vec[0] == obj[0] &&
            vec[1] == obj[1] &&
            vec[2] == obj[2] &&
            vec[3] == obj[3]
        );
    }
    
    bool operator!=(const Vector4& obj) const {
        return !operator==(obj);
    }
    
    bool operator!=(const float obj[4]) const {
        return !operator==(obj);
    }

    // Dot product shorthand
    inline float operator^(const Vector4& obj) const {
        return dot(obj);
    }


    // Special functions
    // These are unique to this class
    Vector4 normal() const {
        float res[4] = {};
        float magnitude = getMagnitude();

        if(magnitude != 0.0f) {
            res[0] = vec[0] / magnitude;
            res[1] = vec[1] / magnitude;
            res[2] = vec[2] / magnitude;
            res[3] = vec[3] / magnitude;
        }

        return Vector4(res);
    }

    void normalise() {
        float magnitude = getMagnitude();

        if(magnitude != 0.0f) {
            vec[0] /= magnitude;
            vec[1] /= magnitude;
            vec[2] /= magnitude;
            vec[3] /= magnitude;
        }
    }

    inline float dot(const Vector4& obj) const {
        return vec[0] * obj.vec[0] + vec[1] * obj.vec[1] + vec[2] * obj.vec[2] + vec[3] * obj.vec[3];
    }

    inline float dot() const {
        return dot(*this);
    }

    inline float getMagnitude() const {
        return sqrt(dot());
    }


    // Getters & setters
    float& operator[](int i) {
        return vec[i % 4];
    }

    float operator[](int i) const {
        return vec[i % 4];
    }


    // toString()
    // "x y z w "
    friend ostream& operator<< (ostream& os, const Vector4& obj) {
        for(const float ele: obj.vec)
            os << ele << ' ';

        return os;
    }
};

#endif