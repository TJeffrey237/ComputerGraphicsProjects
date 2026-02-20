#include "renderer.h"

void render(uint32_t width, uint32_t height, const Camera& cam,
            const std::vector<Shape*>& shapes, std::vector<uint8_t>& buffer) {
        float Ro[3] = {0.0f, 0.0f, 0.0f};

        for(uint32_t j = 0; j < height; j++) {
            for(uint32_t i = 0; i < width; i++) {
                // pixel coordinates
                float px = -(cam.width / 2.0f) + cam.width * (i + 0.5f) / width;
                float py = (cam.height / 2.0f) - cam.height * (j + 0.5f) / height;

                float Rd[3] = {px, py, -1.0f};
                v3_normalize(Rd, Rd);

                float closest_t = std::numeric_limits<float>::infinity();
                Shape* closest_shape = nullptr;

                // check for shape intersections
                for(Shape* s : shapes) {
                    float t = s->intersect(Ro, Rd);
                    if(t > 0.0001f && t < closest_t) {
                        closest_t = t;
                        closest_shape = s;
                    }
                }

                size_t shape_index = (j * width + i) * 3;
                if(closest_shape) {
                    buffer[shape_index] = (uint8_t)(closest_shape->color[0] * 255);
                    buffer[shape_index + 1] = (uint8_t)(closest_shape->color[1] * 255);
                    buffer[shape_index + 2] = (uint8_t)(closest_shape->color[2] * 255);
                }
                else {
                    buffer[shape_index] = 0;
                    buffer[shape_index + 1] = 0;
                    buffer[shape_index + 2] = 0;
                }

            }
        }
    }