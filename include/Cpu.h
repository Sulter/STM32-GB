#pragma once
#include <cstdint>
#include <functional>
#include <iostream>
#include <cstdio>
#include "../include/Memory.h"

//TODO: move from std::function to function pointers
//TODO: rewrite all the copy-pasted opcodes into templates (depending on register, so we still end up with individual functions)
//TODO: make setFlag override share the 99% of the code they share....
//TODO: instructions for bootstrap ROM:

class Cpu
{
public:
  //! Default constructor
  /*!
      Calls reset to reset all the pointers etc.
      Also sets up the arrays of pointer to the functions with instructions.
     */
  Cpu();

  //! Executes next instruction
  void execute();

  //! set stack pointer, program counter, and the registers to 0
  void reset();

  void printLastInstructions();

  Memory &getMMU() { return MMU; };

protected:
  struct registers
  {
    //! Program counter
    uint16_t pc;
    //! Stack pointer
    uint16_t sp;
    //Basic regsiters
    uint8_t regA, regB, regC, regD, regE, regH, regL;
    //! zero flag
    uint8_t flagZ;
    //! substract flag
    uint8_t flagN;
    //! half-carry flag
    uint8_t flagH;
    //! carry flag
    uint8_t flagC;

    friend std::ostream &operator<<(std::ostream &out, const registers &b)
    {
      char str16bit[30];
      snprintf(str16bit, sizeof(str16bit), "  PC: 0x%04x SP: 0x%04x\n", b.pc, b.sp);
      char str8bit[100];
      snprintf(str8bit, sizeof(str8bit),
               "regA: 0x%02x\nregB: 0x%02x regC: 0x%02x\nregD: 0x%02x regE: 0x%02x\nregH: 0x%02x regL: 0x%02x\n",
               b.regA, b.regB, b.regC, b.regD, b.regE, b.regH, b.regL);
      char strF[40];
      snprintf(strF, sizeof(strF), "regF: 0b%d%d%d%d\n        ZNHC\n", b.flagZ, b.flagN, b.flagH, b.flagC);

      out << str16bit << str8bit << strF;
      return out;
    }
  };

  std::string getInfo(registers reg, uint16_t opcode);
  uint16_t fetchOpcode();
  void runOpcode(uint16_t);
  uint32_t getTotalCycles() const { return totalCycles; };
  uint16_t getPC() const { return regs.pc; };

