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
Byte CPU::read(Rock address){
    return bus->read(address);

}
void CPU::write(Rock address, Byte data ){
    return bus->write(address, data);
}
void CPU::push(Byte data){
    bus->write(0x0100 + StackPointer, data);
    StackPointer--; 

}
Byte CPU::pop(){
    Byte data = bus->read(0x0100 + StackPointer);
    StackPointer++; 
    return data; 
}

Byte CPU::fetch(){
    Byte fetched_data = read(ProgramCounter);
    ProgramCounter++;
    return fetched_data; 
}
void CPU::execute(){
    // if cycles is 0 then the next instruction can be executed 
    if(cycles == 0){
        //fetch the opcode
        Byte opcode = fetch();
        

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
    so we need our address to point to the next byte, this will be given by the PC.
*/ 
void CPU::IMM_Addr(){
    targetAddress = ProgramCounter++; 

}
/*
    Absolute addressing mode: provides the 16-bit address of a memory location to identify the target.
*/
void CPU::ABS_Addr(){
    Rock lowByte = read(ProgramCounter);
    ProgramCounter++; 
    Rock highByte = read(ProgramCounter);
    ProgramCounter++; 
    targetAddress = lowByte | (highByte << 8);

}
/*
    Absolute addressing + X Register mode: essentially the same thing except the X register is added and if the
    the contents inside the X register causes the address to cross a page boundary an additional
    cycle will need to happen and the pageBoundary will be incremented.

    we can check if the a page boundary is crossed if the highbyte changes after the X register is
    added. 
*/
void CPU::ABSX_Addr(){
    Rock lowByte = read(ProgramCounter);
    ProgramCounter++; 
    Rock highByte = read(ProgramCounter);
    ProgramCounter++;
    targetAddress = lowByte | (highByte << 8);
    targetAddress += X;

    if(targetAddress &= 0xFF00 != highByte){
          
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
    Rock lowByte = read(ProgramCounter);
    ProgramCounter++; 
    Rock highByte = read(ProgramCounter);
    ProgramCounter++;
    targetAddress = lowByte | (highByte << 8);
    targetAddress += Y;

    if(targetAddress &= 0xFF00 != highByte){
          pBoundaryCrossed = 1; 
    }
    else{
        pBoundaryCrossed  = 0; 
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
    Rock pointerAddress = read(ProgramCounter++);
    pBoundaryCrossed = 0; 
    
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
    Rock lowByte = read(ProgramCounter);
    ProgramCounter++;
    Rock highByte = 0x00;
    targetAddress = lowByte | (highByte << 8);
    pBoundaryCrossed = 0; 
}

/*
    Zero Page + X Register Addressing Mode: Essentially the same thing as Zero Page addressing except we add the contents of the
    X register to the low-byte; 
*/
void CPU::ZPX_Addr(){
    Rock lowByte = (read(ProgramCounter) + X); 
    ProgramCounter++;
    Rock highByte = 0x00;
    targetAddress = lowByte | (highByte << 8);
    pBoundaryCrossed = 0; 
}
/*
    Zero Page + Y Register Addressing Mode: Essentially the same thing as Zero Page addressing except we add the contents of the
    Y register to the low-void; 
*/
void CPU::ZPY_Addr(){
    Rock lowByte = (read(ProgramCounter) + Y); 
    ProgramCounter++;
    Rock highByte = 0x00;
    targetAddress = lowByte | (highByte << 8);
    pBoundaryCrossed = 0; 
}

void CPU::REL_Addr(){


}




// ---------INSTRUCTION SET-----------

// Add With Carry
void CPU::ADC(){}

/* 
    AND instruction: This is the Bitwise logic AND, used on the Accumulator with the contents of a byte of memory and set 
    Flags: Z, N
*/ 
void CPU::AND(){
    fetchedData = fetch();

    Accum = Accum & fetchedData;
    BIT_SET(StatusRegister,Z,(Accum == 0x00));
    BIT_SET(StatusRegister,N,(Accum & 0x80));
    pBoundaryCrossed = 1; 
}

// Arithmethic Shift Left
void CPU::ASL(){}

// Branch on Clear Carry
void CPU::BCC(){}

void CPU::BCS(){}

void CPU::BEQ(){}
/*
    BIT instruction: the instruction is used to test if one or more bits are set in a target memory location. Accumulator is ANDed with
    the value in memory to set or clear the Zero flag, result is not kept. Bits 7 and 6 of the value from memory are copied into the N
    and OV flags.
*/
void CPU::BIT(){
    fetchedData = fetch();
    Byte throwAway = Accum & fetchedData; 
    BIT_SET(StatusRegister,Z, (throwAway == 0x00));
    BIT_SET(StatusRegister, N, (fetchedData & (1<<7)));
    BIT_SET(StatusRegister,OV,(fetchedData & (1 << 6)));

    pBoundaryCrossed = 0; 
} 
/*
    Branch If Minus instruction: if the negative flag is set then add the relative displacemenet to the program counter to cause a branch to
    the new location. This instruction increments cycles if branch succeeeds and sets page boundary crossed if its true.  
*/  
void CPU::BMI(){
    bool nFlagCheck = BIT_GRAB(StatusRegister, N);
    if(nFlagCheck){
        Rock newPC = ProgramCounter + relativeDisplacement; 
        targetAddress = newPC;
        cycles++;
        
        if((targetAddress & 0xFF00) != (ProgramCounter & 0xFF00)){
            pBoundaryCrossed = 1; 
        }
        else{
            pBoundaryCrossed = 0; 
        }
        //set program counter to the new TargetAddress
        ProgramCounter = targetAddress; 
    }
}
/*
    Branch If Not Equal instruction: if the Zero flag is clear then add the relative displacement to program counter to cause a branch to a new 
    location. This instruction will increment by one cycles and set page boundary crossed to 1 if its true.
*/
void CPU::BNE(){
    bool nFlagCheck = BIT_GRAB(StatusRegister,N);
    if(nFlagCheck){
        Rock newPC = ProgramCounter + relativeDisplacement;
        targetAddress = newPC;
        cycles++; 
        
        if((targetAddress & 0xFF00) != (ProgramCounter & 0xFF00)){
            pBoundaryCrossed = 1; 
        }
        else{
            pBoundaryCrossed = 0; 
        }
        ProgramCounter = targetAddress; 
    }
}
/*
    Branch If Positive instruction: if the Zero flag is clear then add the relative displacement to the program location to branch to a new
    location. Add a cycle if branch succeeds and set page boundary crossed if its true. 
*/
void CPU::BPL(){
    bool nFlagCheck = BIT_GRAB(StatusRegister,N);
    if(!nFlagCheck){
        Rock newPC = ProgramCounter + relativeDisplacement; 
        targetAddress = newPC;
        cycles++; 
        
        if((targetAddress & 0xFF00) != (ProgramCounter & 0xFF00)){
            pBoundaryCrossed = 1; 
        }
        else{
            pBoundaryCrossed = 0;
        }
        ProgramCounter = targetAddress; 
    }
}

/*
    Break instruction: This is similiar to the IRQ but for software not the hardware, it forces the generation of an interrupt request.The program 
    counter and status register are pushed on the stack then IRQ interrupt vector is at $FFFE/F is loaded into the PC and the break
    flag in the status is set to one and ID flag is set to 0; 
    Note: Program counter is incremented by 2 so it points to the second byte after the opcode
*/
void CPU::BRK(){
    ProgramCounter += 2;

    BIT_SET(StatusRegister,ID,1);
    push((ProgramCounter &= 0xFF00));
    push((ProgramCounter &= 0xFF00));
    
    BIT_SET(StatusRegister,B,1);
    push(StatusRegister);

    BIT_SET(StatusRegister,B,0);
    ProgramCounter = static_cast<Rock>((read(0xFFFE) | read(0xFFFF)));

}
/*
    Branch if Overflow Clear instruction: If the overflow flag is clear then add the relative displacement to the program counter to cause a branch to
    a new location. If branch is successful cycles is incremented and check if page boundary is crossed.

*/
void CPU::BVC(){
    bool overflowFlag = BIT_GRAB(StatusRegister,OV);
    if(!overflowFlag){
        Rock newPC = ProgramCounter + relativeDisplacement;
        targetAddress = newPC; 
        cycles++;

        if((targetAddress &= 0xFF00) != (ProgramCounter &= 0xFF00)){
            pBoundaryCrossed = 1; 
        }
        else{
            pBoundaryCrossed = 0; 
        }
        ProgramCounter = targetAddress;
        
    }

}
/*
    Branch If Overflow Set instruction: if the Overflow flag is set then add the relative displacement to the program counter and branch to new
    location. If branch succeeds cycles is incremeneted and check if page boundary is crossed then we store that for cycle increments later.
*/
void CPU::BVS(){
    bool overflowFlag = BIT_GRAB(StatusRegister,OV);
    if(overflowFlag){
        Rock newPC = ProgramCounter + relativeDisplacement; 
        targetAddress = newPC;
        cycles++; 
        
        if((targetAddress &= 0xFF00) != (ProgramCounter &= 0xFF00)){
            pBoundaryCrossed = 1; 
        }
        else{
            pBoundaryCrossed = 0; 
        }
        ProgramCounter = targetAddress;
    }

}
/*
    Clear Carry Flag: set the carry flag to 0.
*/
void CPU::CLC(){
    BIT_SET(StatusRegister,C, 0);
    pBoundaryCrossed = 0; 
}
/*
    Clear Deceimal flag: set decimal flag to 0; 
*/
void CPU::CLD(){
    BIT_SET(StatusRegister,D,0);
    pBoundaryCrossed = 0; 
}
/*
    Clear Interrupt Disable: set interrupt disable to 0; 
*/
void CPU::CLI(){
    BIT_SET(StatusRegister,ID,0);
    pBoundaryCrossed = 0; 
}

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
    pBoundaryCrossed = 0; 
}