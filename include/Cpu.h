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

    /*****************instructions****************/
    void nop();   //0x00
    void incB();  //0x04
    void decB();  //0x05
    void rlcA();  //0x07
    void incC();  //0x0C
    void decC();  //0x0D
    void rrcA();  //0x0F

//1
    void incD();  //0x14
    void decD();  //0x15
    void rlA();   //0x17
    void incE();  //0x1C
    void decE();  //0x1D
    void rrA();   //0x1F

//2
    void incH();  //0x24
    void decH();  //0x25
    void incL();  //0x2C
    void decL();  //0x2D
    void cpl();   //0x2F

//3
    void incSP(); //0x33
    void scf();   //0x37
    void decSP(); //0x3B
    void incA();  //0x3C
    void decA();  //0x3D
    void ccf();   //0x3F

//4
    void ldBB();  //0x40
    void ldBC();  //0x41
    void ldBD();  //0x42
    void ldBE();  //0x43
    void ldBH();  //0x44
    void ldBL();  //0x45
    void ldBA();  //0x47
    void ldCB();  //0x48
    void ldCC();  //0x49
    void ldCD();  //0x4A
    void ldCE();  //0x4B
    void ldCH();  //0x4C
    void ldCL();  //0x4D
    void ldCA();  //0x4F

//5
    void ldDB();  //0x50
    void ldDC();  //0x51
    void ldDD();  //0x52
    void ldDE();  //0x53
    void ldDH();  //0x54
    void ldDL();  //0x55
    void ldDA();  //0x57
    void ldEB();  //0x58
    void ldEC();  //0x59
    void ldED();  //0x5A
    void ldEE();  //0x5B
    void ldEH();  //0x5C
    void ldEL();  //0x5D
    void ldEA();  //0x5F

//6
    void ldHB();  //0x60
    void ldHC();  //0x61
    void ldHD();  //0x62
    void ldHE();  //0x63
    void ldHH();  //0x64
    void ldHL();  //0x65
    void ldHA();  //0x67
    void ldLB();  //0x68
    void ldLC();  //0x69
    void ldLD();  //0x6A
    void ldLE();  //0x6B
    void ldLH();  //0x6C
    void ldLL();  //0x6D
    void ldLA();  //0x6F


//7
    void ldAB();  //0x78
    void ldAC();  //0x79
    void ldAD();  //0x7A
    void ldAE();  //0x7B
    void ldAH();  //0x7C
    void ldAL();  //0x7D
    void ldAA();  //0x7F

//8
    void addAB(); //0x80
    void addAC(); //0x81
    void addAD(); //0x82
    void addAE(); //0x83
    void addAH(); //0x84
    void addAL(); //0x85
    void addAA(); //0x87
    void adcAB(); //0x88
    void adcAC(); //0x89
    void adcAD(); //0x8A
    void adcAE(); //0x8B
    void adcAH(); //0x8C
    void adcAL(); //0x8D
    void adcAA(); //0x8F

//9
    void subAB(); //0x90
    void subAC(); //0x91
    void subAD(); //0x92
    void subAE(); //0x93
    void subAH(); //0x94
    void subAL(); //0x95
    void subAA(); //0x97
    void sbcAB(); //0x98
    void sbcAC(); //0x99
    void sbcAD(); //0x9A
    void sbcAE(); //0x9B
    void sbcAH(); //0x9C
    void sbcAL(); //0x9D
    void sbcAA(); //0x9F

//A

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
    uint8_t regA, regB, regC, regD, regE, regH, regL;

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
