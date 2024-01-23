#include "cpu.hpp"
#include "typedefs.h"
#include "bus.hpp"

//Constructor
CPU::CPU()
{
    lookup =
    {
            {&CPU::BRK, &CPU::IMP_Addr, 7}, {&CPU::ORA, &CPU::IZX_Addr, 6}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZX_Addr, 8}, {&CPU::NOP, &CPU::ZPO_Addr, 3}, {&CPU::ORA, &CPU::ZPO_Addr, 3}, {&CPU::ASL, &CPU::ZPO_Addr, 5}, {&CPU::IOC, &CPU::ZPO_Addr, 5}, {&CPU::PHP, &CPU::IMP_Addr, 3}, {&CPU::ORA, &CPU::IMM_Addr, 2}, {&CPU::ASL, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::NOP, &CPU::ABS_Addr, 4}, {&CPU::ORA, &CPU::ABS_Addr, 4}, {&CPU::ASL, &CPU::ABS_Addr, 6}, {&CPU::IOC, &CPU::ABS_Addr, 6},
            {&CPU::BPL, &CPU::REL_Addr, 2}, {&CPU::ORA, &CPU::IZY_Addr, 5}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZY_Addr, 8}, {&CPU::NOP, &CPU::ZPX_Addr, 4}, {&CPU::ORA, &CPU::ZPX_Addr, 4}, {&CPU::ASL, &CPU::ZPX_Addr, 6}, {&CPU::IOC, &CPU::ZPX_Addr, 6}, {&CPU::CLC, &CPU::IMP_Addr, 2}, {&CPU::ORA, &CPU::ABY_Addr, 4}, {&CPU::NOP, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::ABS_Addr, 7}, {&CPU::NOP, &CPU::ABX_Addr, 4}, {&CPU::ORA, &CPU::ABX_Addr, 4}, {&CPU::ASL, &CPU::ABX_Addr, 7}, {&CPU::IOC, &CPU::ABX_Addr, 7},
            {&CPU::JSR, &CPU::ABY_Addr, 6}, {&CPU::AND, &CPU::IZX_Addr, 6}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZX_Addr, 8}, {&CPU::BIT, &CPU::ZPO_Addr, 3}, {&CPU::AND, &CPU::ZPX_Addr, 3}, {&CPU::ROL, &CPU::ZPO_Addr, 5}, {&CPU::IOC, &CPU::ZPO_Addr, 5}, {&CPU::PLP, &CPU::IMP_Addr, 4}, {&CPU::AND, &CPU::IMM_Addr, 2}, {&CPU::ROL, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::BIT, &CPU::ABS_Addr, 4}, {&CPU::AND, &CPU::ABS_Addr, 4}, {&CPU::ROL, &CPU::ABS_Addr, 4}, {&CPU::IOC, &CPU::ABS_Addr, 6},
            {&CPU::BMI, &CPU::REL_Addr, 2}, {&CPU::AND, &CPU::IZY_Addr, 5}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZY_Addr, 8}, {&CPU::NOP, &CPU::ZPX_Addr, 4}, {&CPU::AND, &CPU::ZPX_Addr, 4}, {&CPU::ROL, &CPU::ZPX_Addr, 6}, {&CPU::IOC, &CPU::ZPX_Addr, 6}, {&CPU::SEC, &CPU::IMP_Addr, 2}, {&CPU::AND, &CPU::ABY_Addr, 4}, {&CPU::NOP, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::ABY_Addr, 7}, {&CPU::NOP, &CPU::ABX_Addr, 4}, {&CPU::AND, &CPU::ABX_Addr, 4}, {&CPU::ROL, &CPU::ABX_Addr, 7}, {&CPU::IOC, &CPU::ABX_Addr, 7},
            {&CPU::RTI, &CPU::IMP_Addr, 6}, {&CPU::EOR, &CPU::IZX_Addr, 6}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZX_Addr, 8}, {&CPU::NOP, &CPU::ZPO_Addr, 3}, {&CPU::EOR, &CPU::ZPO_Addr, 3}, {&CPU::LSR, &CPU::ZPO_Addr, 5}, {&CPU::IOC, &CPU::ZPO_Addr, 5}, {&CPU::PHA, &CPU::IMP_Addr, 3}, {&CPU::EOR, &CPU::IMM_Addr, 2}, {&CPU::LSR, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::JMP, &CPU::ABS_Addr, 3}, {&CPU::EOR, &CPU::ABS_Addr, 4}, {&CPU::LSR, &CPU::ABS_Addr, 6}, {&CPU::IOC, &CPU::ABS_Addr, 6},
            {&CPU::BVC, &CPU::REL_Addr, 2}, {&CPU::EOR, &CPU::IZY_Addr, 5}, {&CPU::IOC, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::IZY_Addr, 8}, {&CPU::NOP, &CPU::ZPX_Addr, 4}, {&CPU::EOR, &CPU::ZPX_Addr, 4}, {&CPU::LSR, &CPU::ZPX_Addr, 6}, {&CPU::IOC, &CPU::ZPX_Addr, 6}, {&CPU::CLI, &CPU::IMP_Addr, 2}, {&CPU::EOR, &CPU::ABY_Addr, 4}, {&CPU::NOP, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::ABY_Addr, 7}, {&CPU::NOP, &CPU::ABX_Addr, 4}, {&CPU::EOR, &CPU::ABX_Addr, 4}, {&CPU::LSR, &CPU::ABX_Addr, 7}, {&CPU::IOC, &CPU::ABX_Addr, 7},
            {&CPU::RTS, &CPU::IMP_Addr, 6}, {&CPU::ADC, &CPU::IZX_Addr, 5}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZX_Addr, 8}, {&CPU::NOP, &CPU::ZPO_Addr, 3}, {&CPU::ADC, &CPU::ZPO_Addr, 3}, {&CPU::ROR, &CPU::ZPO_Addr, 5}, {&CPU::IOC, &CPU::ZPO_Addr, 5}, {&CPU::PLA, &CPU::IMP_Addr, 4}, {&CPU::ADC, &CPU::IMM_Addr, 2}, {&CPU::ROR, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::JMP, &CPU::IND_Addr, 5}, {&CPU::ADC, &CPU::ABS_Addr, 4}, {&CPU::ROR, &CPU::ABS_Addr, 6}, {&CPU::IOC, &CPU::ABS_Addr, 6},
            {&CPU::BVS, &CPU::REL_Addr, 2}, {&CPU::ADC, &CPU::IZY_Addr, 5}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZY_Addr, 8}, {&CPU::NOP, &CPU::ZPX_Addr, 4}, {&CPU::ADC, &CPU::ZPX_Addr, 4}, {&CPU::ROR, &CPU::ZPX_Addr, 6}, {&CPU::IOC, &CPU::ZPX_Addr, 6}, {&CPU::SEI, &CPU::IMP_Addr, 2}, {&CPU::ADC, &CPU::ABY_Addr, 4}, {&CPU::NOP, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::ABY_Addr, 7}, {&CPU::NOP, &CPU::ABX_Addr, 4}, {&CPU::ADC, &CPU::ABX_Addr, 4}, {&CPU::ROR, &CPU::ABX_Addr, 7}, {&CPU::IOC, &CPU::ABX_Addr, 7},
            {&CPU::NOP, &CPU::IMM_Addr, 2}, {&CPU::STA, &CPU::IZX_Addr, 6}, {&CPU::NOP, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZX_Addr, 6}, {&CPU::STY, &CPU::ZPO_Addr, 3}, {&CPU::STA, &CPU::ZPO_Addr, 3}, {&CPU::STX, &CPU::ZPO_Addr, 3}, {&CPU::IOC, &CPU::ZPO_Addr, 3}, {&CPU::DEY, &CPU::IMP_Addr, 2}, {&CPU::NOP, &CPU::IMM_Addr, 2}, {&CPU::TXA, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::STY, &CPU::ABS_Addr, 4}, {&CPU::STA, &CPU::ABS_Addr, 4}, {&CPU::STX, &CPU::ABS_Addr, 4}, {&CPU::IOC, &CPU::ABS_Addr, 4},
            {&CPU::BCC, &CPU::REL_Addr, 2}, {&CPU::STA, &CPU::IZY_Addr, 6}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZY_Addr, 6}, {&CPU::STY, &CPU::ZPX_Addr, 4}, {&CPU::STA, &CPU::ZPX_Addr, 4}, {&CPU::STX, &CPU::ZPY_Addr, 4}, {&CPU::IOC, &CPU::ZPY_Addr, 4}, {&CPU::TYA, &CPU::IMP_Addr, 2}, {&CPU::STA, &CPU::ABY_Addr, 5}, {&CPU::TXS, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::ABY_Addr, 5}, {&CPU::IOC, &CPU::ABX_Addr, 5}, {&CPU::STA, &CPU::ABX_Addr, 5}, {&CPU::IOC, &CPU::ABY_Addr, 5}, {&CPU::IOC, &CPU::ABY_Addr, 5},
            {&CPU::LDY, &CPU::IMM_Addr, 2}, {&CPU::LDA, &CPU::IZX_Addr, 6}, {&CPU::LDX, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZX_Addr, 6}, {&CPU::LDY, &CPU::ZPO_Addr, 3}, {&CPU::LDA, &CPU::ZPO_Addr, 3}, {&CPU::LDX, &CPU::ZPO_Addr, 3}, {&CPU::IOC, &CPU::ZPO_Addr, 3}, {&CPU::TAY, &CPU::IMP_Addr, 2}, {&CPU::LDA, &CPU::IMM_Addr, 2}, {&CPU::TAX, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::LDY, &CPU::ABS_Addr, 4}, {&CPU::LDA, &CPU::ABS_Addr, 4}, {&CPU::LDX, &CPU::ABS_Addr, 4}, {&CPU::IOC, &CPU::ABS_Addr, 4},
            {&CPU::BCS, &CPU::REL_Addr, 2}, {&CPU::LDA, &CPU::IZY_Addr, 5}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZY_Addr, 5}, {&CPU::LDY, &CPU::ZPX_Addr, 4}, {&CPU::LDA, &CPU::ZPX_Addr, 4}, {&CPU::LDX, &CPU::ZPY_Addr, 4}, {&CPU::IOC, &CPU::ZPY_Addr, 4}, {&CPU::CLV, &CPU::IMP_Addr, 2}, {&CPU::LDA, &CPU::ABY_Addr, 4}, {&CPU::TSX, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::ABY_Addr, 4}, {&CPU::LDY, &CPU::ABX_Addr, 4}, {&CPU::LDA, &CPU::ABX_Addr, 4}, {&CPU::LDX, &CPU::ABY_Addr, 4}, {&CPU::IOC, &CPU::ABY_Addr, 4},
            {&CPU::CPY, &CPU::IMM_Addr, 2}, {&CPU::CMP, &CPU::IZX_Addr, 6}, {&CPU::NOP, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZX_Addr, 8}, {&CPU::CPY, &CPU::ZPO_Addr, 3}, {&CPU::CMP, &CPU::ZPO_Addr, 3}, {&CPU::DEC, &CPU::ZPO_Addr, 5}, {&CPU::IOC, &CPU::ZPO_Addr, 5}, {&CPU::INY, &CPU::IMP_Addr, 2}, {&CPU::CMP, &CPU::IMM_Addr, 2}, {&CPU::DEX, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::CPY, &CPU::ABS_Addr, 4}, {&CPU::CMP, &CPU::ABS_Addr, 4}, {&CPU::DEC, &CPU::ABS_Addr, 6}, {&CPU::IOC, &CPU::ABS_Addr, 6},
            {&CPU::BNE, &CPU::REL_Addr, 2}, {&CPU::CMP, &CPU::IZY_Addr, 5}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZY_Addr, 8}, {&CPU::NOP, &CPU::ZPX_Addr, 4}, {&CPU::CMP, &CPU::ZPX_Addr, 4}, {&CPU::DEC, &CPU::ZPX_Addr, 6}, {&CPU::IOC, &CPU::ZPX_Addr, 6}, {&CPU::CLD, &CPU::IMP_Addr, 2}, {&CPU::CMP, &CPU::ABY_Addr, 4}, {&CPU::NOP, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::ABY_Addr, 7}, {&CPU::NOP, &CPU::ABX_Addr, 4}, {&CPU::CMP, &CPU::ABX_Addr, 4}, {&CPU::DEC, &CPU::ABX_Addr, 7}, {&CPU::IOC, &CPU::ABX_Addr, 7},
            {&CPU::CPX, &CPU::IMM_Addr, 2}, {&CPU::SBC, &CPU::IZX_Addr, 6}, {&CPU::NOP, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZX_Addr, 8}, {&CPU::CPX, &CPU::ZPO_Addr, 3}, {&CPU::SBC, &CPU::ZPO_Addr, 3}, {&CPU::INC, &CPU::ZPO_Addr, 5}, {&CPU::IOC, &CPU::ZPO_Addr, 5}, {&CPU::INX, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::NOP, &CPU::IMP_Addr, 2}, {&CPU::SBC, &CPU::IMM_Addr, 2}, {&CPU::CPX, &CPU::ABS_Addr, 4}, {&CPU::SBC, &CPU::ABS_Addr, 4}, {&CPU::INC, &CPU::ABS_Addr, 6}, {&CPU::IOC, &CPU::ABS_Addr, 6},
            {&CPU::BEQ, &CPU::REL_Addr, 2}, {&CPU::SBC, &CPU::IZY_Addr, 5}, {&CPU::IOC, &CPU::IMM_Addr, 2}, {&CPU::IOC, &CPU::IZY_Addr, 8}, {&CPU::NOP, &CPU::ZPX_Addr, 4}, {&CPU::SBC, &CPU::ZPX_Addr, 4}, {&CPU::INC, &CPU::ZPX_Addr, 4}, {&CPU::IOC, &CPU::ZPX_Addr, 8}, {&CPU::SED, &CPU::IMP_Addr, 2}, {&CPU::SBC, &CPU::ABY_Addr, 4}, {&CPU::NOP, &CPU::IMP_Addr, 2}, {&CPU::IOC, &CPU::ABY_Addr, 7}, {&CPU::NOP, &CPU::ABX_Addr, 4}, {&CPU::SBC, &CPU::ABX_Addr, 4}, {&CPU::INC, &CPU::ABX_Addr, 7}, {&CPU::IOC, &CPU::ABX_Addr, 7},
    };

}
//Destructor 
CPU::~CPU()
{

}
void CPU::busConnection(Bus *b){
    bus = b; 
}