  registers getRegisters() const { return regs; };
  enum class instructions : uint16_t
  {
    nop = 0x00,
    ldBCnn = 0x01,
    ldBCA = 0x02,
    incBC = 0x03,
    incB = 0x04,
    decB = 0x05,
    ldBn = 0x06,
    rlcA = 0x07,
    ldnnSP = 0x08,
    addHLBC = 0x09,
    ldABC = 0x0A,
    decBC = 0x0B,
    incC = 0x0C,
    decC = 0x0D,
    ldCn = 0x0E,
    rrcA = 0x0F,
    ldDEnn = 0x11,
    ldDEA = 0x12,
    incDE = 0x13,
    incD = 0x14,
    decD = 0x15,
    ldDn = 0x16,
    rlA = 0x17,
    jrn = 0x18,
    addHLDE = 0x19,
    ldADE = 0x1A,
    decDE = 0x1B,
    incE = 0x1C,
    decE = 0x1D,
    ldEn = 0x1E,
    rrA = 0x1F,
    jrnz = 0x20,
    ldHLnn = 0x21,
    ldiHLA = 0x22,
    incHL = 0x23,
    incH = 0x24,
    decH = 0x25,
    ldHn = 0x26,
    addHLHL = 0x29,
    incL = 0x2C,
    decL = 0x2D,
    cpl = 0x2F,
    ldSPnn = 0x31,
    ldiHLAm = 0x32,
    incSP = 0x33,
    scf = 0x37,
    ldAn = 0x38,
    decSP = 0x3B,
    incA = 0x3C,
    decA = 0x3D,
    ccf = 0x3F,
    ldBB = 0x40,
    ldBC = 0x41,
    ldBD = 0x42,
    ldBE = 0x43,
    ldBH = 0x44,
    ldBL = 0x45,
    ldBA = 0x47,
    ldCB = 0x48,
    ldCC = 0x49,
    ldCD = 0x4A,
    ldCE = 0x4B,
    ldCH = 0x4C,
    ldCL = 0x4D,
    ldCA = 0x4F,
    ldDB = 0x50,
    ldDC = 0x51,
    ldDD = 0x52,
    ldDE = 0x53,
    ldDH = 0x54,
    ldDL = 0x55,
    ldDA = 0x57,
    ldEB = 0x58,
    ldEC = 0x59,
    ldED = 0x5A,
    ldEE = 0x5B,
    ldEH = 0x5C,
    ldEL = 0x5D,
    ldEA = 0x5F,
    ldHB = 0x60,
    ldHC = 0x61,
    ldHD = 0x62,
    ldHE = 0x63,
    ldHH = 0x64,
    ldHL = 0x65,
    ldHA = 0x67,
    ldLB = 0x68,
    ldLC = 0x69,
    ldLD = 0x6A,
    ldLE = 0x6B,
    ldLH = 0x6C,
    ldLL = 0x6D,
    ldLA = 0x6F,
    ldHLA = 0x77,
    ldAB = 0x78,
    ldAC = 0x79,
    ldAD = 0x7A,
    ldAE = 0x7B,
    ldAH = 0x7C,
    ldAL = 0x7D,
    ldAA = 0x7F,
    addAB = 0x80,
    addAC = 0x81,
    addAD = 0x82,
    addAE = 0x83,
    addAH = 0x84,
    addAL = 0x85,
    addAA = 0x87,
    adcAB = 0x88,
    adcAC = 0x89,
    adcAD = 0x8A,
    adcAE = 0x8B,
    adcAH = 0x8C,
    adcAL = 0x8D,
    adcAA = 0x8F,
    subAB = 0x90,
    subAC = 0x91,
    subAD = 0x92,
    subAE = 0x93,
    subAH = 0x94,
    subAL = 0x95,
    subAA = 0x97,
    sbcAB = 0x98,
    sbcAC = 0x99,
    sbcAD = 0x9A,
    sbcAE = 0x9B,
    sbcAH = 0x9C,
    sbcAL = 0x9D,
    sbcAA = 0x9F,
    xorA = 0xAF,
    popBC = 0xC1,
    pushBC = 0xC5,
    preCB = 0xCB,
    callnn = 0xCD,
    ldhnA = 0xE0,
    ldCCA = 0xE2
  };

private:
  void noInstruction();
  /*****************instructions****************/
  void nop();     //0x00
  void ldBCnn();  //0x01
  void ldBCA();   //0x02
  void incBC();   //0x03
  void incB();    //0x04
  void decB();    //0x05
  void ldBn();    //0x06
  void rlcA();    //0x07
  void ldnnSP();  //0x08
  void addHLBC(); //0x09
  void ldABC();   //0x0A
  void decBC();   //0x0B
  void incC();    //0x0C
  void decC();    //0x0D
  void ldCn();    //0x0E
  void rrcA();    //0x0F

  //1
  void ldDEnn();  //0x11
  void ldDEA();   //0x12
  void incDE();   //0x13
  void incD();    //0x14
  void decD();    //0x15
  void ldDn();    //0x16
  void rlA();     //0x17
  void jrn();     //0x18
  void addHLDE(); //0x19
  void ldADE();   //0x1A
  void decDE();   //0x1B
  void incE();    //0x1C
  void decE();    //0x1D
  void ldEn();    //0x1E
  void rrA();     //0x1F

  //2
  void jrnz();    //0x20
  void ldHLnn();  //0x21
  void ldiHLA();  //0x22
  void incHL();   //0x23
  void incH();    //0x24
  void decH();    //0x25
  void ldHn();    //0x26
  void jrz();     //0x28
  void addHLHL(); //0x29
  void incL();    //0x2C
  void decL();    //0x2D
  void ldLn();    //0x2E
  void cpl();     //0x2F

