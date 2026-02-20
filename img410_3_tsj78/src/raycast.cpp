#include <stdio.h>
#include <stdint.h>
#include <vector>

#include "ppm.h"
#include "scene.h"
#include "renderer.h"
#include "v3math.h"

int main(int argc, char **argv) {
    if(argc != 5) {
        fprintf(stderr, "Error: Incorrect number of arguments provided.\n");
        return 1;
    }

    uint32_t img_width = atoi(argv[1]);
    uint32_t img_height = atoi(argv[2]);
    char* input_scene = argv[3];
    char* output_ppm = argv[4];

    if(img_width <= 0 || img_height <= 0) {
        fprintf(stderr, "Error: Invalid image dimensions.\n");
        return 1;
    }

    std::vector<Shape*> shapes;
    Camera cam;

    // STEP 1: READ SCENE DATA
    if(read_scene(input_scene, shapes, cam) < 0) {
        return 1;
    }

    // STEP 2: CAST RAYS
    std::vector<uint8_t> pixel_buffer(img_width * img_height * 3, 0);
    render(img_width, img_height, cam, shapes, pixel_buffer);

    // STEP 3: WRITE TO PPM FILE
    // stuff
}