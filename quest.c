#include <stdlib.h>
#include <stdio.h>
#include "vector3Math.h"

void main() {
    Matrix3 mat = {{{2, 4, 4}, {2, 1, 3}, {7, 9, 1}}};

    printf("Det = %f\n", getMatDet(&mat));
}