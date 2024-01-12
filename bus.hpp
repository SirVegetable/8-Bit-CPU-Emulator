#pragma once 

#include "Memory.hpp"
#include "cpu.hpp"
#include "typedefs.h"

class Bus
{   
    //Constructor && Destructor
    public: 
        Bus(); 
        ~Bus();

    //Member functions
    void write(Rock addr, Byte dataToMem);
    Byte read(Rock addr);

    //Members     
    public:
        Memory Mem;

};
