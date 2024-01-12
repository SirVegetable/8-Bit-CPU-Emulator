#include "cpu.hpp"
#include "typedefs.h"
#include "bus.hpp"

//Constructor
CPU::CPU()
{
    // lookup =
    // {
    //         {&CPU::BRK,&CPU::IMP_Addr,7}, {&CPU::ORA, &CPU::IZPX_Addr, 6},{&CPU:: , &CPU::, }
    // };

}
//Destructor 
CPU::~CPU()
{

}
void CPU::busConnection(Bus *b){
    bus = b; 
}


void CPU::Reset(){

    
}
void CPU::NonMaskableInterrupt(){

}
void CPU::InterruptRequest(){

}



Byte CPU::Fetch(){
    Byte fetched_data = bus->read(ProgramCounter);
    ProgramCounter++;
    return fetched_data; 
}
void CPU::Execute(){
    // if cycles is 0 then the next instruction can be executed 
    if(cycles == 0){
        //fetch the opcode
        Byte opcode = Fetch();
        


    }
}

// --------ADDRESSING MODES----------

/*
    Implied Addressing Mode: These instruction act directly on one or more registers or flags internal to the CPU, 
    single-byte instructions, no operand, excusively target the contents of the Accumulator. 
*/
Byte CPU::IMP_Addr(){
    fetchedData = Accum;

    return 0; 
    
}
/*
    Immediate addressing mode: Opcode specifies the operand and the instruction expects the next byte to be used as a value, 
    so we need our address to point to the next byte, this will be given by the PC.
*/ 
Byte CPU::IMM_Addr(){
    currentAddress = ProgramCounter++; 

    return 0; 

}

/*
    Zero Page Addressing Mode: An instruction using ZPA only has an 8-bit addressing operand, therefore the addressing can only
    be the first 256 bytes of memory ($0000 - $00FF). Meaning the significant byte is always zero, only one read occurs 
*/ 
Byte CPU::ZP_Addr(){
    currentAddress = bus->read(ProgramCounter);

}

// Zero Page + X Register Addressing Mode: 
Byte CPU::ZPX_Addr(){
    
}
// Zero Page + Y Register Adressing Mode: 
Byte CPU::ZPY_Addr(){

}
Byte CPU::REL_Addr(){

}
Byte CPU::ABS_Addr(){

}
Byte CPU::ABSX_Addr(){

}
Byte CPU::ABSY_Addr(){

}
Byte CPU::IND_Addr(){

}
Byte CPU::IZPX_Addr(){

}
Byte CPU::IZPY_Addr(){

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

Byte CPU::BCS(){}

Byte CPU::BEQ(){}
Byte CPU::BIT(){}
Byte CPU::BMI(){}
Byte CPU::BNE(){}
Byte CPU::BPL(){}
Byte CPU::BRK(){}
Byte CPU::BVC(){}
Byte CPU::BVS(){}
Byte CPU::CLC(){}
Byte CPU::CLD(){}
Byte CPU::CLI(){}
Byte CPU::CLV(){}
Byte CPU::CMP(){}
Byte CPU::CPX(){}
Byte CPU::CPY(){}
Byte CPU::DEC(){}
Byte CPU::DEX(){}
Byte CPU::DEY(){}
Byte CPU::EOR(){}
Byte CPU::INC(){}
Byte CPU::INX(){}
Byte CPU::INY(){}
Byte CPU::JMP(){}
Byte CPU::JSR(){}
Byte CPU::LDX(){}
Byte CPU::LDY(){}
Byte CPU::LSR(){}
Byte CPU::NOP(){}
Byte CPU::ORA(){}
Byte CPU::PHA(){}
Byte CPU::PHP(){}
Byte CPU::PLA(){}
Byte CPU::PLP(){}
Byte CPU::ROL(){}
Byte CPU::ROR(){}
Byte CPU::RTI(){}
Byte CPU::RTS(){}
Byte CPU::SBC(){}
Byte CPU::SEC(){}
Byte CPU::SED(){}
Byte CPU::SEI(){}
Byte CPU::STA(){}
Byte CPU::STX(){}
Byte CPU::STY(){}
Byte CPU::TAX(){}
Byte CPU::TAY(){}
Byte CPU::TXS(){}
Byte CPU::TXA(){}
Byte CPU::TXS(){}
Byte CPU::TYA(){}

Byte CPU::Illegal_opcode(){
    return 0; 
}