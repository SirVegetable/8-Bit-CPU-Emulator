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
    Byte read(Rock addr);

    //Members     
    public:
        Memory Mem;

};
#endif 