// Reader.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Reader.h"


// This is an example of an exported variable
READER_API int nReader=0;

// This is an example of an exported function.
READER_API int fnReader(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CReader::CReader()
{
    return;
}
