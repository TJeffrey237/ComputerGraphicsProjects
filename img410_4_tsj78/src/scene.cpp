#include "scene.h"

int read_scene(const char* filename, std::vector<Shape*>& shapes, Camera& cam) {
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

        else if(strcmp(buffer, "light") == 0) {
            // read light values
                // set them too
            // default ns to 20
            // check for the semicolon, remember that the file IS supposed to have one
            // otherwise same as the others
        }

        // reading sphere data
        else if(strcmp(buffer, "sphere") == 0) {
            float pos[3] = {0, 0, 0};
            float col[3] = {0, 0, 0};
            float radius = 0;

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
            }
            shapes.push_back(new Sphere(pos, radius, col));
        }

        // reading plane data
        else if(strcmp(buffer, "plane") == 0) {
            float pos[3] = {0, 0, 0};
            float col[3] = {0, 0, 0};
            float norm[3] = {0, 0, 0};

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
            }
            shapes.push_back(new Plane(pos, norm, col));
        }
    }

    fclose(fp);
    return shapes.size();
}