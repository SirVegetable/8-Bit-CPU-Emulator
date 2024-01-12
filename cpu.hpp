#ifndef CPU_HPP
#define CPU_HPP
#include <iostream> 
#include <array> 
#include "typedefs.h"
#include "Memory.hpp"


#define BIT_GRAB(SR,f)(((SR & f) > 0) ? 1 : 0);
#define BIT_SET(SR,f,bl) if(bl){ (SR) |= (f); } else { (SR) &= (~f); };
class Bus;

class CPU
{
public:
    // the flags that make up the 8 bits, shift the 1 to the left 
    enum FLAGS{
        C = 1 << 0,  // Carry
        Z = 1 << 1,  // Zero
        ID = 1 << 2, // Interrupt Disable
        D = 1 << 3,  // Decimal Mode
        B = 1 << 4,  // Break
        U = 1 << 5,  // Unused
        OV = 1 << 6, // Overflow
        N = 1 << 7   // Negative
    };
    //Bus member value which connects the bus to the cpu and allows for read and write
    Bus *bus; 

    //Acumulator, X and Y Registers
    Byte Accum,X,Y = 0x00;
    //Stack Pointer
    Byte StackPointer= 0x00; 
    //Program Counter
    Rock ProgramCounter= 0x0000;
    //Status Register for the flags
    Byte StatusRegister = 0x00; 

    // Connecting CPU to the bus
    void busConnection(Bus *b);
    
    //functions that handle 6502 interrupts
    void Reset();
    void NonMaskableInterrupt();
    void InterruptRequest(); 
    
    // Fetch is used for instructions 
    Byte Fetch();
    
    //function that executes the instructions
    void Execute();
 


    /* 
        The instruction set for our lookup table will be two function pointers: The first one is the opcode function to be executed
        and the second function pointer will be to the address mode that is used for the instruction. Lastly this struct will hold
        the number of cycles that is needed to execute the instructions
    */
    struct Instruction_Set{
        Byte (CPU::*op_code)(void) = nullptr; 
        Byte (CPU::*addr_mode)(void) = nullptr; 
        Byte cycles = 0x00;

    };
    // Lookup Table: 
    std::vector<Instruction_Set> lookup; 
    



private:
    // Variables to hold timing information
    Byte cycles = 0x00;
    Byte ticks = 0x00;
    // Variable to hold fetched information
    Byte fetchedData = 0x00;
    Rock currentAddress = 0x0000;
    
    //The 6502 branching instructions have a specified range(explaination in the Relative Addressing mode)
    Rock relativeAddress = 0x0000; 
    // Variable to check if the instruction crosses a page boundary
    Byte pageBoundary = 0x00;


     



private: 
    //Adressing modes, the 6502 has many different ways in which memory is addressed
    Byte IMP_Addr(); Byte IMM_Addr();   Byte ZP_Addr(); 
    Byte ZPX_Addr(); Byte ZPY_Addr();   Byte REL_Addr();
    Byte ABS_Addr(); Byte ABSX_Addr();  Byte ABSY_Addr(); 
    Byte IND_Addr(); Byte IZPX_Addr();  Byte IZPY_Addr();



private: 
    // Opcodes - 56 total instructions 
    Byte ADC(); Byte AND(); Byte ASL(); Byte BCC(); Byte BCS(); Byte BEQ(); Byte BIT(); Byte BMI(); 
    Byte BNE(); Byte BPL(); Byte BRK(); Byte BVC(); Byte BVS(); Byte CLC(); Byte CLD(); Byte CLI(); 
    Byte CLV(); Byte CMP(); Byte CPX(); Byte CPY(); Byte DEC(); Byte DEX(); Byte DEY(); Byte EOR(); 
    Byte INC(); Byte INX(); Byte INY(); Byte JMP(); Byte JSR(); Byte LDA(); Byte LDX(); Byte LDY(); 
    Byte LSR(); Byte NOP(); Byte ORA(); Byte PHA(); Byte PHP(); Byte PLA(); Byte PLP(); Byte ROL(); 
    Byte ROR(); Byte RTI(); Byte RTS(); Byte SBC(); Byte SEC(); Byte SED(); Byte SEI(); Byte STA(); 
    Byte STX(); Byte STY(); Byte TAX(); Byte TAY(); Byte TSX(); Byte TXA(); Byte TXS(); Byte TYA(); 
    
    Byte Illegal_opcode(); 

}; 

#endif 