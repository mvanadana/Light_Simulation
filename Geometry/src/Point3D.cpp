#include "pch.h"
#include "Point3D.h"

Point3D::Point3D(double inX, double inY, double inZ) : mX(0.0), mY(0.0), mZ(0.0)
{
    mX = inX;
    mY = inY;
    mZ = inZ;
}

Point3D::~Point3D()
{

}

double Point3D::x() const
{
    return mX;
}

double Point3D::y() const
{
    return mY;
}

double Point3D::z() const
{
    return mZ;
}

void Point3D::setX(double inX)
{
    mX = inX;
}

void Point3D::setY(double inY)
{
    mY = inY;
}

void Point3D::setZ(double inZ)
{
    mZ = inZ;
}
