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
        void  (CPU::*op_code)(void) = nullptr; 
        void  (CPU::*addr_mode)(void) = nullptr; 
        Byte  cycles = 0x00;

    };
    // Lookup Table: 
    std::vector<Instruction_Set> lookup; 
    



private:
    // Variables to hold timing information
    Byte  cycles = 0x00;
    Byte  ticks = 0x00;
    // Variable to hold fetched information
    Byte fetchedData = 0x00;
    Rock targetAddress = 0x0000;
    
    // The 6502 branching instructions have a specified range(explaination in the Relative addressing mode) and branching instructions 
    // take a relative displacement used to add to the program counter. 
    Rock relativeDisplacement = 0x0000; 
    // Variable to check if the instruction crosses a page boundary
    Byte pBoundaryCrossed = 0x00;


     



private: 
    //Adressing modes, the 6502 has many different ways in which memory is addressed
    void  IMP_Addr();   void  IMM_Addr();   void  ABS_Addr(); 
    void  ABSX_Addr();  void  ABSY_Addr();  void  IND_Addr(); 
    void  IZPX_Addr();  void  IZPY_Addr();  void  ZP_Addr(); 
    void  ZPX_Addr();   void  ZPY_Addr();   void  REL_Addr();
     



private: 
    // Opcodes - 56 total instructions 
    void  ADC(); void  AND(); void  ASL(); void  BCC(); void  BCS(); void  BEQ(); void  BIT(); void  BMI(); 
    void  BNE(); void  BPL(); void  BRK(); void  BVC(); void  BVS(); void  CLC(); void  CLD(); void  CLI(); 
    void  CLV(); void  CMP(); void  CPX(); void  CPY(); void  DEC(); void  DEX(); void  DEY(); void  EOR(); 
    void  INC(); void  INX(); void  INY(); void  JMP(); void  JSR(); void  LDA(); void  LDX(); void  LDY(); 
    void  LSR(); void  NOP(); void  ORA(); void  PHA(); void  PHP(); void  PLA(); void  PLP(); void  ROL(); 
    void  ROR(); void  RTI(); void  RTS(); void  SBC(); void  SEC(); void  SED(); void  SEI(); void  STA(); 
    void  STX(); void  STY(); void  TAX(); void  TAY(); void  TSX(); void  TXA(); void  TXS(); void  TYA(); 
    
    void  Illegal_opcode(); 

}; 

#endif 