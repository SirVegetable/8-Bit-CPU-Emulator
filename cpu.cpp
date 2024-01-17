#include "cpu.hpp"
#include "typedefs.h"
#include "bus.hpp"

//Constructor
CPU::CPU()
{
    lookup =
    {
            {&CPU::BRK,&CPU::IMP_Addr,7}, {&CPU::ORA, &CPU::IZPX_Addr, 6}
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
    Accum = 0x00; 
    X = 0x00; 
    Y = 0x00;   
    StackPointer   = 0xFF;
    StatusRegister = 0x00 | (1 << 5);
    targetAddress  = 0xFFFC;
    Rock lowByte  = read(targetAddress + 0 );
    Rock highByte   = read(targetAddress + 1);
    ProgramCounter = (highByte << 8) | lowByte;

    relativeDisplacement = 0x0000; 
    targetAddress = 0x0000; 
    fetchedData = 0x00; 
    pPBC = 0; 
    cycles = 8; 
}

/*
    IRQ: the CPU pushes the program counter and status register to the stack, setting the ID flag in order to 
    ignore further IRQ requests and the program counter will read the values at 0xFFFE and 0xFFFF. IRQ takes
    7 cycles. 
*/
void CPU::InterruptRequest(){
    if(BIT_GRAB(StatusRegister,ID) == 0){
        push((ProgramCounter >> 8 ) & 0x00FF);  // Pushing the lowbytes 
        push((ProgramCounter & 0x00FF));        // Pushing the highbytes
        BIT_SET(StatusRegister,B , 0);          // Shows this was a hardware interrupt not a program interrupt
        BIT_SET(StatusRegister,ID , 1);         // Interrupt Disabled
        BIT_SET(StatusRegister,U , 1)           // Unused bit set 
        push(StatusRegister);                   // Push status register

        targetAddress = 0xFFFE; 
        Rock lowByte = read(targetAddress + 0);
        Rock highByte = read(targetAddress + 1);
        ProgramCounter = (highByte << 8) | lowByte; 

    cycles = 7; 

    }

}


/*
    A NMI will behave the same as an IRQ which means it cannot be ignored but reads the new program counter
    from location 0xFFFA. 
*/
void CPU::NonMaskableInterrupt(){
    push((ProgramCounter >> 8) & 0x00FF);

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
void CPU::ABSX_Addr(){
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
void CPU::ABSY_Addr(){
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
void CPU::IZPX_Addr(){
    Rock addressTable = read(ProgramCounter); 
    ProgramCounter++; 

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
    Y register to the low-void; 
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
    pPBC = 1; 
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

    pPBC = 0; 
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
            pPBC = 1; 
        }
        else{
            pPBC = 0; 
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
            pPBC = 1; 
        }
        else{
            pPBC = 0; 
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
            pPBC = 1; 
        }
        else{
            pPBC = 0;
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
    a new location. If branch is successful cycles is incremented and check if page boundary is crossed.

*/
void CPU::BVC(){
    bool overflowFlag = BIT_GRAB(StatusRegister,OV);
    if(!overflowFlag){
        Rock newPC = ProgramCounter + relativeDisplacement;
        targetAddress = newPC; 
        cycles++;

        if((targetAddress &= 0xFF00) != (ProgramCounter &= 0xFF00)){
            pPBC = 1; 
        }
        else{
            pPBC = 0; 
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
            pPBC = 1; 
        }
        else{
            pPBC = 0; 
        }
        ProgramCounter = targetAddress;
    }

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
    bit 0 position is shifted into the carry flag. Bit 7 is set to zero. C flag set to contents of old bit 0, set Z if result = 0, set N if bit
    7 of the result is set. If the addressing mode is implied then Accumulator is shifted otherwise memory byte is shifted. 
*/

void CPU::LSR(){
    
}
void CPU::NOP(){}
/*
    Logical Inclusive OR instruction: an inclusive OR is performed bit by bit on the accumulator using the contents of a byte of memory
    the zero flag is set if A = 0, N flag set if bit 7 is set. Possibility of page boundary crossed. 

*/
void CPU::ORA(){
    fetchedData = fetch();
    Accum = Accum | fetchedData;
    BIT_SET(StatusRegister, Z , (Accum == 0x00));
    BIT_SET(StatusRegister, N , (Accum & (1 << 6) != 0));

    pPBC = 0; 

}
void CPU::PHA(){}
void CPU::PHP(){}
void CPU::PLA(){}
void CPU::PLP(){}
void CPU::ROL(){}
void CPU::ROR(){}
void CPU::RTI(){}
void CPU::RTS(){}
void CPU::SBC(){}
/*
    Set Carry Flag instruction: set the carry flag 
*/
void CPU::SEC(){
    BIT_SET(StatusRegister, C , 1);
    pPBC = 0; 
}
/*
    Set Decimal Flag instruction: set the cdecimal flag 
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

void CPU::Illegal_opcode(){
    pPBC = 0; 
}