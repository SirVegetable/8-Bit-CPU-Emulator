#include "bus.hpp"
#include "Memory.hpp"


Bus::Bus(){
    Mem.initializeMem(); 
}

Bus::~Bus()
{

}
//can use our Memory read & write function 
void Bus::write(Rock addr, Byte dataToMem){
    Mem.write(addr,dataToMem);

}
Byte Bus::read(Rock addr){
    return Mem.read(addr);
}