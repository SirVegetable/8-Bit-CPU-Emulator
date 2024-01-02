#include "Memory.hpp"
#include "cpu.hpp"
#ifndef BUS_HPP
#define BUS_HPP
class Bus
{   
    //Constructor && Destructor
    public: 
        Bus(); 
        ~Bus();

    //Member functions
    void write(Rock addr, Byte dataToMem);
    Byte read(); 
    //Members     
    public:
        Memory Mem;
        CPU cpu; 

};
#endif 