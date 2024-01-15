#pragma once

#include "pch.h"
#include "Triangle.h"

#include <string>
#include <vector>

class READER_API ReadSTL
{
public:
	ReadSTL();
	~ReadSTL();

	void read(std::string inFilePath, std::vector<Triangle>& inTriangles);

};
