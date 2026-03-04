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
                        // STEP 1: CHECK FOR SHADOWS
                        float L_ray[3];
                        v3_subtract(L_ray, L->position, P);
                        float dist_to_light = v3_length(L_ray);
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

                        // STEP 2: CALCULATE ATTENUATION
                        float illumination[3] = {0.0f, 0.0f, 0.0f};
                        float rad_attn = 1.0f / (L->radial_a2 * (dist_to_light * dist_to_light) + L->radial_a1 * dist_to_light + L->radial_a0);
                        float ang_attn = 1.0f;
                        // check for spotlight
                        if(L->theta > 0) {
                            float Vobj[3]; 
                            v3_subtract(Vobj, P, L->position);
                            v3_normalize(Vobj, Vobj);
                            float cos_alpha = v3_dot_product(Vobj, L->direction);
                            // converting to radians
                            float cos_theta = cos(L->theta * M_PI / 180.0f);
                            
                            if (cos_alpha < cos_theta) {
                                ang_attn = 0.0f;
                            } else {
                                ang_attn = pow(cos_alpha, L->angular_a0);
                            }
                        }

                        // STEP 3: CALC SPECULAR AND DIFFUSE COMPONENTS
                        float n_dot_l = v3_dot_product(N, L_ray);
                        if(n_dot_l > 0) {
                            illumination[0] += closest_shape->color[0] * L->color[0] * n_dot_l;
                            illumination[1] += closest_shape->color[1] * L->color[1] * n_dot_l;
                            illumination[2] += closest_shape->color[2] * L->color[2] * n_dot_l;
                        }

                        // reflection vector of L_ray about N
                        float NegL_ray[3] = {-L_ray[0], -L_ray[1], -L_ray[2]};
                        float R[3];
                        v3_reflect(R, NegL_ray, N);

                        // view vector
                        float V[3] = {-Rd[0], -Rd[1], -Rd[2]};
                        v3_normalize(V, V);

                        float r_dot_v = v3_dot_product(R, V);
                        if(r_dot_v > 0) {
                            float spec_comp = powf(r_dot_v, closest_shape->ns);
                            illumination[0] += closest_shape->c_spec[0] * L->color[0] * spec_comp;
                            illumination[1] += closest_shape->c_spec[1] * L->color[1] * spec_comp;
                            illumination[2] += closest_shape->c_spec[2] * L->color[2] * spec_comp;
                        }

                        // STEP 4: SUM LIGHT CONTRIBUTIONS
                        final_color[0] += rad_attn * ang_attn * illumination[0];
                        final_color[1] += rad_attn * ang_attn * illumination[1];
                        final_color[2] += rad_attn * ang_attn * illumination[2];
                    }

                    // STEP 5: CLAMP COLORS
                    buffer[shape_index] = (uint8_t)(std::min(1.0f, final_color[0]) * 255);
                    buffer[shape_index + 1] = (uint8_t)(std::min(1.0f, final_color[1]) * 255);
                    buffer[shape_index + 2] = (uint8_t)(std::min(1.0f, final_color[2]) * 255);
                }
                else {
                    buffer[shape_index] = 0;
                    buffer[shape_index + 1] = 0;
                    buffer[shape_index + 2] = 0;
                }

            }
        }
    }