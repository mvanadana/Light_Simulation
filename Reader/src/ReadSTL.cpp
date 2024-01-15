#include "pch.h"
#include "ReadSTL.h"
#include "framework.h"
#include "Point3D.h"

#include <fstream>
#include <sstream>

ReadSTL::ReadSTL()
{

}

ReadSTL::~ReadSTL()
{

}

void ReadSTL::read(std::string inFilePath, std::vector<Triangle>& inTriangles)
{
    std::ifstream dataFile;
    dataFile.open(inFilePath);
    if (!dataFile.is_open())
    {
        return;
    }

    std::string line;
    Point3D normal(0, 0, 0);
    while (std::getline(dataFile, line))
    {
        if (line.find("facet normal") != std::string::npos)
        {
            std::string token;
            std::string toke;
            std::istringstream iss4(line);
            double x, y, z;
            iss4 >> token >> toke >> x >> y >> z;
            normal = Point3D(x, y, z);
        }
        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;

            iss >> token >> x >> y >> z;

            Point3D point1(x, y, z);

            std::getline(dataFile, line);
            std::istringstream iss1(line);
            iss1 >> token >> x >> y >> z;
            Point3D point2(x, y, z);

            std::getline(dataFile, line);
            std::istringstream iss2(line);
            iss2 >> token >> x >> y >> z;
            Point3D point3(x, y, z);

            Triangle triangle(point1, point2, point3);
            triangle.setNormal(normal);
            inTriangles.push_back(triangle);
        }
       
    }
    
}

