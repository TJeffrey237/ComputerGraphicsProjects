# P1 Overview
Name: Tyler Jeffrey\
Email: tsj78@nau.edu

This is a command-line utility that applied a 3x3 Gaussian Blur filter to ASCII PPM (P3) images.

## Usage
### Directory Structure
- **src/** - holds the implementation files (.cpp)
- **include/** - holds the header files (.h)
- **examples/** - sample PPM images for testing
- **build/** - holds the compiled object files generated after using Makefile
### Compilation
This project uses a Makefile for compilation. To build, navigate inside the root directory and run:\
```make```\
This will create the blur executable inside the root directory. To remove build artifacts, run:\
```make clean```
### Running The Executable
The format for running blur.exe is as follows:\
```./blur <input_path> <output_path>```\
Example usage with premade test images:\
```./blur examples/test1.ppm output.ppm```

## Known Issues
There are no known issues at this time.
