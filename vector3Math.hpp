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
    Vector3(): vec(3, 0) {}
    // Construct with individual values
    Vector3(const float x, const float y, const float z = 0) {
        vec.push_back(x);
        vec.push_back(y);
        vec.push_back(z);
    }
    // Construct with array
    Vector3(const float arr[3]): vec(arr, arr + 3) {}
    // Scalar vector
    Vector3(const float scalar): vec(3, scalar) {}

    // Operator overloading
    // Loops aren't used to avoid the overhead of looping statements
    // (iteration variable, incrementation, condition checking)
    // The disadvantage is slightly bigger (compiled & uncompiled) code size
    Vector3 operator+(const Vector3& obj) const {
        float res[3] = {};
        
        res[0] = vec.at(0) + obj.vec.at(0);
        res[1] = vec.at(1) + obj.vec.at(1);
        res[2] = vec.at(2) + obj.vec.at(2);

        return Vector3(res);
    }

    Vector3 operator+() const {
        return Vector3(*this);
    }

    Vector3 operator-(const Vector3& obj) const {
        float res[3] = {};
        
        res[0] = vec.at(0) - obj.vec.at(0);
        res[1] = vec.at(1) - obj.vec.at(1);
        res[2] = vec.at(2) - obj.vec.at(2);

        return Vector3(res);
    }

    Vector3 operator-() const {
        float res[3] = {};

        res[0] = -vec.at(0);
        res[1] = -vec.at(1);
        res[2] = -vec.at(2);

        return Vector3(res);
    }

    Vector3 operator*(const Vector3& obj) const {
        float res[3] = {};
        
        res[0] = vec.at(0) * obj.vec.at(0);
        res[1] = vec.at(1) * obj.vec.at(1);
        res[2] = vec.at(2) * obj.vec.at(2);

        return Vector3(res);
    }

    Vector3 operator/(const Vector3& obj) const {
        float res[3] = {};
        
        if(obj.vec.at(0) != 0)
            res[0] = vec.at(0) / obj.vec.at(0);
        if(obj.vec.at(1) != 0)
            res[1] = vec.at(1) / obj.vec.at(1);
        if(obj.vec.at(2) != 0)
            res[2] = vec.at(2) / obj.vec.at(2);

        return Vector3(res);
    }

    Vector3& operator=(const Vector3& obj) {
        vec = obj.vec;

        return *this;
    }

    Vector3& operator=(const float obj[3]) {
        vec.assign(obj, obj + 3);
        
        return *this;
    }

    void operator+=(const Vector3& obj) {
        
        vec.at(0) += obj.vec.at(0);
        vec.at(1) += obj.vec.at(1);
        vec.at(2) += obj.vec.at(2);
    }

    void operator-=(const Vector3& obj) {
        vec.at(0) -= obj.vec.at(0);
        vec.at(1) -= obj.vec.at(1);
        vec.at(2) -= obj.vec.at(2);
    }

    void operator*=(const Vector3& obj) {
        vec.at(0) *= obj.vec.at(0);
        vec.at(1) *= obj.vec.at(1);
        vec.at(2) *= obj.vec.at(2);
    }

    void operator/=(const Vector3& obj) {
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
    }

    bool operator==(const Vector3& obj) const {
        return vec == obj.vec;
    }

    bool operator==(const float obj[3]) const {
        return (
            vec.at(0) == obj[0] &&
            vec.at(1) == obj[1] &&
            vec.at(2) == obj[2]
        );
    }

    float operator^(const Vector3& obj) const {
        return vec.at(0) * obj.vec.at(0) + vec.at(1) * obj.vec.at(1) + vec.at(2) * obj.vec.at(2);
    }


    // Special functions
    // These are unique to this class
    Vector3 normal() {
        float res[3] = {};
        float magnitude = getMagnitude();

        if(magnitude != 0.0f) {
            res[0] = vec.at(0) / magnitude;
            res[1] = vec.at(1) / magnitude;
            res[2] = vec.at(2) / magnitude;
        }

        return Vector3(res);
    }

    void normalise() {
        float magnitude = getMagnitude();

        if(magnitude != 0.0f) {
            vec.at(0) /= magnitude;
            vec.at(1) /= magnitude;
            vec.at(2) /= magnitude;
        }
    }

    inline float dot() const {
        return vec.at(0) * vec.at(0) + vec.at(1) * vec.at(1) + vec.at(2) * vec.at(2);
    }

    inline float dot(const Vector3& obj) const {
        return vec.at(0) * obj.vec.at(0) + vec.at(1) * obj.vec.at(1) + vec.at(2) * obj.vec.at(2);
    }

    inline float getMagnitude() const {
        return sqrt(dot());
    }


    // Getter & setter
    float& operator()(int i) {
        return vec.at(i % 3);
    }

    float operator()(int i) const {
        return vec.at(i % 3);
    }


    // toString()
    friend ostream& operator<< (ostream& os, const Vector3& obj) {
        for(const float ele: obj.vec)
            os << ele << ' ';

        return os;
    }
};

#endif