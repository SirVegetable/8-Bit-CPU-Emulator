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
Byte Memory::read(Rock addr){
        if(addr >= 0x0000 && addr <= 0xFFFF ){
                return data[addr];
        }
        else{
                return 0x00; 
        }
}