/*
    Reset System Interrupt: This will configure the cpu to a known state, setting the registers Accumulator, X to
    0 and the Stackpointer will be set to the address 0xFF as stack memory is between 0x0100 - 0x01FF, I think the
    value you set these to is arbitrary and would just depend on your routine, I'm setting to 0XFF because the stack
    grows downwards. The program counter will be set to where the reset vector and is held typically at 0xFFFC and 
    0xFFFD - the data at this address is set by the programmer at compile time. The Status register is reset and 
    only the U flag is set. Lastly, the reset takes a total of 8 cycles to complete. 
*/
void CPU::Reset(){
    Accum = 0x00;                                 // Reset Accumulator contents
    X = 0x00;                                     // Reset X register contents 
    Y = 0x00;                                     // Reset Y register contents
    StackPointer = 0xFF;                          // Set stack pointer to the last byte of the Stack
    StatusRegister = 0x00 | (U);                  // Set Unused flag to known state
    targetAddress = 0xFFFC;                       // Target address specified by Reset 
    Rock lowByte  = read(targetAddress + 0 );     // Read the low byte from the target address + 0 (0xFFFC)
    Rock highByte = read(targetAddress + 1);      // Read the high byte from the target address + 1 (0xFFFD)
    ProgramCounter = (highByte << 8) | lowByte;   // Assign contents to the program counter

    relativeDisplacement = 0x0000;                // Reset relative displacement
    targetAddress = 0x0000;                       // Reset target address set
    fetchedData = 0x00;                           // Reset variable holding data
    pPBC = 0;                                     // Reset our bool for page boundary crossed
    cycles = 8;                                   // Reset takes 8 cycles
}

