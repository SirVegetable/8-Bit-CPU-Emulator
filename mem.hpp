
#ifndef MEM_HPP
#define MEM_HPP
#include <iostream>
#include <array> 

class Memory{
public:
    Memory(); 
    
    ~Memory();

    //Mem initialize function, that represents
    void initializeMem(); 
 
    static constexpr std::size_t MaxMemSize = 64 * 1024; 
};

#endif