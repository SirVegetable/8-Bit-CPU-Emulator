
#ifndef MEMORY_HPP
#define MEMORY_HPP

#pragma once

#include "typedefs.h"
#include <iostream> 
class Memory {
public:
    static const size_t MaxMemSize = 64 * 1024;

    Memory();
    ~Memory();

    void initializeMem();

private:
    Byte data[MaxMemSize];
};

#endif