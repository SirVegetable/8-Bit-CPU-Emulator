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
    Byte fetchbyte(Memory &mem, unsigned int &Cycles){
        Byte data = mem.data[ProgramCounter]; 
        ProgramCounter++;
        Cycles--; 

        return data; 
    }

    Rock fetchRock(Memory &mem, unsigned int &Cycles){
        // this is little endian 
        Byte lowbyte = mem.data[ProgramCounter]; 
        ProgramCounter++; 
        Cycles--; 
        //bits after ProgramCounter is incremented
        Byte highbyte = mem.data[ProgramCounter];

        Rock data = static_cast<Rock> (lowbyte) | static_cast<Rock> (highbyte); 

        return data; 
    }
    //function to read a byte through a CPU cycle but doesn't increment PC like fetch
    Byte readByte(Memory &mem,Byte Address,unsigned int& Cycles){
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
    static constexpr Byte 
        LDA_IM_INS = 0xA89, 
        LDA_ZP_INS = 0xA5,
        LDA_ZPX_INS = 0xB5; 

    /*This is where the operation is performed, every part of the cpu that is needed activated
    to carry out the instructions*/
    
    
    void execute(Memory &mem, unsigned int Cycles){

        while (Cycles != 0){
            Byte instructions = fetchbyte(mem, Cycles);
            switch (instructions)
            {
            case LDA_IM_INS:{

                Byte secondByte = fetchbyte(mem,Cycles);
                Accum = secondByte;
                LDA_FLAG_SETTR();

            }break;

            case LDA_ZP_INS:{
                Byte ZPaddress = fetchbyte(mem,Cycles);
                Accum = readByte(mem,ZPaddress, Cycles);
                LDA_FLAG_SETTR();
            }break;

            case LDA_ZPX_INS:{
                Byte ZPaddress = fetchbyte(mem,Cycles);
                ZPaddress += X;
                Cycles--;
                Accum = readByte(mem,ZPaddress,Cycles);
                LDA_FLAG_SETTR(); 

            }break; 
            
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