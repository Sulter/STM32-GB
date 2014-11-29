#include <cstdint>

class Cpu
{
public:
    //! Default constructor
    /*!
      Calls reset to reset all the pointers etc.
      Also sets up the arrays of pointer to the functions with instructions.
     */
    Cpu();

    //! set stack pointer, program counter, and the registers to 0
    void reset();

    /*****************all the opcodes****************/
    void nop();   //0x01
    void incB();  //0x04
    void decB();  //0x05
    void rlcA();  //0x07
    void incC();  //0x0C
    void decC();  //0x0D
    void rrcA();  //0x0F

    void incD();  //0x14
    void decD();  //0x15
    void rlA();   //0x17

    void incA();  //0x3C

private:
    //! pointer to opcode functions
    typedef void (Cpu::*opcodeFunctionPointer) ();

    //! Array of pointers to opcode instructions.
    const opcodeFunctionPointer opcodeMap[2];

    //! Array of pointers to the extended opcode instructions.
    //const opcodeFunctionPointer opcodeExtendedMap[2];

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

    //! register F flags
    uint8_t flagZ, flagN, flagH, flagC;

    //! Stores the clock cycles of the last insturction
    uint8_t lastCycle;

    //! Stores the total amount of clock cycles ran
    uint32_t totalCycles;

    //! Sets the flags, according to settings
    /*!
      Called by all opcode-functions that influence the flag register. 
      \param zero -1 ignore, 0 set to 0 no matter what, 1 - set to 1 no matter what, 2 - set if \p a is 0 else set to 0
      \param substract -1 ignore, 0 set to 0 no matter what, 1 - set to 1 no matter what
      \param halfCarry -1 ignore, 0 set to 0 no matter what, 1 - set to 1 no matter what,  <br>
      2 - *temp is being added to a* set if there is a half carry when adding temp to a (else set to 0) <br>
      3 - *temp is being substracted from a* set if there is a half carry borrow when substracting temp from a (else set to 0)<br>
      \param carry -1 ignore, 0 set to 0 no matter what, 1 - set to 1 no matter what, <br>
      2 - *temp is being added to a* set if there is a carry when adding temp to a (else set to 0) <br>
      3 - *temp is being substracted from a* set if there is a carry when substracting temp from a (else set to 0) <br>
      \param a - the result of the operation
      \param temp - the value before the operation, or the value added/substracted to a
     */
    void setFlag(int8_t zero, int8_t substract, int8_t halfCarry, int8_t carry, const uint8_t & a, uint8_t temp);

};
