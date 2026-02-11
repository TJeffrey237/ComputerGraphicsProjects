# Project 2: 3D Math
**Name:** Tyler Jeffrey
**Email:** tsj78@nau.edu

This program creates and tests a library of 3D Vector math.

## Usage
### Directory Structure
- **src/** - holds the implementation files (.c)
- **include/** - holds the header files (.h)
- **tests/** - holds the tests used for each function
- **build/** - holds the compiled object files generated after using Makefile
### Compilation
This project uses a Makefile for compilation. To build, navigate inside the root directory and run:\
```make```\
This will create the v3test executable inside the root directory. To remove build artifacts, run:\
```make clean```
### Running The Executable
Ensure you are still inside the root directory (img410_2_tsj78)
The format for running blur.exe is as follows:\
```./v3test```\
Example usage with premade test images:\
```./blur examples/test1.ppm output.ppm```
**NOTE** The examples above were done on windows, please contact me if there are any issues with platforms.

## Known Issues
There are no known issues at this time.