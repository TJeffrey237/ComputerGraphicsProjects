#ifndef SHAPES_H
#define SHAPES_H

#include "v3math.h"
#include <cmath>

class Shape {
public: 
    float position[3];
    float color[3];
    float c_spec[3];
    float ns;

    // defaults everything
    Shape() : ns(20.0f) {
        for(int i = 0; i < 3; i++) {
            position[i] = 0.0f;
            color[i] = 0.0f;
            c_spec[i] = 0.0f;
        }
    }

    virtual ~Shape() {};
    virtual float intersect(float* Ro, float* Rd) = 0;
    virtual void getNormal(float* hit_point, float* result_normal) = 0;
};

class Sphere : public Shape {
public:
    float radius;

    Sphere(float* pos, float r, float* col, float* spec, float shiny) {
        radius = r;
        ns = shiny;
        for(int i = 0; i < 3; i++) {
            position[i] = pos[i];
            color[i] = col[i];
            c_spec[i] = spec[i];
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

    void getNormal(float* hit_point, float* result_normal) override {
        v3_subtract(result_normal, hit_point, position);
        v3_normalize(result_normal, result_normal);
    }
};

class Plane : public Shape {
public:
    float normal[3];

    Plane(float* pos, float* norm, float* col, float* spec, float shiny) {
        v3_normalize(normal, norm);

        ns = shiny;
        for(int i = 0; i < 3; i++) {
            position[i] = pos[i];
            color[i] = col[i];
            c_spec[i] = spec[i];
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

    void getNormal(float* hit_point, float* result_normal) override {
        result_normal[0] = normal[0];
        result_normal[1] = normal[1];
        result_normal[2] = normal[2];
    }
};

class Light {
public:
    float position[3];
    float color[3];
    float direction[3];
    float theta;
    float angular_a0;
    float radial_a0;
    float radial_a1;
    float radial_a2;
    
    Light() : theta(0.0f), angular_a0(0.0f), radial_a0(1.0f), radial_a1(0.0f), radial_a2(0.0f) {
        for(int i = 0; i < 3; i++) {
            position[i] = 0.0f;
            color[i] = 0.0f;
            direction[i] = 0.0f;
        }
    }
};

class Camera {
public:
    float width;
    float height;
};

#endif