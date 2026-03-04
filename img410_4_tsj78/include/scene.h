#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include "shapes.h"

int read_scene(const char* filename, std::vector<Shape*>& shapes, std::vector<Light*>& lights, Camera& cam);

#endif