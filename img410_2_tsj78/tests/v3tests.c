#include "v3math.h"

int main() {
    // something
    return 0;
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
        } else {
            printf("FAIL\n");
            printf("  Input A:  [%f, %f, %f]\n", inputs_a[i][0], inputs_a[i][1], inputs_a[i][2]);
            printf("  Input B:  [%f, %f, %f]\n", inputs_b[i][0], inputs_b[i][1], inputs_b[i][2]);
            printf("  Expected: [%f, %f, %f]\n", expected[i][0], expected[i][1], expected[i][2]);
            printf("  Actual:   [%f, %f, %f]\n", actual[0], actual[1], actual[2]);
        }
    }
}