#include "renderer.h"

#define MAX_DEPTH 5

void ray_trace(float* Ro, float* Rd,  const std::vector<Shape*>& shapes, const std::vector<Light*>& lights, int depth, float* final_color) {
    if(depth > MAX_DEPTH) {
        final_color[0] = 0;
        final_color[1] = 0;
        final_color[2] = 0;
        return;
    }

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

    if(closest_shape) {
        // getting the normal at the intersection point
        float P[3], N[3];
        P[0] = Ro[0] + closest_t * Rd[0];
        P[1] = Ro[1] + closest_t * Rd[1];
        P[2] = Ro[2] + closest_t * Rd[2];
        closest_shape->getNormal(P, N);

        float diffuse_color[3];

        // tex mapping
        if(closest_shape->has_texture && closest_shape->texture != nullptr) {
            float u, v;
            closest_shape->getUV(P, u, v);

            int tx = (int)(u * closest_shape->texture->width);
            int ty = (int)(v * closest_shape->texture->height);

            // clamping tx and ty to be within the texture dimensions
            tx = std::max(0, std::min(tx, closest_shape->texture->width - 1));
            ty = std::max(0, std::min(ty, closest_shape->texture->height - 1));

            int tex_index = (ty * closest_shape->texture->width + tx) * 3;

            // coverting back to values between 0.0 and 1.0
            diffuse_color[0] = closest_shape->texture->pixels[tex_index] / 255.0f;
            diffuse_color[1] = closest_shape->texture->pixels[tex_index + 1] / 255.0f;
            diffuse_color[2] = closest_shape->texture->pixels[tex_index + 2] / 255.0f;
        }
        else {
            diffuse_color[0] = closest_shape->color[0];
            diffuse_color[1] = closest_shape->color[1];
            diffuse_color[2] = closest_shape->color[2];
        }

        // this is for light calculation

        for(Light* L : lights) {
            // checking for shadows
            float L_ray[3];
            v3_subtract(L_ray, L->position, P);
            float dist_to_light = v3_length(L_ray);
            v3_normalize(L_ray, L_ray);
            // offset origin with 0.001
            float shadow_origin[3] = {P[0] + N[0] * 0.001f, P[1] + N[1] * 0.001f, P[2] + N[2] * 0.001f};

            bool in_shadow = false;
            for(Shape* s : shapes) {
                float shadow_t = s->intersect(shadow_origin, L_ray);
                if(shadow_t > 0.0001f && shadow_t < dist_to_light) {
                    in_shadow = true;
                    break;
                }
            }

            if(in_shadow) {
                continue;
            }

            // calculate attenuation
            float illumination[3] = {0.0f, 0.0f, 0.0f};
            float rad_attn = 1.0f / (L->radial_a2 * (dist_to_light * dist_to_light) + L->radial_a1 * dist_to_light + L->radial_a0);
            float ang_attn = 1.0f;
            // check for spotlight
            if(L->theta > 0) {
                // point to light vector
                float V_obj[3]; 
                v3_subtract(V_obj, P, L->position);
                v3_normalize(V_obj, V_obj);
                float cos_alpha = v3_dot_product(V_obj, L->direction);
                // converting to radians
                float cos_theta = cos(L->theta * 2 * acos(0.0) / 180.0f);
    
                if (cos_alpha < cos_theta) {
                    ang_attn = 0.0f;
                } else {
                    ang_attn = pow(cos_alpha, L->angular_a0);
                }
            }

            // calculate diffuse & specular components
            float n_dot_l = v3_dot_product(N, L_ray);
            if(n_dot_l > 0) {
                illumination[0] += diffuse_color[0] * L->color[0] * n_dot_l;
                illumination[1] += diffuse_color[1] * L->color[1] * n_dot_l;
                illumination[2] += diffuse_color[2] * L->color[2] * n_dot_l;
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

            // sum all of the light contributions
            final_color[0] += rad_attn * ang_attn * illumination[0];
            final_color[1] += rad_attn * ang_attn * illumination[1];
            final_color[2] += rad_attn * ang_attn * illumination[2];
        }

        // this is where we do recursive reflection
        if(closest_shape->reflection > 0) {
            float reflect_Rd[3];
            v3_reflect(reflect_Rd, Rd, N);
            v3_normalize(reflect_Rd, reflect_Rd);

            // new ray from the hit point
            float reflect_Ro[3] = {P[0] + N[0] * 0.001f, P[1] + N[1] * 0.001f, P[2] + N[2] * 0.001f};

            float reflected_color[3] = {0.0f, 0.0f, 0.0f};
            ray_trace(reflect_Ro, reflect_Rd, shapes, lights, depth + 1, reflected_color);

            float ref = closest_shape->reflection;
            final_color[0] = (1.0f - ref) * final_color[0] + ref * reflected_color[0];
            final_color[1] = (1.0f - ref) * final_color[1] + ref * reflected_color[1];
            final_color[2] = (1.0f - ref) * final_color[2] + ref * reflected_color[2];
        }
    }
    else {
        final_color[0] = 0.0f;
        final_color[1] = 0.0f;
        final_color[2] = 0.0f;
        return;
    }
}

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

                float final_color[3] = {0.0f, 0.0f, 0.0f};
                
                // recursively handles color calculation
                ray_trace(Ro, Rd, shapes, lights, 0, final_color);
                
                size_t shape_index = (j * width + i) * 3;
                // clamp the colors
                buffer[shape_index] = (uint8_t)(std::min(1.0f, final_color[0]) * 255);
                buffer[shape_index + 1] = (uint8_t)(std::min(1.0f, final_color[1]) * 255);
                buffer[shape_index + 2] = (uint8_t)(std::min(1.0f, final_color[2]) * 255);
            }
        }
    }