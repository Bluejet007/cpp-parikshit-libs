#ifndef VECTOR_3_MATH_H
#define VECTOR_3_MATH_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Vector3 {
    private:
    vector<float> vec;
    
    public:
    // Default constructor
    Vector3(): vec(3, 0.0f) {}
    // Construct with individual values
    Vector3(const float x, const float y, const float z = 0.0f) {
        vec.push_back(x);
        vec.push_back(y);
        vec.push_back(z);
    }
    // Construct with array
    Vector3(const float arr[3]): vec(arr, arr + 3) {}
    // Scalar vector
    Vector3(const float scalar): vec(3, scalar) {}

    // Deconstruct vector into normal array
    void toArray(float arr[3]) {
        copy(vec.begin(), vec.end(), arr);
    }

    // Operator overloading
    // Loops aren't used to avoid the overhead of looping statements
    // (iteration variable, incrementation, condition checking)
    // The disadvantage is slightly bigger (compiled & uncompiled) code size
    Vector3 operator+(const Vector3& obj) const {
        float res[3] = {};
        
        res[0] = vec[0] + obj.vec[0];
        res[1] = vec[1] + obj.vec[1];
        res[2] = vec[2] + obj.vec[2];

        return Vector3(res);
    }

    // Unary plus forces pass-by-ref to be pass-by-value
    Vector3 operator+() const {
        return Vector3(*this);
    }

    Vector3 operator-(const Vector3& obj) const {
        float res[3] = {};
        
        res[0] = vec[0] - obj.vec[0];
        res[1] = vec[1] - obj.vec[1];
        res[2] = vec[2] - obj.vec[2];

        return Vector3(res);
    }

    Vector3 operator-() const {
        float res[3] = {};

        res[0] = -vec[0];
        res[1] = -vec[1];
        res[2] = -vec[2];

        return Vector3(res);
    }

    Vector3 operator*(const Vector3& obj) const {
        float res[3] = {};
        
        res[0] = vec[0] * obj.vec[0];
        res[1] = vec[1] * obj.vec[1];
        res[2] = vec[2] * obj.vec[2];

        return Vector3(res);
    }

    Vector3 operator/(const Vector3& obj) const {
        float res[3] = {INFINITY, INFINITY, INFINITY};
        
        if(obj.vec[0] != 0)
            res[0] = vec[0] / obj.vec[0];
        if(obj.vec[1] != 0)
            res[1] = vec[1] / obj.vec[1];
        if(obj.vec[2] != 0)
            res[2] = vec[2] / obj.vec[2];

        return Vector3(res);
    }

    Vector3& operator=(const Vector3& obj) {
        vec = obj.vec;

        return *this;
    }

    Vector3& operator+=(const Vector3& obj) {
        
        vec[0] += obj.vec[0];
        vec[1] += obj.vec[1];
        vec[2] += obj.vec[2];

        return *this;
    }

    Vector3& operator-=(const Vector3& obj) {
        vec[0] -= obj.vec[0];
        vec[1] -= obj.vec[1];
        vec[2] -= obj.vec[2];

        return *this;
    }

    Vector3& operator*=(const Vector3& obj) {
        vec[0] *= obj.vec[0];
        vec[1] *= obj.vec[1];
        vec[2] *= obj.vec[2];

        return *this;
    }

    Vector3& operator/=(const Vector3& obj) {
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

        return *this;
    }
    
    bool operator==(const Vector3& obj) const {
        return vec == obj.vec;
    }
    
    bool operator==(const float obj[3]) const {
        return (
            vec[0] == obj[0] &&
            vec[1] == obj[1] &&
            vec[2] == obj[2]
        );
    }
    
    inline bool operator!=(const Vector3& obj) const {
        return !operator==(obj);
    }
    
    inline bool operator!=(const float obj[3]) const {
        return !operator==(obj);
    }

    // Dot product shorthand
    inline float operator^(const Vector3& obj) const {
        return dot(obj);
    }


    // Special functions
    // These are unique to this class
    Vector3 normal() const {
        float res[3] = {};
        float magnitude = getMagnitude();

        if(magnitude != 0.0f) {
            res[0] = vec[0] / magnitude;
            res[1] = vec[1] / magnitude;
            res[2] = vec[2] / magnitude;
        }

        return Vector3(res);
    }

    void normalise() {
        float magnitude = getMagnitude();

        if(magnitude != 0.0f) {
            vec[0] /= magnitude;
            vec[1] /= magnitude;
            vec[2] /= magnitude;
        }
    }

    inline float dot(const Vector3& obj) const {
        return vec[0] * obj.vec[0] + vec[1] * obj.vec[1] + vec[2] * obj.vec[2];
    }

    inline float dot() const {
        return dot(*this);
    }

    inline float getMagnitude() const {
        return sqrt(dot());
    }


    // Getter & setter
    float& operator[](int i) {
        return vec[i % 3];
    }

    float operator[](int i) const {
        return vec[i % 3];
    }


    // toString()
    // "x y z "
    friend ostream& operator<< (ostream& os, const Vector3& obj) {
        for(const float ele: obj.vec)
            os << ele << ' ';

        return os;
    }

    
};

#endif