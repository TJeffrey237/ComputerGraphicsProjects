# Project 6: Texturing
**Name:** Tyler Jeffrey
**Email:** tsj78@nau.edu

This program implements texture mapping to objects.

## Usage
### Directory Structure
- **src/** - holds the implementation files (.c & .cpp)
- **include/** - holds the header files (.h)
- **examples/** - holds the test scene file.
- **build/** - holds the compiled executable generated after using Makefile
### Compilation
This project uses a Makefile for compilation. To build, navigate inside the root directory and run:\
```make```\
This will create the raycast executable inside the build folder. To remove build artifacts, run:\
```make clean```
### Running The Executable
Ensure you are still inside the root directory (img410_6_tsj78)
The format for running raycast.exe is as follows:\
```./build/raycast <img_width> <img_height> <scenefile.scene> <output.ppm>```\
Here is an example command using the available test scene image inside the examples folder:\
```./build/raycast 400 420 examples/test1.scene output.ppm```\
The <output.ppm> image can be found inside the root directory for viewing.

**NOTE** The examples above were done on windows, please contact me if there are any issues with platforms.

## Known Issues
1. Because texture mapping has only been implemented on the Sphere object, it is currently impossible to try mapping the texture onto a Plane object.
