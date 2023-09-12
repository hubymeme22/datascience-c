#include <stdio.h>
#include <math.h>

// calculates the eucledian distance between point a and b
// condition: a and b must have equal size
float eucledian_distance(float* a, float* b, int size) {
    float sumsquared = 0;
    for (int i = 0; i < size; i++)
        sumsquared += (a[i] - b[i]) * (a[i] - b[i]);

    return sqrt(sumsquared);
}