  //3
  void ldSPnn();  //0x31
  void ldiHLAm(); //0x32
  void incSP();   //0x33
  void scf();     //0x37
  void ldAn();    //0x38
  void decSP();   //0x3B
  void incA();    //0x3C
  void decA();    //0x3D
  void ccf();     //0x3F

  //4
  void ldBB(); //0x40
  void ldBC(); //0x41
  void ldBD(); //0x42
  void ldBE(); //0x43
  void ldBH(); //0x44
  void ldBL(); //0x45
  void ldBA(); //0x47
  void ldCB(); //0x48
  void ldCC(); //0x49
  void ldCD(); //0x4A
  void ldCE(); //0x4B
  void ldCH(); //0x4C
  void ldCL(); //0x4D
  void ldCA(); //0x4F

  //5
  void ldDB(); //0x50
  void ldDC(); //0x51
  void ldDD(); //0x52
  void ldDE(); //0x53
  void ldDH(); //0x54
  void ldDL(); //0x55
  void ldDA(); //0x57
  void ldEB(); //0x58
  void ldEC(); //0x59
  void ldED(); //0x5A
  void ldEE(); //0x5B
  void ldEH(); //0x5C
  void ldEL(); //0x5D
  void ldEA(); //0x5F

  //6
  void ldHB(); //0x60
  void ldHC(); //0x61
  void ldHD(); //0x62
  void ldHE(); //0x63
  void ldHH(); //0x64
  void ldHL(); //0x65
  void ldHA(); //0x67
  void ldLB(); //0x68
  void ldLC(); //0x69
  void ldLD(); //0x6A
  void ldLE(); //0x6B
  void ldLH(); //0x6C
  void ldLL(); //0x6D
  void ldLA(); //0x6F

  //7
  void ldHLA(); //0x77
  void ldAB();  //0x78
  void ldAC();  //0x79
  void ldAD();  //0x7A
  void ldAE();  //0x7B
  void ldAH();  //0x7C
  void ldAL();  //0x7D
  void ldAA();  //0x7F

  //8
  void addAB();  //0x80
  void addAC();  //0x81
  void addAD();  //0x82
  void addAE();  //0x83
  void addAH();  //0x84
  void addAL();  //0x85
  void addAHL(); //0x86
  void addAA();  //0x87
  void adcAB();  //0x88
  void adcAC();  //0x89
  void adcAD();  //0x8A
  void adcAE();  //0x8B
  void adcAH();  //0x8C
  void adcAL();  //0x8D
  void adcAA();  //0x8F

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
  void xorA(); //0xAF

  //B
  void cpHL(); //0xBE

  //C
  void popBC();  //0xC1
  void pushBC(); //0xC5
  void ret();    //0xC9
  void preCB();  //0xCB
  void callnn(); //0xCD

  //D

  //E
  void ldhnA(); //0xE0
  void ldCCA(); //0xE2
  void ldnnA(); //0xEA

  //F
  void ldhAn(); //0xF0
  void cpn();   //0xFE

  //CB1
  void CBRLC(); //0x11

  //CB7
  void CBbit7H(); //0x7C

  //! Reference to the memory
  Memory MMU;

  static constexpr uint16_t opcodeNumber = 0xff * 2;

  //! pointer to opcode functions
  std::array<std::function<void()>, opcodeNumber> opcodes;

  //! Stores the clock cycles of the last insturction
  uint8_t lastCycle;

  //! Stores the total amount of clock cycles ran
  uint32_t totalCycles;

  static constexpr uint8_t CBval = 0xff;
  uint8_t CB;

  registers regs = {};

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
  void setFlag(int8_t zero, int8_t substract, int8_t halfCarry, int8_t carry, uint8_t a, uint8_t temp);
  void setFlag(int8_t zero, int8_t substract, int8_t halfCarry, int8_t carry, uint16_t a, uint16_t temp);
};
