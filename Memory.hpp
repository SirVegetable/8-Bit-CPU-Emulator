
#pragma once
#include <iostream>
#include <array>
#include "typedefs.h"

class Memory{
public:
    Memory(); 
    
    ~Memory();

    //Initialize Memory function
    void initializeMem();

    //Read and Write functions
    Byte read(Rock addr);
    void write(Rock addr, Byte dataToMem);

    //member values 
    static constexpr std::size_t maxMemSize = 64 * 1024;
    std::array<Byte,maxMemSize> ram; 
};