/*
    IRQ: the CPU pushes the program counter and status register to the stack, setting the ID flag in order to 
    ignore further IRQ requests and the program counter will read the values at 0xFFFE and 0xFFFF. IRQ takes
    7 cycles. 
*/
void CPU::InterruptRequest(){
    if(BIT_GRAB(StatusRegister,ID) == 0){
        push((ProgramCounter >> 8 ) & 0x00FF);        // Pushing the high bytes to the stack 
        push((ProgramCounter & 0x00FF));              // Pushing the low bytes to the stack
        BIT_SET(StatusRegister ,B , 0);               // Shows this was a hardware interrupt not a program interrupt
        BIT_SET(StatusRegister, ID , 1);              // Interrupt Disabled bit set 
        BIT_SET(StatusRegister, U , 1)                // Unused bit set to known state
        push(StatusRegister);                         // Push status register to the stack

        targetAddress = 0xFFFE;                       // Address set for IRQ 
        Rock lowByte = read(targetAddress + 0);       // Read the low byte from IRQ specified address
        Rock highByte = read(targetAddress + 1);      // Read the high byte from IRQ specified address 
        ProgramCounter = (highByte << 8) | lowByte;   // Set the read data to the program counter 

        cycles = 7;                                   // IRQ causes 7 cycles to occur

    }

}


/*
    A NMI will behave the same as an IRQ which means it cannot be ignored but reads the new program counter
    from location 0xFFFA. But you do not need to check the Interrupt Disable flag since it is non-maskable.
*/
void CPU::NonMaskableInterrupt(){
    push((ProgramCounter >> 8) & 0x00FF);        // Push the high bytes to the stack
    push((ProgramCounter & 0x00FF));             // Push the low bytes to the stack

    BIT_SET(StatusRegister, B , 0);              // Shows this was a hardware interrupt not a program interrupt
    BIT_SET(StatusRegister, U , 1);              // Set Unused bit to a known state
    BIT_SET(StatusRegister, ID , 1)              // Interruped Disable Bit set 
    push(StatusRegister);                        // Push the status register to the stack 

    targetAddress = 0xFFFA;                      // Set the target address to 0xFFFE
    Rock lowByte = read(targetAddress + 0);      // Read the low byte from the specified NMI address
    Rock highByte = read(targetAddress + 1);     // Read the high byte fromt the specified NMI address
    ProgramCounter = (highByte << 8) | lowByte;  // Assign the contents to the program counter

    cycles = 7;                                  // NMI causes 7 cycles to occur
}

/*
    CPU connects to the bus and reads from the specified memory address. 
*/
Byte CPU::read(Rock address){
    return bus->read(address);

}

/*
    CPU connects to the bus and writes the specified data to the specified memory address. 
*/
void CPU::write(Rock address, Byte data ){
    return bus->write(address, data);
}

/*
    The CPU pushes the specified data to the stack. It must be offset with 0x0100 because 
    the stack is between 0x0100 and 0x01FF. The stack pointer is an unsigned int so it will 
    simulate the wrapping behaviour necessary to remain in the addressable range.
*/
void CPU::push(Byte data){
    bus->write(0x0100 + StackPointer, data);
    StackPointer--; 

}
/*
    The CPU pops the data from the specified location on the stack. It must be offset with 
    0x0100 because the stack is between 0x0100 and 0x01FF. The stack pointer is an unsigned 
    int so it will simulate the wrapping behaviour necessary to remain in the addressable 
    range.
*/
Byte CPU::pop(){
    StackPointer++; 
    Byte data = bus->read(0x0100 + StackPointer);
    return data; 
}
/*
    The CPU fetchs the data from memory from the targetAddress. If the addressing mode is implied 
    then no new data is required otherwise the data needed for the instruction resides at memory
    address pointed at by target address.
*/
Byte CPU::fetch(){
    if(lookup[opcode].addr_mode != &CPU::IMP_Addr){
        Byte fetched_data = read(targetAddress);
        return fetched_data;

    }
    else{
        return fetchedData;  // original contents is returned. 
    }
}
/*
    This function will handle the all of the execution of the instructions.
*/
void CPU::execute(){

    if(cycles == 0){                           // If cycles is 0 then the next instruction can be executed
        Byte opcode = fetch();                 // Fetch the opcode
        ProgramCounter++;                      // Increment program counter 
        BIT_SET(StatusRegister, U , 1);        // Set the status register unused bit to known state just in case.
        cycles = lookup[opcode].cycles;        // Get starting cycles
        (this->*lookup[opcode].addr_mode)();   // Call the addressing mode function
        bool pPBC1 = pPBC;                     // Save the state of pPBC after addressing mode is called
        (this->*lookup[opcode].instruction)(); // Call the opcode instruction
        bool pPBC2 = pPBC;                     // Save the state of pPBC after instruction is called

    }
}

