#ifndef SHAPES_H
#define SHAPES_H

#include "v3math.h"
#include <cmath>

class Shape {
public:
    Vector3 position;
    Vector3 color;

    virtual ~Shape() {};
    virtual float intersect(Vector3 Ro, Vector3 Rd) = 0;
};

class Sphere : public Shape {
public:
    float radius;

    Sphere(Vector3 pos, float r, Vector3 col) : position(pos), color(col), radius(r) {};
    float intersect(Vector3 Ro, vector3 Rd) override {
        Vector3 L = v3_subtract(Ro, position);

        float a = v3_dot_product(Rd, Rd);
        float b = 2.0f * v3_dot_product(Rd, L);
        float c = v3_dot_product(L, L) - (radius * radius);
    }
}

class Plane : public Shape {
public:
    Vector3 normal;

    Plane(Vector3 pos, Vector3 norm, Vector3 col) : position(pos), color(col), normal(norm) {};
    float intersect(Vector3 Ro, Vector3 Rd) override {
        float dot_n = v3_dot_product(Rd, normal);

        if(fabs(dot_n) < 0.0001) {
            return -1.0f;
        }

        Vector3 L = v3_subtract(position, Ro);
        float t = v3_dot_product(L, normal) / dot_n;

        return (t > 0) ? t : -1.0f;
    }
}

class Camera {
public:
private:
};

#endif