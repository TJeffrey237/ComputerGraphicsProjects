#include "v3math.h"

// helper function
void v3_print(float *v) {
    printf("[%f, %f, %f]", v[0], v[1], v[2]);
}

void test_v3_from_points() {
    // code
}

void test_v3_add() {
    printf("\n--- Testing v3_add ---\n");

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

    for(int i = 0; i < 4; i++) {
        float actual[3];
        v3_add(actual, inputs_a[i], inputs_b[i]);
        printf("Test %d: ", i + 1);
        if(v3_equals(actual, expected[i], 0.001f)) {
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
    printf("\n--- Testing v3_subtract ---\n");

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

    for(int i = 0; i < 3; i++) {
        float actual[3];
        v3_subtract(actual, inputs_a[i], inputs_b[i]);
        printf("Test %d: ", i + 1);
        if(v3_equals(actual, expected[i], 0.001f)) {
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
    printf("\n--- Testing v3_dot_product ---\n");

    float inputs_a[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {2.0f, 0.0f, 0.0f},
        {1.0f, 1.5f, 1.5f},
    };
    float inputs_b[3][3] = {
        {0.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {-1.0f, 0.0f, 0.0f},
    };
    float expected[3] = {
        0.0f, 2.0f, -1.0f
    };

    for(int i = 0; i < 3; i++) {
        float actual = v3_dot_product(inputs_a[i], inputs_b[i]);
        printf("Test %d: ", i + 1);
        if(fabsf(actual - expected[i]) <= 0.001f) {
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

            printf("\tExpected: %f\n", expected[i]);
            printf("\tActual: %f\n", actual);
        }
    }
}

void test_v3_cross_product() {
    printf("\n--- Testing v3_cross_product ---\n");

    float inputs_a[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {1.0f, 2.0f, 3.0f},
    };
    float inputs_b[3][3] = {
        {0.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 2.0f, 3.0f},
    };
    float expected[3][3] = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, -1.0f},
        {0.0f, 0.0f, 0.0f},
    };

    for(int i = 0; i < 3; i++) {
        float actual[3];
        v3_cross_product(actual, inputs_a[i], inputs_b[i]);
        printf("Test %d: ", i + 1);
        if(v3_equals(actual, expected[i], 0.001f)) {
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

void test_v3_scale() {
    printf("\n--- Testing v3_scale ---\n");

    float inputs_a[3][3] = {
        {1.0f, 2.0f, 3.0f},
        {5.0f, 5.0f, 5.0f},
        {1.0f, -1.0f, 0.0f},
    };
    float inputs_s[3] = {
        2.0f, 0.0f, -1.0f
    };
    float expected[3][3] = {
        {2.0f, 4.0f, 6.0f},
        {0.0f, 0.0f, 0.0f},
        {-1.0f, 1.0f, 0.0f},
    };

    for(int i = 0; i < 3; i++) {
        float actual[3];
        actual[0] = inputs_a[i][0];
        actual[1] = inputs_a[i][1];
        actual[2] = inputs_a[i][2];
        v3_scale(actual, inputs_s[i]);
        printf("Test %d: ", i + 1);
        if(v3_equals(actual, expected[i], 0.001f)) {
            printf("PASS\n");
        } 
        else {
            printf("FAIL:\n");
            printf("\tInput A: "); 
            v3_print(inputs_a[i]); 
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

void test_v3_angle() {
    printf("\n--- Testing v3_angle ---\n");

    float inputs_a[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
    };
    float inputs_b[3][3] = {
        {0.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {-1.0f, 0.0f, 0.0f},
    };
    float expected[3] = {
        1.57079f, 0.0f, 3.14159f
    };

    for(int i = 0; i < 3; i++) {
        float actual = v3_angle(inputs_a[i], inputs_b[i]);
        printf("Test %d: ", i + 1);
        if(fabsf(actual - expected[i]) <= 0.001f) {
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

            printf("\tExpected: %f\n", expected[i]);
            printf("\tActual: %f\n", actual);
        }
    }
}

void test_v3_angle_quick() {
    // code
}

void test_v3_reflect() {
    printf("\n--- Testing v3_reflect ---\n");

    float inputs_a[3][3] = {
        {1.0f, -1.0f, 0.0f},
        {0.0f, -1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
    };
    float inputs_b[3][3] = {
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
    };
    float expected[3][3] = {
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
    };

    for(int i = 0; i < 3; i++) {
        float actual[3];
        v3_reflect(actual, inputs_a[i], inputs_b[i]);
        printf("Test %d: ", i + 1);
        if(v3_equals(actual, expected[i], 0.001f)) {
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

void test_v3_length() {
    printf("\n--- Testing v3_length ---\n");

    float inputs_a[3][3] = {
        {3.0f, 4.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {3.0f, 2.0f, -1.0f},
    };
    float expected[3] = {
        5.0f, 1.73205f, 3.74166f
    };

    for(int i = 0; i < 3; i++) {
        float actual = v3_length(inputs_a[i]);
        printf("Test %d: ", i + 1);
        if(fabsf(actual - expected[i]) <= 0.001f) {
            printf("PASS\n");
        } 
        else {
            printf("FAIL:\n");
            printf("\tInput A: "); 
            v3_print(inputs_a[i]); 
            printf("\n");

            printf("\tExpected: %f\n", expected[i]);
            printf("\tActual: %f\n", actual);
        }
    }
}

void test_v3_normalize() {
    printf("\n--- Testing v3_normalize ---\n");

    float inputs_a[3][3] = {
        {5.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 2.0f, 3.0f},
    };
    float expected[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.57735f, 0.57735f, 0.57735f},
        {0.26726f, 0.53452f, 0.80178f},
    };

    for(int i = 0; i < 3; i++) {
        float actual[3];
        v3_normalize(actual, inputs_a[i]);
        printf("Test %d: ", i + 1);
        if(v3_equals(actual, expected[i], 0.001f)) {
            printf("PASS\n");
        } 
        else {
            printf("FAIL:\n");
            printf("\tInput A: "); 
            v3_print(inputs_a[i]); 
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

int main() {
    test_v3_add();
    test_v3_subtract();
    test_v3_dot_product();
    test_v3_cross_product();
    test_v3_scale();
    test_v3_angle();
    test_v3_reflect();
    test_v3_length();
    test_v3_normalize();

    return 0;
}