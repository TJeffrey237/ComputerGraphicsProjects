#include <stdio.h>
#include "v3math.h"

// helper function
void v3_print(float *v) {
    printf("[%f, %f, %f]", v[0], v[1], v[2]);
}

void test_v3_from_points() {
    // code
}

void test_v3_add() {
    printf("--- Testing v3_add ---\n");

    float inputs_a[4][3] = {
        {1.0f, 2.0f, 3.0f},
        {10.5f, -2.0f, 0.0f},
        {5.5f, 5.5f, 5.5f},
        {100.0f, 200.0f, 300.0f}
    };
    float inputs_b[4][3] = {
        {4.0f, 5.0f, 6.0f},
        {0.0f, 0.0f, 0.0f},
        {-5.5f, -5.5f, -5.5f},
        {0.1f, 0.2f, 0.3f}
    };
    float expected[4][3] = {
        {5.0f, 7.0f, 9.0f},
        {10.5f, -2.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {100.1f, 200.2f, 300.3f}
    };

    for (int i = 0; i < 4; i++) {
        float actual[3];
        v3_add(actual, inputs_a[i], inputs_b[i]);
        printf("Test %d: ", i + 1);
        if (v3_equals(actual, expected[i], 0.001f)) {
            printf("PASS\n");
        } 
        else {
            printf("FAIL:\n");
            printf("\tInput A: "); 
            v3_print(inputs_a[i]); 
            printf("\n");

            printf("\tInput B: ");
            v3_print(inputs_b[i]);
            printf("\n");

            printf("\tExpected: ");
            v3_print(expected[i]);
            printf("\n");

            printf("\tActual: ");
            v3_print(actual);
            printf("\n");
        }
    }
}

void test_v3_subtract() {
    printf("--- Testing v3_subtract ---\n");

    float inputs_a[3][3] = {
        {10.0f, 10.0f, 10.0f},
        {1.0f, 1.0f, 1.0f},
        {1.5f, 1.5f, 1.5f},
    };
    float inputs_b[3][3] = {
        {3.0f, 2.0f, 1.0f},
        {5.0f, 5.0f, 5.0f},
        {1.5f, 1.5f, 1.5f},
    };
    float expected[3][3] = {
        {7.0f, 8.0f, 9.0f},
        {-4.0f, -4.0f, -4.0f},
        {0.0f, 0.0f, 0.0f},
    };

    for (int i = 0; i < 3; i++) {
        float actual[3];
        v3_subtract(actual, inputs_a[i], inputs_b[i]);
        printf("Test %d: ", i + 1);
        if (v3_equals(actual, expected[i], 0.001f)) {
            printf("PASS\n");
        } 
        else {
            printf("FAIL:\n");
            printf("\tInput A: "); 
            v3_print(inputs_a[i]); 
            printf("\n");

            printf("\tInput B: ");
            v3_print(inputs_b[i]);
            printf("\n");

            printf("\tExpected: ");
            v3_print(expected[i]);
            printf("\n");

            printf("\tActual: ");
            v3_print(actual);
            printf("\n");
        }
    }
}

void test_v3_dot_product() {
    // code
}

void test_v3_cross_product() {
    // code
}

void test_v3_scale() {
    // code
}

void test_v3_angle() {
    // code
}

void test_v3_angle_quick() {
    // code
}

void test_v3_reflect() {
    // code
}

void test_v3_length() {
    // code
}

void test_v3_normalize() {
    // code
}

int main() {
    test_v3_add();
    test_v3_subtract();
    return 0;
}