#include <iostream>
#include <array>
 
//Definitions for 8 bit type and 16 bit type 
typedef uint8_t Byte; 
typedef uint16_t Rock;

struct Memory{
    static constexpr std::size_t maxMemorySize = 64 * 1024; // 64 kb

    std::array<Byte,maxMemorySize> data; 

    void initializeMem(){
        for(std::size_t i = 0; i < maxMemorySize; i++){
            data[i] = 0; 
        }
    }
    //Read one byte of memory, may get rid of later for a read and write function
    Byte operator [](unsigned int Address) const{
        //must assert the address is less than maxMemorySize
        return data[Address];
    }
};


struct CPU{

    

    Rock ProgramCounter;
    Rock StackPointer;

    //Registers
    Byte Accum;
    Byte X; 
    Byte Y; 

    /*CPU member Processor Status, comprised of the processor flags, either a 1
      Or a 0, depending on if the flag is present or not and each flag being 1 bit
    */
    Byte carry : 1; 
    Byte zero : 1;
    Byte interrDisable : 1; 
    Byte decMode : 1; 
    Byte brCmd : 1; 
    Byte overflow : 1; 
    Byte neg: 1; 
    
    /* Emulates the computer turning off and the CPU having to reset*/
    void Reset(Memory &mem){
        carry = 0, zero = 0, interrDisable = 0, decMode = 0, brCmd = 0, overflow = 0, neg =0;
        ProgramCounter = 0xFFFC;
        StackPointer = 0x0100;

        mem.initializeMem();
    }
    /* The operation which recieves the instructions from Memory*/
    Byte fetch(Memory &mem, unsigned int &Cycles){
        Byte data = mem.data[ProgramCounter]; 
        ProgramCounter++;
        Cycles--; 

        return data; 
    }

    /*This is where the operation is performed, every part of the cpu that is needed activated
    to carry out the instructions*/
    
    
    void execute(Memory &mem, unsigned int cycles){

        while (cycles != 0){
            Byte instructions = fetch(mem, cycles);

        } 
    }

    /* where the instructions are converted to understand which other parts of the CPU are
    needed to continue the operation . Performed by the Instruction decoder*/
    void decode(){

    }
    void writeBack(){

    }
    

};  

int main(){
    Memory mem; 
    CPU cpu;
    cpu.Reset(mem);
    cpu.execute(mem,4);
    

    return 0; 
}