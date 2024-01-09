#include "cpu.hpp"
#include "typedefs.h"

//Constructor
CPU::CPU()
{
    
}
//Destructor 
CPU::~CPU()
{

}

void CPU::Clock(){

}
void CPU::Reset(){
    
}
void CPU::NonMaskableInterrupt(){

}
void CPU::InterruptRequest(){

}
void CPU::setFlags(){

}
CPU::FLAGS CPU::getFlags(){

}


Byte CPU::Fetch(){

}

//ADDRESSING MODES 

//Implied function: Does not require any additional data for ins
Byte CPU::IMP_Addr(){
    
}
// Immediate addressing mode: 
Byte CPU::IMM_Addr(){}


// INSTRUCTION SET

// Add With Carry
Byte CPU::ADC(){}

// And (with the Accumulator)
Byte CPU::AND(){}

// Arithmethic Shift Left
Byte CPU::ASL(){}

// Branch on Clear Carry
Byte CPU::BCC(){}

