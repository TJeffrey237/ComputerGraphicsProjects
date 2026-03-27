#include "scene.h"

int read_scene(const char* filename, std::vector<Shape*>& shapes, std::vector<Light*>& lights, Camera& cam) {
    FILE* fp = fopen(filename, "r");
    if(!fp) {
        fprintf(stderr, "Error: Cannot open file %s.\n", filename);
        return -1;
    }

    // buffer holds the text from the file
    char buffer[128];

    if(fscanf(fp, "%127s", buffer) != 1 || strcmp(buffer, "img410scene") != 0) {
        fprintf(stderr, "Error: Invalid scene header.\n");
        fclose(fp);
        return -1;
    }

    while(fscanf(fp, "%127s", buffer) == 1 && strcmp(buffer, "end") != 0) {
        // reading camera data
        if(strcmp(buffer, "camera") == 0) {
            cam.width = 0;
            cam.height = 0;

            while(fscanf(fp, "%127s", buffer) == 1 && strcmp(buffer, ";") != 0) {
                if(strcmp(buffer, "width:") == 0) {
                    fscanf(fp, "%f", &cam.width);
                }
                else if(strcmp(buffer, "height:") == 0) {
                    fscanf(fp, "%f", &cam.height);
                }
            }
        }

        // reading light data
        else if(strcmp(buffer, "light") == 0) {
            Light* L = new Light();

            while(fscanf(fp, "%127s", buffer) == 1 && strcmp(buffer, ";") != 0) {
                if(strcmp(buffer, "position:") == 0) {
                    fscanf(fp, "%f %f %f", &L->position[0], &L->position[1], &L->position[2]);
                }
                else if(strcmp(buffer, "color:") == 0) {
                    fscanf(fp, "%f %f %f", &L->color[0], &L->color[1], &L->color[2]);
                }
                else if(strcmp(buffer, "direction:") == 0) {
                    fscanf(fp, "%f %f %f", &L->direction[0], &L->direction[1], &L->direction[2]);
                }
                else if(strcmp(buffer, "radial_a0:") == 0) {
                    fscanf(fp, "%f", &L->radial_a0);
                }
                else if(strcmp(buffer, "radial_a1:") == 0) {
                    fscanf(fp, "%f", &L->radial_a1);
                }
                else if(strcmp(buffer, "radial_a2:") == 0) {
                    fscanf(fp, "%f", &L->radial_a2);
                }
                else if(strcmp(buffer, "angular_a0:") == 0) {
                    fscanf(fp, "%f", &L->angular_a0);
                }
                else if(strcmp(buffer, "theta:") == 0) {
                    fscanf(fp, "%f", &L->theta);
                }
            }
            lights.push_back(L);
        }

        // reading sphere data
        else if(strcmp(buffer, "sphere") == 0) {
            float pos[3] = {0.0f, 0.0f, 0.0f};
            float col[3] = {0.0f, 0.0f, 0.0f};
            float spec[3] = {0.0f, 0.0f, 0.0f};
            float radius = 0.0f;
            float ns = 20.0f;
            float reflection = 0.0f;
            char texture_name[65] = "";


            while(fscanf(fp, "%127s", buffer) == 1 && strcmp(buffer, ";") != 0) {
                if(strcmp(buffer, "position:") == 0) {
                    fscanf(fp, "%f %f %f", &pos[0], &pos[1], &pos[2]);
                }
                else if(strcmp(buffer, "c_diff:") == 0) {
                    fscanf(fp, "%f %f %f", &col[0], &col[1], &col[2]);
                }
                else if(strcmp(buffer, "radius:") == 0) {
                    fscanf(fp, "%f", &radius);
                }
                else if(strcmp(buffer, "c_spec:") == 0) {
                    fscanf(fp, "%f %f %f", &spec[0], &spec[1], &spec[2]);
                }
                else if(strcmp(buffer, "ns:") == 0) {
                    fscanf(fp, "%f", &ns);
                }
                else if(strcmp(buffer, "reflection:") == 0) {
                    fscanf(fp, "%f", &reflection);
                }
                else if(strcmp(buffer, "texture:") == 0) {
                    fscanf(fp, "%64s", texture_name);
                }
            }
            
            Sphere* s = new Sphere(pos, radius, col, spec, ns, reflection);

            if(strlen(texture_name) > 0) {
                s->texture = new PPMImage();
                if(s->texture->readPPM(texture_name)) {
                    s->has_texture = true;
                }
                else {
                    fprintf(stderr, "Warning: Unable to read texture %s.", texture_name);
                    delete s->texture;
                    s->texture = nullptr;
                }
            }

            shapes.push_back(s);
        }

        // reading plane data
        else if(strcmp(buffer, "plane") == 0) {
            float pos[3] = {0.0f, 0.0f, 0.0f};
            float col[3] = {0.0f, 0.0f, 0.0f};
            float norm[3] = {0.0f, 0.0f, 0.0f};
            float spec[3] = {0.0f, 0.0f, 0.0f};
            float ns = 20.0f;
            float reflection = 0.0f;

            while(fscanf(fp, "%127s", buffer) == 1 && strcmp(buffer, ";") != 0) {
                if(strcmp(buffer, "position:") == 0) {
                    fscanf(fp, "%f %f %f", &pos[0], &pos[1], &pos[2]);
                }
                else if(strcmp(buffer, "c_diff:") == 0) {
                    fscanf(fp, "%f %f %f", &col[0], &col[1], &col[2]);
                }
                else if(strcmp(buffer, "normal:") == 0) {
                    fscanf(fp, "%f %f %f", &norm[0], &norm[1], &norm[2]);
                }
                else if(strcmp(buffer, "c_spec:") == 0) {
                    fscanf(fp, "%f %f %f", &spec[0], &spec[1], &spec[2]);
                }
                else if(strcmp(buffer, "ns:") == 0) {
                    fscanf(fp, "%f", &ns);
                }
                else if(strcmp(buffer, "reflection:") == 0) {
                    fscanf(fp, "%f", &reflection);
                }
            }
            shapes.push_back(new Plane(pos, norm, col, spec, ns, reflection));
        }
    }

    fclose(fp);
    return shapes.size();
}