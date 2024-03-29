#pragma once 


#define BIT_GRAB(SR,f)(((SR & f) > 0) ? 1 : 0)
#define BIT_SET(SR,f,bl) if(bl){ (SR) |= (f); } else { (SR) &= (~f); };
class Bus;

class CPU
{
public:
    // --------------FLAGS--------------
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
    
    Bus *bus;                      // Pointer to the bus which connects the bus to the cpu and allows for read and write
    Byte Accum,X,Y = 0x00;         // Acumulator, X and Y Registers
    Byte StackPointer= 0x00;       // Stack Pointer
    Rock ProgramCounter = 0x0000;  // Program Counter
    Byte StatusRegister = 0x00;    // Status Register 
    
    
    
    void busConnection(Bus *b);  // Connecting CPU to the bus
    void Reset();                // Reset request function
    void NonMaskableInterrupt(); // NMI function 
    void InterruptRequest();     // IRQ function
    
    
    Byte fetch();                       // Fetch is used for instructions 
    void execute();                     // function that executes the instructions
 

    Byte read(Rock Addr);               // CPU read function 
    void write(Rock addr, Byte data);   // CPU write function
    Byte pop();                         // CPU pops to stack
    void push(Byte data);               // CPU pushes to stack 


    // --------------Instruction Set--------------
    struct Instruction_Set{
        void  (CPU::*instruction)(void) = nullptr;  // function pointer to the first opcode to used for instruction 
        void  (CPU::*addr_mode)(void) = nullptr;    // function pointer to the addressing mode used for instruction 
        Byte  cycles = 0x00;                        // number of cycles the instruction will take 

    };
    std::vector<Instruction_Set> lookup;          // Lookup Table
    



private:
    Byte cycles = 0x00;                   // Variable to track cycles 
    Byte ticks = 0x00;                    // Tick to measure clock 
    Byte fetchedData = 0x00;              // Holds the data for ALU input value
    Byte opcode = 0x00;                   // Instruction byte
    Rock targetAddress = 0x0000;          // Holds the current target address  
    Rock relativeDisplacement = 0x0000;   // Relative displacement used to add to the program counter when branching occurs 
    bool pPBC = 0;                        // Possible page boundary crossed, will be set to 1 if its possible and 0 if not 


     



private: 
    // --------------Adressing modes--------------
    void  IMP_Addr();  void  IMM_Addr();  void  ABS_Addr(); 
    void  ABX_Addr();  void  ABY_Addr();  void  IND_Addr(); 
    void  IZX_Addr();  void  IZY_Addr();  void  ZPO_Addr(); 
    void  ZPX_Addr();  void  ZPY_Addr();  void  REL_Addr();
     



private: 
    // --------------Opcodes--------------
    void  ADC(); void  AND(); void  ASL(); void  BCC(); void  BCS(); void  BEQ(); void  BIT(); void  BMI(); 
    void  BNE(); void  BPL(); void  BRK(); void  BVC(); void  BVS(); void  CLC(); void  CLD(); void  CLI(); 
    void  CLV(); void  CMP(); void  CPX(); void  CPY(); void  DEC(); void  DEX(); void  DEY(); void  EOR(); 
    void  INC(); void  INX(); void  INY(); void  JMP(); void  JSR(); void  LDA(); void  LDX(); void  LDY(); 
    void  LSR(); void  NOP(); void  ORA(); void  PHA(); void  PHP(); void  PLA(); void  PLP(); void  ROL(); 
    void  ROR(); void  RTI(); void  RTS(); void  SBC(); void  SEC(); void  SED(); void  SEI(); void  STA(); 
    void  STX(); void  STY(); void  TAX(); void  TAY(); void  TSX(); void  TXA(); void  TXS(); void  TYA(); 
    

    // function to encompass most of the Ilegal opcodes except the NOP ones.
    void  IOC(); 

}; 

