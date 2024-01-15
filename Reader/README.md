
# Reader DLL
This DLL (Reader.dll) provides a class ReadSTL for reading STL files and extracting information about triangles. This document provides information on using the ReadSTL class.

## ReadSTL Class
## Description
The ReadSTL class is designed to read STL files and extract information about triangles present in the file.

## Public Methods
ReadSTL(): Constructor.
~ReadSTL(): Destructor.
void read(std::string inFilePath, std::vector<Triangle>& inTriangles): Reads an STL file specified by the given file path and populates the provided vector with Triangle objects.
## Building and Linking
To use the ReadSTL class in your project:

Ensure Reader.dll is present in your project directory or accessible in your system's library path.
Include the appropriate headers in your project (#include "ReadSTL.h").
Link against Reader.dll when building your project.
