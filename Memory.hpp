
#ifndef MEMORY_HPP
#define MEMORY_HPP
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
    void write();

    //member values 
    static constexpr std::size_t MaxMemSize = 64 * 1024;
    std::array<Byte,MaxMemSize> data; 
};

#endif