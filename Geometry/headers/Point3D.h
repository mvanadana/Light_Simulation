#pragma once

#include "pch.h"

class GEOMETRY_API Point3D
{
public:
	Point3D(double inX, double inY, double inZ);
	~Point3D();

	double x() const;
	double y() const;
	double z() const;

	void setX(double inX);
	void setY(double inY);
	void setZ(double inZ);

private:
	double mX;
	double mY;
	double mZ;
};
