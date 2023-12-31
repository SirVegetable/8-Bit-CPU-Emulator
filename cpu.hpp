#ifndef CPU_HPP
#define CPU_HPP
#include <iostream> 
#include <array> 
#include "typedefs.h"
#include "Memory.hpp"


class CPU
{
public:
    // the flags that make up the 8 bits, shift the 1 to the left 
    enum FLAGS{
        C = 1 << 0,  // Carry
        Z = 1 << 1,  // Zero
        ID = 1 << 2, // Interrupt Disable
        D = 1 << 3,  //Decimal Mode
        B = 1 << 4,  //Break
        U = 1 << 5,  //Unused
        OV = 1 << 6, //Overflow
        N = 1 << 7   // Negative
    };


    //Acumulator, X and Y Registers
    Byte Accum,X,Y = 0x00;
    //Stack Pointer
    Byte StackPointer= 0x00; 
    //Program Counter
    Rock ProgramCounter= 0x0000;
    //Status Register for the flags
    Byte StatusRegister = 0x00; 

    //function to measure clock cycles of the cpu
    void Clock();
    
    //functions that handle 6502 interrupts
    void Reset();
    void NonMaskableInterrupt();
    void InterruptRequest(); 

    //setter and getter
    void setFlags(); 
    void getFlags();

    //fetch function
    Byte Fetch(); 



private:
    // Variables to hold information
    Byte fetchedData;
    Byte Cycles;
    Rock addr_abs = 0x0000;
    Byte current_opcode; 


private: 
    //Adressing modes, the 6502 has many different ways in which memory is addressed
    Byte IMP_Addr(); Byte IMM_Addr(); Byte ZP_Addr(); 
    Byte ZPX_Addr(); Byte ZPY_Addr(); Byte REL_Addr();
    Byte ABS_Addr(); Byte ABSX_Addr(); Byte ABS_Addr(); 
    Byte IND_Addr(); Byte IZPX_Addr(); Byte IZPY_AddrI();

private: 
    // Opcodes - 56 total instructions 
    Byte ADC(); Byte AND(); Byte ASL(); Byte BCC();
    Byte BCS(); Byte BEQ(); Byte BIT(); Byte BMI(); 
    Byte BNE(); Byte BPL(); Byte BRK(); Byte BVC(); 
    Byte CLC(); Byte CLD(); Byte CLV(); Byte CMP();

}; 

#endif 