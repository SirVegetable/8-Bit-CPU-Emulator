#include <iostream> 
#include <array> 
#include "typedefs.h"


class CPU
{
public:
    enum FLAGS{
        C, // Carry
        Z, // Zero
        ID, // Interrupt Disable
        D, //Decimal Mode
        B, //Break
        U, //Unused
        OV, //Overflow
        N // Negative
    };
    //Acumulator, X and Y Registers
    Byte Accum,X,Y = 0x00;
    //Stack Pointer
    Byte StackPointer= 0x00; 
    //Program Counter
    Rock ProgramCounter= 0x0000; 

    //function to measure clock cycles of the cpu
    void Clock();
    
    //functions that handle 6502 interrupts
    void Reset();
    void NonMaskableInterrupt();
    void InterruptRequest(); 

}