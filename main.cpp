#include <iostream>
#include <array>
 
//Definitions for 8 bit type and 16 bit type 
typedef uint8_t Byte; 
typedef uint16_t Rock;

struct Memory{
    static constexpr std::size_t maxMemorySize = 64 * 1024; // 64Kb

    std::array<Byte,maxMemorySize> data; 

    void initializeMem(){
        for(std::size_t i = 0; i < maxMemorySize; i++){
            data[i] = 0; 
        }
    }
    // //Read one byte of memory, may get rid of later for a read and write function
    // Byte operator [](unsigned int Address) const{
    //     //must assert the address is less than maxMemorySize
    //     return data[Address];
    // }
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
    Byte breakCmd : 1; 
    Byte overflow : 1; 
    Byte neg: 1; 
    
    /* Emulates the computer turning off and the CPU having to reset*/
    void Reset(Memory &mem){
        carry = 0, zero = 0, interrDisable = 0, decMode = 0, breakCmd = 0, overflow = 0, neg =0;
        ProgramCounter = 0xFFFC; // reset location
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
    //function to read a byte through a CPU cycle but doesn't increment PC like fetch
    Byte ReadByte(Memory &mem,unsigned int& Cycles){
        Byte Data = mem.data[ProgramCounter];
        Cycles--; 
        return Data; 
    }
    void LDA_FLAG_SETTR(){
        zero = (Accum == 0);
        //binary literal used to check if accum's 7th bit is set
        neg = (Accum& 0b10000000) > 0; 

    }
    //opcodes
    static constexpr Byte LDA_IM_INS = 0xA89, LDA_ZP_INS = 0xA5; 

    /*This is where the operation is performed, every part of the cpu that is needed activated
    to carry out the instructions*/
    
    
    void execute(Memory &mem, unsigned int Cycles){

        while (Cycles != 0){
            Byte instructions = fetch(mem, Cycles);
            switch (instructions)
            {
            case LDA_IM_INS:{

                Byte secondByte = fetch(mem,Cycles);
                Accum = secondByte;
                LDA_FLAG_SETTR();

            }break;

            case LDA_ZP_INS:{
                Byte ZPaddress = fetch(mem,Cycles);


            }
            
            default:{
                std::cout << "the instructions could not be handled\n";
            }
                break;
            }
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
    mem.data[0xFFFC] = CPU::LDA_IM_INS; 
    mem.data[0xFFFD] = 0x42; 


    return 0; 
}