// --------ADDRESSING MODES----------

/*
    Implied Addressing Mode: These instruction act directly on one or more registers or flags internal to the CPU, 
    single-byte instructions, no operand, has a special sub mode called Accumulator addressing for certain instructions 
    that acts directly on the Accumulator, Ex. LSR when in addressing mode will act Logically shift the contents of the 
    Accum hence fetchedData = Accum. 
*/
void CPU::IMP_Addr(){
    fetchedData = Accum;
    pPBC = 0; 
    
}
/*
    Immediate addressing mode: Opcode specifies the operand and the instruction expects the next byte to be used as a value, 
    so we need our address to point to the next byte, this will be given by the PC.
*/ 
void CPU::IMM_Addr(){
    targetAddress = ProgramCounter++; 
    pPBC = 0; 

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
    pPBC = 0; 

}
/*
    Absolute addressing + X Register mode: essentially the same thing except the X register is added and if the
    the contents inside the X register causes the address to cross a page boundary an additional
    cycle will need to happen and the pageBoundary will be incremented.

    we can check if the a page boundary is crossed if the highbyte changes after the X register is
    added. 
*/
void CPU::ABX_Addr(){
    Rock lowByte = read(ProgramCounter);
    ProgramCounter++; 
    Rock highByte = read(ProgramCounter);
    ProgramCounter++;
    targetAddress = lowByte | (highByte << 8);
    targetAddress += X;

    if(targetAddress &= 0xFF00 != highByte){
          pPBC = 1; 
    }
    else{
        pPBC = 0; 
    }

}
/*
    Absolute addressing + Y Register mode: essentially the same thing except the Y register is added and if the
    the contents inside the Y register causes the address to cross a page boundary an additional
    cycle will need to happen and the pageBoundary will be incremented.

    we can check if the a page boundary is crossed if the highbyte changes after the X register is
    added. 
*/
void CPU::ABY_Addr(){
    Rock lowByte = read(ProgramCounter);
    ProgramCounter++; 
    Rock highByte = read(ProgramCounter);
    ProgramCounter++;
    targetAddress = lowByte | (highByte << 8);
    targetAddress += Y;

    if(targetAddress &= 0xFF00 != highByte){
          pPBC = 1; 
    }
    else{
        pPBC  = 0; 
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
    Rock ptrLowByte = read(ProgramCounter);
    ProgramCounter++; 
    Rock ptrHighByte = read(ProgramCounter );
    ProgramCounter++; 
    Rock ptrAddress = (ptrHighByte << 8)  | ptrLowByte;

    if(ptrLowByte == 0x00FF){
        targetAddress = (read(ptrAddress & 0xFF00) << 8) | (read(ptrAddress + 0));
    }
    else{
        targetAddress = (read(ptrAddress + 1) << 8) | (read(ptrAddress + 0));
    }
    pPBC = 0; 
    
}
/*  
    Indexed Indirect addressing mode: used in conjunction with a table of address held on zero page. The address of the table is 
    taken from the instruction and the X register added with it(zero pge wrapped) to give the location of the least significant 
    byte of the target address. 
*/
void CPU::IZX_Addr(){
    Rock addressTable = read(ProgramCounter); 
    ProgramCounter++; 
    addressTable += X; 
    Rock lowByte = read((addressTable & 0x00FF));
    Rock highByte = read((addressTable + 1) & 0x00FF);
    targetAddress = (highByte << 8) | lowByte; 
    pPBC = 0; 

}
/*
    Indirect Indexed addressing mode: the most common indirection mode used on the 6502. In instruction contains the zero page 
    location of the least significant byte of 16 bit address. The address is read from memory into the target address and then
    the contents of the Y register is added to that. If the addition of the Y address changes the highByte then a page boundary
    has been crossed. 
*/
void CPU::IZY_Addr(){
    Rock addressTable = read(ProgramCounter);
    ProgramCounter++;
    Rock lowByte = read(addressTable & 0x00FF);
    Rock highByte = read((addressTable + 1) & 0x00FF);
    targetAddress = (highByte << 8) | lowByte;
    targetAddress += Y; 

    if((targetAddress & 0xFF00) != highByte){           // a page boundary will be crossed only if the high byte changes
        pPBC = 1; 
    }
    else{
        pPBC = 0; 
    }

}

/*
    Zero Page Addressing Mode: An instruction using ZPA only has an 8-bit addressing operand, therefore the addressing can only
    be the first 256 bytes of memory ($0000 - $00FF). Meaning the significant byte is always zero and only one read occurs to
    the low void. 
*/ 
void CPU::ZPO_Addr(){
    Rock lowByte = read(ProgramCounter);
    ProgramCounter++;
    Rock highByte = 0x00;
    targetAddress = lowByte | (highByte << 8);
    pPBC = 0; 
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
    pPBC = 0; 
}
/*
    Zero Page + Y Register Addressing Mode: Essentially the same thing as Zero Page addressing except we add the contents of the
    Y register to the low-byte 
*/
void CPU::ZPY_Addr(){
    Rock lowByte = (read(ProgramCounter) + Y); 
    ProgramCounter++;
    Rock highByte = 0x00;
    targetAddress = lowByte | (highByte << 8);
    pPBC = 0; 
}
/*
    Relative Adressing Mode: This addressing mode is exclusive to the branching instructions. Since the 6502 has a range of -128
    to 127 from original address, you can't branch to all addresses. To get around this the CPU uses a relative displacement to 
    allow for branching outside the range. 

*/

void CPU::REL_Addr(){
    relativeDisplacement = read(ProgramCounter);
    ProgramCounter++;
    if(relativeDisplacement & 0x80){
        relativeDisplacement |=0xFF00; 
    }
    pPBC = 0; 

}




// ---------INSTRUCTION SET-----------

/*
    Add With Carry instruction: This instruction adds the contents of a memory location to the accumulator together with the carry bit. 
    If overflow occurs the carry bit is set, this enables multiple byte addition to be performed. Set carry bit if overflow occurs, set
    Zero flag if A = 0 (the sum is 0), set negative flag if bit 7 is set, overflow is set if signed operation returns a different sign 
    then expected. Ex. Pos + Pos = Neg or Neg + Neg = Pos. Possible page boundary can be crossed. 

*/
void CPU::ADC(){
    fetchedData = fetch();
    Rock sum = static_cast<Rock>(Accum) + static_cast<Rock> (fetchedData) + static_cast<Rock>(BIT_GRAB(StatusRegister, C));
    BIT_SET(StatusRegister, C , sum > 0xFF);
    BIT_SET(StatusRegister, Z , (sum & 0xFF) == 0x00);
    bool overflowCheck = (~(static_cast<Rock>(Accum) ^ static_cast<Rock>(fetchedData)) & (static_cast<Rock>(Accum) ^ static_cast<Rock>(sum))) & 0x0080;
    BIT_SET(StatusRegister, OV , overflowCheck);
    BIT_SET(StatusRegister, N , sum & 0x0080);
    Accum = sum & 0x00FF; 
    pPBC = 1;  
}

/* 
    AND instruction: This is the Bitwise logic AND, used on the Accumulator with the contents of a byte of memory and set 
    Flags: Z, N
*/ 
void CPU::AND(){
    fetchedData = fetch();

    Accum = Accum & fetchedData;
    BIT_SET(StatusRegister,Z,(Accum == 0x00));
    BIT_SET(StatusRegister,N,(Accum & 0x80));
    pPBC = 1; 
}

/*
    Arithmetic Shift Left instruction: This operation shifts all the bits of the accumulator or memory contents one bit left. 
    Bit 0 is set to 0 and bit 7 is placed in the carry flag. The effect of this operation is to multiply the memory contents 
    by 2 (ignoring 2's complement considerations), setting the carry if the result will not fit in 8 bits. If the addressing 
    mode is Implied then the accumulator is directly updated, if not the result is written back to memory shifted left. 
*/
void CPU::ASL(){
    fetchedData = fetch(); 
    Rock shiftedLeft = static_cast<Rock>(fetchedData) << 1; 
    BIT_SET(StatusRegister, C , (shiftedLeft & 0xFF00) > 0);
    BIT_SET(StatusRegister, Z , (shiftedLeft & 0x00FF) == 0x00);
    BIT_SET(StatusRegister, N , shiftedLeft & 0x80);

    if(lookup[opcode].addr_mode == CPU::IMP_Addr){
        Accum = shiftedLeft & 0x00FF; 
    }
    else{
        write(targetAddress, shiftedLeft & 0x00FF);
    }
    pPBC = 0; 

}

/*
    Branch if Carry Clear: If the carry flag is clear then add the relative displacement to the program counter to cause a 
    branch to a new location. No flags are changed. Increment cycles if branch succeeds. If page boundary is crossed cycles 
    is incremented again. 
*/
void CPU::BCC(){
    bool carryCheck = BIT_GRAB(StatusRegister, C);
    if(carryCheck == 0){
        targetAddress = ProgramCounter + relativeDisplacement; 
        cycles++;

        if((targetAddress & 0xFF00) != (ProgramCounter & 0xFF00)){   // Check if high byte changes
            cycles++;
        }
        ProgramCounter = targetAddress; 

    }
    pPBC = 0; 

}
/*
    Branch if Carry Set: If the carry flag is set then add the relative displacement to the program counter to cause a branch 
    to a new location. No flags are changed. Increment cycles if branch succeeds. If page boundary is crossed cycles will need
    to be incremented again. 
*/
void CPU::BCS(){
    bool carryCheck = BIT_GRAB(StatusRegister, C);
    if(carryCheck != 0){
        targetAddress = ProgramCounter + relativeDisplacement; 
        cycles++; 

        if((targetAddress & 0xFF00) != (ProgramCounter & 0xFF00)){   // Check if high byte changes
            cycles++;
        }
        ProgramCounter = targetAddress; 

    }
    pPBC = 0; 


}
/*
    Branch if Equal instruction: If the zero flag is set then add the relative displacement to the program counter to cause a branch
    to a new location. No flags are changed. Increment cyckes if branch succeeds. If page boundary is crossed cycles is incremented 
    an additional time. 
*/

void CPU::BEQ(){
    bool zeroCheck = BIT_GRAB(StatusRegister, Z);
    if(zeroCheck){
        targetAddress = ProgramCounter + relativeDisplacement; 
        cycles++; 
        if((targetAddress & 0xFF00) != (ProgramCounter & 0xFF00)){  // Check if high byte changes
            cycles++; 
        }
        ProgramCounter = targetAddress; 

    }
    pPBC = 0; 

}
/*
    BIT instruction: the instruction is used to test if one or more bits are set in a target memory location. Accumulator is ANDed 
    with the value in memory to set or clear the Zero flag, result is not kept. Bits 7 and 6 of the value from memory are copied 
    into the N and OV flags.
*/
void CPU::BIT(){
    fetchedData = fetch();
    Byte throwAway = Accum & fetchedData; 
    BIT_SET(StatusRegister,Z, (throwAway == 0x00));
    BIT_SET(StatusRegister, N, (fetchedData & (1 << 7)));
    BIT_SET(StatusRegister,OV,(fetchedData & (1 << 6)));

    pPBC = 0; 
} 
/*
    Branch If Minus instruction: if the negative flag is set then add the relative displacemenet to the program counter to cause a branch to
    the new location. This instruction increments cycles if branch succeeeds and an additional cycle if page boundary is passed. 
*/  
void CPU::BMI(){
    bool nFlagCheck = BIT_GRAB(StatusRegister, N);
    if(nFlagCheck){
        Rock newPC = ProgramCounter + relativeDisplacement; 
        targetAddress = newPC;
        cycles++;
        
        if((targetAddress & 0xFF00) != (ProgramCounter & 0xFF00)){  // Check if high byte changes
            cycles++; 
        }
        ProgramCounter = targetAddress; 
    }
    pPBC = 0; 
}
/*
    Branch If Not Equal instruction: if the Zero flag is clear then add the relative displacement to program counter to cause a branch to a new 
    location. This instruction will increment by one cycles and an additional cycle if page boundary is passed. 
*/
void CPU::BNE(){
    bool nFlagCheck = BIT_GRAB(StatusRegister,N);
    if(nFlagCheck){
        Rock newPC = ProgramCounter + relativeDisplacement;
        targetAddress = newPC;
        cycles++; 
        
        if((targetAddress & 0xFF00) != (ProgramCounter & 0xFF00)){    // Check if high byte changes
            cycles++; 
        }
        ProgramCounter = targetAddress; 
    }
    pPBC = 0; 
}
/*
    Branch If Positive instruction: if the Zero flag is clear then add the relative displacement to the program location to branch to a new
    location. Add a cycle if branch succeeds and increment cycles if a page boundary is crossed.  
*/
void CPU::BPL(){
    bool nFlagCheck = BIT_GRAB(StatusRegister,N);
    if(!nFlagCheck){
        Rock newPC = ProgramCounter + relativeDisplacement; 
        targetAddress = newPC;
        cycles++; 
        
        if((targetAddress & 0xFF00) != (ProgramCounter & 0xFF00)){  // Check if high byte changes
            cycles++; 
        }
        ProgramCounter = targetAddress; 
    }
    pPBC = 0; 
}

/*
    Break instruction: This is similiar to the IRQ but for software not the hardware, it forces the generation of an interrupt request.The program 
    counter and status register are pushed on the stack then IRQ interrupt vector is at $FFFE/F is loaded into the PC and the break
    flag in the status is set to one and ID flag is set to 0; 
    Note: Program counter is incremented by 2 so it points to the second byte after the opcode
*/
void CPU::BRK(){
    ProgramCounter ++;

    BIT_SET(StatusRegister,ID,1);
    push((ProgramCounter >> 8) & 0x00FF);
    push((ProgramCounter & 0x00FF));
    
    BIT_SET(StatusRegister,B,1);
    push(StatusRegister);

    BIT_SET(StatusRegister,B,0);
    ProgramCounter = static_cast<Rock>((read(0xFFFE) | read(0xFFFF)));
    pPBC = 0; 

}
/*
    Branch if Overflow Clear instruction: If the overflow flag is clear then add the relative displacement to the program counter to cause a branch to
    a new location. If branch is successful cycles is incremented and increment again if page boundary is crossed.

*/
void CPU::BVC(){
    bool overflowFlag = BIT_GRAB(StatusRegister,OV);
    if(!overflowFlag){
        Rock newPC = ProgramCounter + relativeDisplacement;
        targetAddress = newPC; 
        cycles++;

        if((targetAddress &= 0xFF00) != (ProgramCounter &= 0xFF00)){ // Check if high byte changes
            cycles++; 
        }
        ProgramCounter = targetAddress;
        
    }
    pPBC = 0; 

}
/*
    Branch If Overflow Set instruction: if the Overflow flag is set then add the relative displacement to the program counter and branch to new
    location. If branch succeeds cycles is incremeneted and check if page boundary is crossed then increment cycles.
*/
void CPU::BVS(){
    bool overflowFlag = BIT_GRAB(StatusRegister,OV);
    if(overflowFlag){
        Rock newPC = ProgramCounter + relativeDisplacement; 
        targetAddress = newPC;
        cycles++; 
        
        if((targetAddress &= 0xFF00) != (ProgramCounter &= 0xFF00)){  // Check if high byte changes
            cycles++; 
        }
        ProgramCounter = targetAddress;
    }
    pPBC = 0; 
}
/*
    Clear Carry Flag: set the carry flag to 0.
*/
void CPU::CLC(){
    BIT_SET(StatusRegister,C, 0);
    pPBC = 0; 
}
/*
    Clear Decimal flag instruction: set decimal flag to 0; 
*/
void CPU::CLD(){
    BIT_SET(StatusRegister,D,0);
    pPBC = 0; 
}
/*
    Clear Interrupt Disable flag instruction : set interrupt disable to 0; 
*/
void CPU::CLI(){
    BIT_SET(StatusRegister,ID,0);
    pPBC = 0; 
}
/*
    Clear Overflow flag instruction: set overflow flag to 0; 
*/
void CPU::CLV(){
    BIT_SET(StatusRegister,OV, 0);
    pPBC = 0; 
}
/*
    Compare instruction: this compares the contents of the accumulator with another memory held vale and set the zero and carry flags.
    set carry if A >= M, set Zero flag if A = M, set Negative flag if bit 7 of the result is set. 
*/
void CPU::CMP(){
    fetchedData = fetch(); 
    Rock compare = static_cast<Rock>(Accum - fetchedData);
    BIT_SET(StatusRegister, C , (Accum >= fetchedData));
    BIT_SET(StatusRegister, Z , (compare &= 0x00FF) == 0x0000);
    BIT_SET(StatusRegister, N , (compare & (1 << 6) != 0));

    pPBC = 1; 

}
/*
    Compare X Register instruction: this compares contents of X register with another memory held value and sets the zero and carry flags as appropriate.
    set carry if X >= M, set zero if X = M, set N if bit 7 of the result is set. 
*/
void CPU::CPX(){
    fetchedData = fetch(); 
    Rock compare = static_cast<Rock>(X - fetchedData);
    BIT_SET(StatusRegister, C , (X >= fetchedData));
    BIT_SET(StatusRegister, Z ,(compare &= 0x00FF == 0x0000));
    BIT_SET(StatusRegister, N , (compare & (1 << 6) != 0));
    pPBC = 0; 
}
/*
    Compare Y Register instruction: this compares contents of Y register with another memory held value and sets the zero and carry flags as appropriate.
    set carry if X >= M, set zero if X = M, set N if bit 7 of the result is set. 
*/
void CPU::CPY(){
    fetchedData = fetch(); 
    Rock compare = static_cast<Rock>(Y - fetchedData);
    BIT_SET(StatusRegister, C , (Y >= fetchedData));
    BIT_SET(StatusRegister, Z , (compare &= 0x00FF == 0x0000));
    BIT_SET(StatusRegister, N , (compare & (1 << 6) != 0));
    pPBC = 0; 
    
}
/*
    Decrement Memory instruction: this subtracts 1 from the value at the specified memory address setting the zero and negative flags. The zero flag is 
    set if the result is zero, and the negative flag is set if the 7th bit is set. 
*/
void CPU::DEC(){
    fetchedData = fetch();
    Byte decremented = fetchedData - 1;
    write(targetAddress,decremented);
    BIT_SET(StatusRegister, Z , (decremented == 0x00));
    BIT_SET(StatusRegister, N , (decremented & (1 << 6) != 0));
    pPBC = 0; 

}

/*
    Decrement X Register instruction: subtracts one from the X register setting the zero and negative flags if X is zero and if the 7th bit is set
    respectively. 
*/
void CPU::DEX(){
    X--;
    BIT_SET(StatusRegister, Z , (X == 0x00));
    BIT_SET(StatusRegister, N, (X & (1 << 6) != 0));
    pPBC = 0; 
}

/*
    Decrement Y Register instruction: subtracts one from the Y register setting the zero and negative flags if X is zero and if the 7th bit is set
    respectively. 
*/
void CPU::DEY(){
    Y--;
    BIT_SET(StatusRegister, Z , (Y == 0x00));
    BIT_SET(StatusRegister, N , (Y & (1 << 6) != 0));
    pPBC = 0; 
}
/*
    Exclusive OR function instruction: an XOR is performed bit by bit on the accumulator contents using the contents of a byte of memory. Setting the
    zero flag if A = 0, setting negative flag if the 7th bit is set; possibility of a possible page boundary being crossed. 
*/

void CPU::EOR(){
    fetchedData = fetch();
    Accum = Accum ^ fetchedData; 
    BIT_SET(StatusRegister, Z , (Accum == 0x00));
    BIT_SET(StatusRegister, N , ( Accum & (1 << 6) != 0));
    pPBC = 1; 
}
/*
    Increment Memory instruction: adds one to the value held at a specified memory location setting the zero and negative flags appropriately. Zero flag
    set if the result is 0, set negative flag if bit 7 of the result is set. 
*/

void CPU::INC(){
    fetchedData = fetch(); 
    Byte incremented = fetchedData + 1;
    write(targetAddress, incremented);
    BIT_SET(StatusRegister, Z , (incremented == 0x00));
    BIT_SET(StatusRegister, N , (incremented &(1 << 6) != 0));
    pPBC = 0; 

}
/*
    Increment X instruction: adds one to the value X register setting the zero and negative flags appropriately. Zero flag
    set if X = 0, set negative flag if bit 7 of the X is set. 
*/
void CPU::INX(){
    X++;
    BIT_SET(StatusRegister, Z , (X == 0x00));
    BIT_SET(StatusRegister, N , (X & (1 << 6) != 0));
    pPBC = 0; 
}
/*
    Increment Y instruction: adds one to the value Y register setting the zero and negative flags appropriately. Zero flag
    set if Y = 0, set negative flag if bit 7 of the Y is set. 
*/
void CPU::INY(){
    Y++;
    BIT_SET(StatusRegister, Z , (Y == 0x00));
    BIT_SET(StatusRegister, N , (Y & (1 << 6) != 0));
    pPBC = 0; 
}
/*
    Jump Instruction: sets the program counter to the address specified by the operand.

*/
void CPU::JMP(){
    ProgramCounter = targetAddress; 
    pPBC = 0 ; 
}
/*
    Jump To Subroutine instruction: pushes the address(minus one) of the return point on to the stack and then sets the program
    counter to the target memory address
*/
void CPU::JSR(){
    ProgramCounter--;
    push((ProgramCounter >> 8) & 0x00FF);
    push((ProgramCounter) & 0x00FF);

    ProgramCounter = targetAddress; 
    pPBC = 0; 
}
/*
    Load Accumulator instruction: Loads a byte of memory into the accumulator setting the zero and negative flags as appropriate. 
    Set zero flag if A = 0, set negative Flag if bit 7 of A is set. Potential page boundary crossed. 
*/
void CPU::LDA(){
    Accum = fetch();
    BIT_SET(StatusRegister, Z , (Accum == 0x00));
    BIT_SET(StatusRegister, N , (Accum & (1 << 6) != 0));
    pPBC = 1; 
}
/*
    Load X Register instruction: Loads a byte of memory into the X register setting the zero and negative flags as appropriate. 
    Set zero flag if X = 0, set negative Flag if bit 7 of X is set. Potential page boundary crossed. 
*/
void CPU::LDX(){
    X = fetch(); 
    BIT_SET(StatusRegister, Z ,(X == 0));
    BIT_SET(StatusRegister, N, (X & (1 << 6) != 0 ));
    pPBC = 1; 
}
/*
    Load Y Register instruction: Loads a byte of memory into the Y register setting the zero and negative flags as appropriate. 
    Set zero flag if Y = 0, set negative Flag if bit 7 of Y is set. Potential page boundary crossed. 
*/
void CPU::LDY(){
    Y = fetch();
    BIT_SET(StatusRegister, Z, (Y == 0));
    BIT_SET(StatusRegister, N , (Y & (1 << 6) != 0));
    pPBC = 1; 
}
/* 
    Logical Shift Right instruction: Each of the bits in Accumulator or said memory byte is shifted one the right. The bit in the
    bit 0 position is shifted into the carry flag. Bit 7 is set to zero. C flag set to contents of old bit 0, set Z if result = 0,
    set N if bit 7 of the result is set. If the addressing mode is implied then Accumulator is shifted otherwise memory byte is 
    shifted. 
*/

void CPU::LSR(){
    fetchedData = fetch();
    BIT_SET(StatusRegister, C , fetchedData & 0x0001);   // Set contents of the carry flag to the last
    Rock shiftedRight = static_cast<Rock>(fetchedData) >> 1;
    BIT_SET(StatusRegister, Z , (shiftedRight & 0x00FF) == 0x0000);
    BIT_SET(StatusRegister, N , shiftedRight & 0x0080);
    if(lookup[opcode].addr_mode == CPU::IMP_Addr){
        Accum = shiftedRight & 0x00FF; 
    }
    else{
        write(targetAddress, shiftedRight & 0x00FF);
    }
    pPBC = 0; 
}

/*
    No Operation instruction: causes no changes to to the processor, there are certain illegal NOP isntructions that could potentially
    cross a page boundary and those cases will be implemented, these are in the opcode table linked below: 
    http://www.oxyron.de/html/opcodes02.html
*/
void CPU::NOP(){
    switch (opcode)
    {
    case 0x1C:
    case 0x3C:
    case 0x5C:
    case 0x7C:
    case 0xDC:
    case 0xFC:
        pPBC = 1; 
        break;

    }
    pPBC = 0; 

}

/*
    Logical Inclusive OR instruction: an inclusive OR is performed bit by bit on the accumulator using the contents of a byte of memory
    the zero flag is set if A = 0, N flag set if bit 7 is set. Possibility of page boundary crossed. 

*/
void CPU::ORA(){
    fetchedData = fetch();
    Accum = Accum | fetchedData;
    BIT_SET(StatusRegister, Z , (Accum == 0x00));
    BIT_SET(StatusRegister, N , (Accum & (1 << 6) != 0));

    pPBC = 1; 

}

/*
    Push Accumulator instruction: Push the contents of the Accumulator to the stack. No flags changed. 
*/
void CPU::PHA(){
    push(Accum);
    pPBC = 0; 
}
/*  
    Pushes a copy of the status flags onto the stack. Set the break to 1 before pushing and Unused flag to ensure state is known.
    Then unset. 
*/
void CPU::PHP(){
    BIT_SET(StatusRegister, B , 1);
    BIT_SET(StatusRegister, U , 1);
    push(StatusRegister);
    BIT_SET(StatusRegister, B , 0);
    BIT_SET(StatusRegister, U, 0 );
    pPBC = 0; 

}
/*
    Pop Accumulator instruction: Pops contents for the accumulator off of the stack. The zero and negative flags are set as appropriate,
    if the Accumulator = 0 zero flag is set and if bit 7 is set of Accumulator set the negative bit. 
*/
void CPU::PLA(){
    Accum = pop();
    BIT_SET(StatusRegister, Z , Accum == 0x00);
    BIT_SET(StatusRegister, N , Accum & 0x80);
    pPBC = 0; 

}

/*
    Pull Processor Status instruction: Pops contents of stack to the Status Register. The flags will take on the new states as determined
    by the value popped. 
*/
void CPU::PLP(){
    StatusRegister = pop();
    BIT_SET(StatusRegister, U, 1);
    pPBC = 0; 

}
/*
    Rotate Left instruction: Move each of the bits in either A or M one place to the left. Bit 0 is filled with the current value of the 
    carry flag while the old bit 7 becomes the new carry flag value. Set negative flag if bit 7 of the result is set, set the zero flag if
    the result is 0. If the addressing mode is IMP then the rotate is performed on the Accumulator, otherwise perform on memory data and 
    write back to memory. 

*/
void CPU::ROL(){
    fetchedData = fetch();
    Rock rotatedData = static_cast<Rock>(fetchedData << 1) | BIT_GRAB(StatusRegister, C);
    BIT_SET(StatusRegister, C , rotatedData & 0x0100); 
    BIT_SET(StatusRegister, N , rotatedData & 0x80);
    BIT_SET(StatusRegister, Z , rotatedData & 0x00FF == 0x0000);
    if(lookup[opcode].addr_mode == &CPU::IMP_Addr){
        Accum = rotatedData & 0x00FF; 
    }
    else{
        write(targetAddress, rotatedData & 0x00FF);
    }
    pPBC = 0; 
}
/*
    Rotate Right instruction: Move each of the bits in either A or M one place to the right. Bit 7 is filled with the current value of the 
    carry flag whilst the old bit 0 becomes the new carry flag value.  Set negative flag if bit 7 of the result is set, set the zero flag 
    if the result is 0. If the addressing mode is IMP then the rotate is performed on the Accumulator, otherwise perform on memory data and 
    write back to memory. 
*/
void CPU::ROR(){
    fetchedData = fetch(); 
    Rock rotatedData = static_cast<Rock>(fetchedData >> 1) | (BIT_GRAB(StatusRegister, C) << 6);
    BIT_SET(StatusRegister, C , fetchedData & 0x01);
    BIT_SET(StatusRegister, N , rotatedData & 0x80);
    BIT_SET(StatusRegister, Z , rotatedData & 0x00FF == 0x0000);
    if(lookup[opcode].addr_mode == &CPU::IMP_Addr){
        Accum = rotatedData & 0x00FF;
    }
    else{
        write(targetAddress, rotatedData & 0x00FF);
    }

    pPBC = 0; 
    
}

/*
    Return From Interrupt instruction: Used at the end of an interrupt processing routine. It pops the processor flags from the stack and 
    then pops the program counter from the stack. 
*/
void CPU::RTI(){
    StatusRegister = pop();
    // Not necessary since interrupts set to flags 0 but just to be sure setting B to 0 and U to 0 for clear state. 
    BIT_SET(StatusRegister, U , 0);
    BIT_SET(StatusRegister, B , 0); 
    Byte lowByte = pop(); 
    Byte highByte = pop(); 
    ProgramCounter = (highByte << 8) | (lowByte);
    pPBC = 0; 
    
}
/*
    Return from from subroutine: Used at the end of a subroutine to return to the calling routine. It pops the program 
    counter from the stack. 
*/
void CPU::RTS(){
    Byte lowByte = pop();
    Byte highByte = pop(); 
    ProgramCounter = (highByte << 8) | lowByte;
    pPBC = 0; 

}
/*
    Subtract with Carry instruction: Subtracts the contents of a memory location to the accumulator together with the 
    not of the carry bit. If overflow occurs the carry bit is clear. Going to handle this differently then the ADC 
    instruction using the signed complement and inverting the bits of the memory contents and adding one to make a 
    positive signed number negative,Ex: 

    7 = 000000111 ==> 7 ^ 0x00FF = 
*/

void CPU::SBC(){
    fetchedData = fetch();
    Rock cFlagValue = BIT_GRAB(StatusRegister, C);
    Rock inverted = (static_cast<Rock>(fetchedData)) ^ 0x00FF; 
    Rock subtracted = static_cast<Rock>(Accum) + inverted + cFlagValue;
    BIT_SET(StatusRegister, C , subtracted & 0xFF00);
    BIT_SET(StatusRegister, Z , ((subtracted & 0x00FF) == 0));
    bool overflowCheck = (subtracted ^(static_cast<Rock>(Accum))) ^ (subtracted ^ inverted) & 0x0080; 
    BIT_SET(StatusRegister, OV , overflowCheck);
    BIT_SET(StatusRegister, N , subtracted & 0x0080);
    pPBC = 1; 

}
/*
    Set Carry Flag instruction: set the carry flag 
*/
void CPU::SEC(){
    BIT_SET(StatusRegister, C , 1);
    pPBC = 0; 
}
/*
    Set Decimal Flag instruction: set the decimal flag 
*/
void CPU::SED(){
    BIT_SET(StatusRegister, D , 1);
    pPBC = 0; 
}
/*
    Set Interrupt Disable Flag instruction: set the interrupt disable flag
*/
void CPU::SEI(){
    BIT_SET(StatusRegister, ID , 1);
    pPBC = 0; 
}
/*
    Store The Accumulator instruction: stores the contents of the accumulator in memory. 
*/
void CPU::STA(){
    write(targetAddress, Accum);
    pPBC = 0; 
}
/*
    Store The X register instruction: stores the contents of the X register in memory
*/
void CPU::STX(){
    write(targetAddress, X);
    pPBC = 0; 

}
/*
    Store The Y register instruction: stores the contents of the Y register in memory
*/
void CPU::STY(){
    write(targetAddress, Y);
    pPBC = 0; 
}
/*
    Transfer the Accumulator to X instruction: Copies the current contents of the accumulator into 
    the X register and sets the zero and negative flags as appropriate. Set Z if X = 0 and set N 
    if bit 7 of the X register is set. 
*/
void CPU::TAX(){
    X = Accum;
    BIT_SET(StatusRegister, Z , (X = 0x00));
    BIT_SET(StatusRegister, N , (X & (1 << 6) != 0));
    pPBC = 0; 
}
/*
    Transfer the Accumulator to Y instruction: Copies the current contents of the accumulator into 
    the Y register and sets the zero and negative flags as appropriate. Set Z if Y = 0 and set N 
    if bit 7 of the Y register is set. 
*/
void CPU::TAY(){
    Y = Accum; 
    BIT_SET(StatusRegister, Z , (Y == 0x00));
    BIT_SET(StatusRegister, Y , (Y & (1 << 6) != 0));
    pPBC = 0; 
}

/*
    Transfer the Accumulator to Stack pointer: Copies the current contents of the accumulator into 
    the Stack pointer and sets the zero and negative flags as appropriate. Set Z if Stack pointer = 0 and set N 
    if bit 7 of the Stack pointer is set. 
*/
void CPU::TXS(){
    StackPointer = Accum;
    BIT_SET(StatusRegister, Z , (StackPointer == 0x00));
    BIT_SET(StatusRegister, N , (StackPointer & (1 << 6) != 0));
    pPBC = 0; 

}
/*
    Transfer the X register into the Accumulator instruction: Copies the current contents of the X register into 
    the accumulator and sets the zero and negative flags as appropriate. Set Z if Y = 0 and set N 
    if bit 7 of the accumulator is set. 
*/
void CPU::TXA(){
    Accum = X;
    BIT_SET(StatusRegister, Z , (Accum == 0x00));
    BIT_SET(StatusRegister, N , (Accum & (1 << 6) != 0 ));
    pPBC = 0; 
}
/*
    Transfer the X Register to Stack Pointer instruction: Copies the current contents of the X register into 
    the StackPointer.
*/
void CPU::TXS(){
    StackPointer = X;
    pPBC = 0; 
}
/*
    Transfer the Y Register to the Accumulator  instruction: Copies the current contents of the Y register into 
    the accumulator and sets the zero and negative flags as appropriate. Set Z if accumulator = 0 and set N 
    if bit 7 of the accumulator. 
*/
void CPU::TYA(){
    Accum = Y;
    BIT_SET(StatusRegister, Z , (Accum == 0x00));
    BIT_SET(StatusRegister, N , (Accum & (1 << 6) != 0 ));
    pPBC = 0; 

}

void CPU::IOC(){
    pPBC = 0; 
}