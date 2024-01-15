
# Geometry DLL
This DLL (Geometry.dll) provides two classes, Point3D and Triangle, for representing 3D points and triangles. This document provides information on using these classes.

## Point3D Class
### Description
The Point3D class represents a point in three-dimensional space with coordinates (x, y, z).

## Public Methods
Point3D(double inX, double inY, double inZ): Constructor to initialize the point with given coordinates.
~Point3D(): Destructor.
double x() const: Returns the x-coordinate of the point.
double y() const: Returns the y-coordinate of the point.
double z() const: Returns the z-coordinate of the point.
void setX(double inX): Sets the x-coordinate of the point.
void setY(double inY): Sets the y-coordinate of the point.
void setZ(double inZ): Sets the z-coordinate of the point.
## Triangle Class
### Description
The Triangle class represents a triangle in three-dimensional space defined by three points.

## Public Methods
Triangle(Point3D inP1, Point3D inP2, Point3D inP3): Constructor to initialize the triangle with three points.
~Triangle(): Destructor.
Point3D p1() const: Returns the first point of the triangle.
Point3D p2() const: Returns the second point of the triangle.
Point3D p3() const: Returns the third point of the triangle.
Point3D normal() const: Returns the normal vector of the triangle.
void setNormal(Point3D inNormal): Sets the normal vector of the triangle.
## Building and Linking
To use these classes in your project:

Ensure Geometry.dll is present in your project directory or accessible in your system's library path.
Include the appropriate headers in your project (#include "Point3D.h" and #include "Triangle.h").
Link against Geometry.dll when building your project.
