#include <cstdint>

class Cpu
{
public:
    //! Default constructor - initializes the CPU
    Cpu();


private:
    //! pointer to opcode functions
    typedef void (Cpu::*opcodeFunctionPointer) ();

    //! Array of pointers to opcode instructions.
    const opcodeFunctionPointer opcodeMap[2];

    //! Program counter
    uint16_t pc;
    
    //! Stack pointer
    uint16_t sp;

    //Basic regsiters
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t regD;
    uint8_t regE; 
    uint8_t regH;
    uint8_t regL;

    //! Flag regsiter
    uint8_t regF;  

    //! Stores the clock cycles of the last insturction
    uint8_t lastCycle;

    //! Stores the total amount of clock cycles ran
    uint32_t totalCycles;

    //! All the cpu instructions
    void DCC();
};
