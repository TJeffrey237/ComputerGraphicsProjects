#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "v3math.h"

void v3_from_points(float *dst, float *a, float *b) {
    dst[0] = b[0] - a[0];
    dst[1] = b[1] - a[1];
    dst[2] = b[2] - a[2];
}

void v3_add(float *dst, float *a, float *b) {
    dst[0] = a[0] + b[0];
    dst[1] = a[1] + b[1];
    dst[2] = a[2] + b[2];
}

void v3_subtract(float *dst, float *a, float *b) {
    dst[0] = a[0] - b[0];
    dst[1] = a[1] - b[1];
    dst[2] = a[2] - b[2]; 
}

float v3_dot_product(float *a, float *b) {
    float prodX = a[0] * b[0];
    float prodY = a[1] * b[1];
    float prodZ = a[2] * b[2];
    return prodX + prodY + prodZ;
}

void v3_cross_product(float *dst, float *a, float *b) {
    float i = (a[1] * b[2]) - (a[2] * b[1]);
    float j = -((a[0] * b[2]) - (a[2] * b[0]));
    float k = (a[0] * b[1]) - (a[1] * b[0]);
    dst[0] = i;
    dst[1] = j;
    dst[2] = k;
}

void v3_scale(float *dst, float s) {
    dst[0] = dst[0] * s;
    dst[1] = dst[1] * s;
    dst[2] = dst[2] * s;
}

float v3_angle(float *a, float *b) {
    float dot = v3_dot_product(a, b);
    float magA = v3_length(a);
    float magB = v3_length(b);
    if(magA == 0.0f || magB == 0.0f) {
        fprintf(stderr, "Error: One of the vectors used has a magnitude of 0.\n");
        return 0.0f;
    }
    // clamping
    float cos_theta = dot / (magA * magB);
    if(cos_theta > 1.0f) {
        cos_theta = 1.0f;
    }
    if(cos_theta < -1.0f) {
        cos_theta = -1.0f;
    }
    return acosf(cos_theta);
}

float v3_angle_quick(float *a, float *b) {
    float dot = v3_dot_product(a, b);
    float magA = v3_length(a);
    float magB = v3_length(b);
    if(magA == 0.0f || magB == 0.0f) {
        fprintf(stderr, "Error: One of the vectors used has a magnitude of 0.\n");
        return 0.0f;
    }
    return dot / (magA * magB);
}

void v3_reflect(float *dst, float *v, float *n) {
    float dot = v3_dot_product(v, n);
    float scalar = 2.0f * dot;
    float x = v[0] - (scalar * n[0]);
    float y = v[1] - (scalar * n[1]);
    float z = v[2] - (scalar * n[2]);
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}

float v3_length(float *a) {
    float x = a[0] * a[0];
    float y = a[1] * a[1];
    float z = a[2] * a[2];
    return sqrtf(x + y + z);
}

void v3_normalize(float *dst, float *a) {
    float mag = v3_length(a);
    if(mag == 0.0f) {
        fprintf(stderr, "Error: The vector used for normalization has a magnitude of 0.\n");
        return;
    }
    dst[0] = a[0] / mag;
    dst[1] = a[1] / mag;
    dst[2] = a[2] / mag;
}

bool v3_equals(float *a, float *b, float tolerance) {
    if(fabsf(a[0] - b[0]) > tolerance) {
        return false;
    }
    if(fabsf(a[1] - b[1]) > tolerance) {
        return false;
    }
    if(fabsf(a[2] - b[2]) > tolerance) {
        return false;
    }
    return true;
}