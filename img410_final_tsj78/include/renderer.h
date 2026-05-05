#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include <vector>
#include <limits>

#include "shapes.h"

void render(uint32_t width, uint32_t height, const Camera& cam,
            const std::vector<Shape*>& shapes, const std::vector<Light*>& lights, std::vector<uint8_t>& buffer);
            
void ray_trace(float* Ro, float* Rd,  const std::vector<Shape*>& shapes,
            const std::vector<Light*>& lights, int depth, float* out_color);

#endif