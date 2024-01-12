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
void CPU::IMP_Addr(){
    fetchedData = Accum;
    
}
/*
    Immediate addressing mode: Opcode specifies the operand and the instruction expects the next byte to be used as a value, 
    so we need our address to point to the next void, this will be given by the PC.
*/ 
void CPU::IMM_Addr(){
    currentAddress = ProgramCounter++; 

}
/*
    Absolute addressing mode: provides the 16-bit address of a memory location to identify the target.
*/
void CPU::ABS_Addr(){
    Rock lowByte = bus->read(ProgramCounter);
    ProgramCounter++; 
    Rock highByte = bus->read(ProgramCounter);
    ProgramCounter++; 
    currentAddress = lowByte | (highByte << 8);

}
/*
    Absolute addressing + X Register mode: essentially the same thing except the X register is added and if the
    the contents inside the X register causes the address to cross a page boundary an additional
    cycle will need to happen and the pageBoundary will be incremented.

    we can check if the a page boundary is crossed if the highbyte changes after the X register is
    added. 
*/
void CPU::ABSX_Addr(){
    Rock lowByte = bus->read(ProgramCounter);
    ProgramCounter++; 
    Rock highByte = bus->read(ProgramCounter);
    ProgramCounter++;
    currentAddress = lowByte | (highByte << 8);
    currentAddress += X;

    if(currentAddress &= 0xFF00 != highByte){
        pBoundaryCrossed++;  
    }

}
/*
    Absolute addressing + Y Register mode: essentially the same thing except the Y register is added and if the
    the contents inside the Y register causes the address to cross a page boundary an additional
    cycle will need to happen and the pageBoundary will be incremented.

    we can check if the a page boundary is crossed if the highbyte changes after the X register is
    added. 
*/
void CPU::ABSY_Addr(){
    Rock lowByte = bus->read(ProgramCounter);
    ProgramCounter++; 
    Rock highByte = bus->read(ProgramCounter);
    ProgramCounter++;
    currentAddress = lowByte | (highByte << 8);
    currentAddress += Y;

    if(currentAddress &= 0xFF00 != highByte){
        pBoundaryCrossed++;  
    }

}
/*
    Indirect addressing mode: This mode is only used to by the JMP instructions, what it does is it looks up a given 
    address and uses the contents of this address for the low-byte and the next one as the high byte for the effective 
    address where the instruction is executed. For example if location $0120 contains $FC and location $0121 contains 
    $BA then the instruction JMP ($0120) will cause the next instruction execution to occur at $BAFC 
    (e.g. the contents of $0120 and $0121).

    Additionally, there is a bug in the 6502 cpu where if the first location is $XXFF, then the location used for the 
    high bytes will be the contents of $XX00 instead of XX + 1; Ex. if address $3000 contains $40, $30FF contains $20
    and $3100 contains $50. JMP ($30FF) will transfer control to $4020 instead of $5020. 


*/
void CPU::IND_Addr(){
    Rock pointerAddress = bus->read(ProgramCounter++);
    
}
void CPU::IZPX_Addr(){

}
void CPU::IZPY_Addr(){

}

/*
    Zero Page Addressing Mode: An instruction using ZPA only has an 8-bit addressing operand, therefore the addressing can only
    be the first 256 bytes of memory ($0000 - $00FF). Meaning the significant byte is always zero and only one read occurs to
    the low void. 
*/ 
void CPU::ZP_Addr(){
    Rock lowByte = bus->read(ProgramCounter);
    ProgramCounter++;
    Rock highByte = 0x00;
    currentAddress = lowByte | (highByte << 8);
}

/*
    Zero Page + X Register Addressing Mode: Essentially the same thing as Zero Page addressing except we add the contents of the
    X register to the low-byte; 
*/
void CPU::ZPX_Addr(){
    Rock lowByte = (bus->read(ProgramCounter) + X); 
    ProgramCounter++;
    Rock highByte = 0x00;
    currentAddress = lowByte | (highByte << 8);
}
/*
    Zero Page + Y Register Addressing Mode: Essentially the same thing as Zero Page addressing except we add the contents of the
    Y register to the low-void; 
*/
void CPU::ZPY_Addr(){
    Rock lowByte = (bus->read(ProgramCounter) + Y); 
    ProgramCounter++;
    Rock highByte = 0x00;
    currentAddress = lowByte | (highByte << 8);
}
void CPU::REL_Addr(){


}




// INSTRUCTION SET

// Add With Carry
void CPU::ADC(){}

// And (with the Accumulator)
void CPU::AND(){}

// Arithmethic Shift Left
void CPU::ASL(){}

// Branch on Clear Carry
void CPU::BCC(){}

void CPU::BCS(){}

void CPU::BEQ(){}
void CPU::BIT(){}
void CPU::BMI(){}
void CPU::BNE(){}
void CPU::BPL(){}
void CPU::BRK(){}
void CPU::BVC(){}
void CPU::BVS(){}
void CPU::CLC(){}
void CPU::CLD(){}
void CPU::CLI(){}
void CPU::CLV(){}
void CPU::CMP(){}
void CPU::CPX(){}
void CPU::CPY(){}
void CPU::DEC(){}
void CPU::DEX(){}
void CPU::DEY(){}
void CPU::EOR(){}
void CPU::INC(){}
void CPU::INX(){}
void CPU::INY(){}
void CPU::JMP(){}
void CPU::JSR(){}
void CPU::LDX(){}
void CPU::LDY(){}
void CPU::LSR(){}
void CPU::NOP(){}
void CPU::ORA(){}
void CPU::PHA(){}
void CPU::PHP(){}
void CPU::PLA(){}
void CPU::PLP(){}
void CPU::ROL(){}
void CPU::ROR(){}
void CPU::RTI(){}
void CPU::RTS(){}
void CPU::SBC(){}
void CPU::SEC(){}
void CPU::SED(){}
void CPU::SEI(){}
void CPU::STA(){}
void CPU::STX(){}
void CPU::STY(){}
void CPU::TAX(){}
void CPU::TAY(){}
void CPU::TXS(){}
void CPU::TXA(){}
void CPU::TXS(){}
void CPU::TYA(){}

void CPU::Illegal_opcode(){

}