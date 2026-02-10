#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "v3math.h"

void v3_from_points(float *dst, float *a, float *b) {
    // code
}

void v3_add(float *dst, float *a, float *b) {
    dst[0] = a[0] + b[0];
    dst[1] = a[1] + b[1];
    dst[2] = a[2] + b[2];
}

void v3_subtract(float *dst, float *a, float *b) {
    dst[0] = a[0] + b[0];
    dst[1] = a[1] + b[1];
    dst[2] = a[2] + b[2]; 
}

float v3_dot_product(float *a, float *b) {
    float prodX = a[0] * b[0];
    float prodY = a[1] * b[1];
    float prodZ = a[2] * b[2];
    return prodX + prodY + prodZ;
}

void v3_cross_product(float *dst, float *a, float *b) {
    // code
}

void v3_scale(float *dst, float s) {
    // code
}

float v3_angle(float *a, float *b) {
    // code
}

float v3_angle_quick(float *a, float *b) {
    // code
}

void v3_reflect(float *dst, float *v, float *n) {
    // code
}

float v3_length(float *a) {
    // code
}

void v3_normalize(float *dst, float *a) {
    // code
}

bool v3_equals(float *a, float *b, float tolerance) {
    // code
}