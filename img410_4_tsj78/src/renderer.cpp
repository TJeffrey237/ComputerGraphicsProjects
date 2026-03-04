#include "renderer.h"

void render(uint32_t width, uint32_t height, const Camera& cam,
            const std::vector<Shape*>& shapes, const std::vector<Light*>& lights, std::vector<uint8_t>& buffer) {
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
                    // getting the normal at the intersection point
                    float P[3], N[3];
                    P[0] = Ro[0] + closest_t * Rd[0];
                    P[1] = Ro[1] + closest_t * Rd[1];
                    P[2] = Ro[2] + closest_t * Rd[2];
                    closest_shape->getNormal(P, N);

                    float final_color[3] = {0.0f, 0.0f, 0.0f};

                    for(Light* L : lights) {
                        // STEP 1: Checking for shadows 
                        float L_ray[3];
                        v3_subtract(L_ray, L->position, P);
                        float dist_to_light[3] = v3_length(L_ray);
                        v3_normalize(L_ray, L_ray);
                        // offset origin with 0.001
                        float shadow_origin[3] = {P[0] + N[0] * 0.001f, P[1] + N[1] * 0.001f, P[2] + N[2] * 0.001f}

                        bool in_shadow = false;
                        for(Shape* s : shapes) {
                            float shadow_t = s->intersect(shadow_origin, L_ray)
                            if(shadow_t > 0.0001f && shadow_t < dist_to_light) {
                                in_shadow = true;
                                break;
                            }
                        }

                        if(in_shadow) {
                            continue;
                        }

                        float illumination[3] = {0.0f, 0.0f, 0.0f};
                        float rad_attn = 1.0f / (L->radial_a2 * (dist_to_light * dist_to_light) + L->radial_a1 * dist_to_light + L->radial_a0);
                        float ang_attn = 1.0f;
                        // check for spotlight and calc angular attenuation
                        if(L->theta > 0) {

                        }

                        // 
                    }


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