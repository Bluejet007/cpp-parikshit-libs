#include "quest.hpp"

int main() {
    Vector3 B1 = Vector3({372.221, 782.933, 11.282});
    Vector3 B2 = Vector3({30.722, 732.773, 12.43});
    Vector3 R1 = Vector3({21.772, -233.71, 92.902});
    Vector3 R2 = Vector3({73.662, 93.102, 44.372});

    quest(B1, B2, R1, R2, 0.5, 0.5);

    return 0;
}