#include "Memory.hpp"


        //constructor
Memory::Memory()
{
}
        //destructor
Memory::~Memory()
{
}
        //copy assignment operator

void Memory::initializeMem(){
    for(size_t i = 0; i < MaxMemSize; i++){
        data[i] = 0; 
    }
}



