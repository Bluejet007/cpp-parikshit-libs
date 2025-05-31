#include <math.h>
#include <stdlib.h>

typedef struct vec_3 {
    float vec[3];
} Vector3;

// Vector operations
Vector3* normaliseVec(Vector3 *inpVec);

// Vector properties
float getMagnitude(Vector3 *inpVec);

Vector3* normaliseVec(Vector3 *inpVec) {
    Vector3 *outVec = (Vector3*) malloc(sizeof(Vector3));
    float mag = getMagnitude(inpVec);

    for(char i = 0; i < 3; i++)
        outVec -> vec[i] = inpVec -> vec[i] / mag;

    return outVec;
}

float getMagnitude(Vector3 *inpVec) {
    float sqMag = 0.0f;

    for(char i = 0; i < 3; i++)
        sqMag += inpVec -> vec[i];

    return powf(sqMag, 0.5f);
}