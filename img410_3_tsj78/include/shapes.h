#ifndef SHAPES_H
#define SHAPES_H

#include "v3math.h"
#include <cmath>

class Shape {
public: 
    float position[3];
    float color[3];

    virtual ~Shape() {};
    virtual float intersect(float* Ro, float* Rd) = 0;
};

class Sphere : public Shape {
public:
    float radius;

    Sphere(float* pos, float r, float* col) {
        radius = r;
        for(int i = 0; i < 3; i++) {
            position[i] = pos[i];
            color[i] = col[i];
        }
    };

    float intersect(float* Ro, float* Rd) override {
        float L[3];
        v3_subtract(L, Ro, position);

        float a = v3_dot_product(Rd, Rd);
        float b = 2.0f * v3_dot_product(Rd, L);
        float c = v3_dot_product(L, L) - (radius * radius); 

        float discriminant = (b * b) - (4.0f * a * c);
        if(discriminant < 0) {
            return -1.0f;
        }

        float t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
        float t1 = (-b + sqrtf(discriminant)) / (2.0f * a);

        if(t0 > 0.0001) {
            return t0;
        }
        if(t1 > 0.0001) {
            return t1;
        }

        return -1.0f;
    }
};

class Plane : public Shape {
public:
    float normal[3];

    Plane(float* pos, float* norm, float* col) {
        v3_normalize(normal, norm);
        for(int i = 0; i < 3; i++) {
            position[i] = pos[i];
            color[i] = col[i];
        }
    };

    float intersect(float* Ro, float* Rd) override {
        float dot_n = v3_dot_product(Rd, normal);

        if(fabsf(dot_n) < 0.0001) {
            return -1.0f;
        } 

        float L[3];
        v3_subtract(L, position, Ro);
        float t = v3_dot_product(L, normal) / dot_n;

        return (t > 0.0001) ? t : -1.0f;
    }
};

class Camera {
public:
    float width;
    float height;
};

#endif