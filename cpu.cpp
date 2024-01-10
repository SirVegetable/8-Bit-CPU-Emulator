#include "cpu.hpp"
#include "typedefs.h"

//Constructor
CPU::CPU()
{
    lookup =
    {
            {CPU::BRK,CPU::IMP_Addr,7},
    };

}
//Destructor 
CPU::~CPU()
{

}


void CPU::Reset(){
    
}
void CPU::NonMaskableInterrupt(){

}
void CPU::InterruptRequest(){

}
void CPU::setFlags(CPU::FLAGS f, bool toSet){
    if(toSet){
        StatusRegister |= f;
    }
    else{
        StatusRegister &= ~f; 
    }

}
CPU::FLAGS CPU::getFlags(CPU::FLAGS f){

}


Byte CPU::Fetch(){
    Byte fetched_data = bus.read(ProgramCounter);
    ProgramCounter++;
    return fetched_data; 
}
void CPU::Execute(){
    // if cycles is 0 then the next instruction can be executed 
    if(Cycles == 0){
        //fetch the opcode
        Byte opcode = Fetch();


    }
}

// --------ADDRESSING MODES----------

// Implied Addressing Mode: Does not require any additional data for ins
Byte CPU::IMP_Addr(){
    
}
// Immediate addressing mode: 
Byte CPU::IMM_Addr(){}

// Zero Page Addressing Mode: 
Byte CPU::ZP_Addr(){

}

// Zero Page + X Register Addressing Mode: 
Byte CPU::ZPX_Addr(){
    
}


// INSTRUCTION SET

// Add With Carry
Byte CPU::ADC(){}

// And (with the Accumulator)
Byte CPU::AND(){}

// Arithmethic Shift Left
Byte CPU::ASL(){}

// Branch on Clear Carry
Byte CPU::BCC(){}

