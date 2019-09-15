#include "../include/Cpu.h"

Cpu::Cpu()
{
  reset();

  opcodes.fill(std::bind(&Cpu::noInstruction, this));

  opcodes[0x00] = std::bind(&Cpu::nop, this);
  opcodes[0x01] = std::bind(&Cpu::ldBCnn, this);
  opcodes[0x02] = std::bind(&Cpu::ldBCA, this);
  opcodes[0x03] = std::bind(&Cpu::incBC, this);
  opcodes[0x04] = std::bind(&Cpu::incB, this);
  opcodes[0x05] = std::bind(&Cpu::decB, this);
  opcodes[0x06] = std::bind(&Cpu::ldBn, this);
  opcodes[0x07] = std::bind(&Cpu::rlcA, this);
  opcodes[0x08] = std::bind(&Cpu::ldnnSP, this);
  opcodes[0x09] = std::bind(&Cpu::addHLBC, this);
  opcodes[0x0A] = std::bind(&Cpu::ldABC, this);
  opcodes[0x0B] = std::bind(&Cpu::decBC, this);
  opcodes[0x0C] = std::bind(&Cpu::incC, this);
  opcodes[0x0D] = std::bind(&Cpu::decC, this);
  opcodes[0x0E] = std::bind(&Cpu::ldCn, this);
  opcodes[0x0F] = std::bind(&Cpu::rrcA, this);
  opcodes[0x11] = std::bind(&Cpu::ldDEnn, this);
  opcodes[0x12] = std::bind(&Cpu::ldDEA, this);
  opcodes[0x13] = std::bind(&Cpu::incDE, this);
  opcodes[0x14] = std::bind(&Cpu::incD, this);
  opcodes[0x15] = std::bind(&Cpu::decD, this);
  opcodes[0x16] = std::bind(&Cpu::ldDn, this);
  opcodes[0x17] = std::bind(&Cpu::rlA, this);
  opcodes[0x18] = std::bind(&Cpu::jrn, this);
  opcodes[0x19] = std::bind(&Cpu::addHLDE, this);
  opcodes[0x1A] = std::bind(&Cpu::ldADE, this);
  opcodes[0x1B] = std::bind(&Cpu::decDE, this);
  opcodes[0x1C] = std::bind(&Cpu::incE, this);
  opcodes[0x1D] = std::bind(&Cpu::decE, this);
  opcodes[0x1E] = std::bind(&Cpu::ldEn, this);
  opcodes[0x1F] = std::bind(&Cpu::rrA, this);
  opcodes[0x21] = std::bind(&Cpu::ldHLnn, this);
  opcodes[0x22] = std::bind(&Cpu::ldiHLA, this);
  opcodes[0x23] = std::bind(&Cpu::incHL, this);
  opcodes[0x24] = std::bind(&Cpu::incH, this);
  opcodes[0x25] = std::bind(&Cpu::decH, this);
  opcodes[0x26] = std::bind(&Cpu::ldHn, this);
  opcodes[0x29] = std::bind(&Cpu::addHLHL, this);
  opcodes[0x2C] = std::bind(&Cpu::incL, this);
  opcodes[0x2D] = std::bind(&Cpu::decL, this);
  opcodes[0x2F] = std::bind(&Cpu::cpl, this);
  opcodes[0x31] = std::bind(&Cpu::ldSPnn, this);
  opcodes[0x32] = std::bind(&Cpu::ldiHLAm, this);
  opcodes[0x33] = std::bind(&Cpu::incSP, this);
  opcodes[0x37] = std::bind(&Cpu::scf, this);
  opcodes[0x3B] = std::bind(&Cpu::decSP, this);
  opcodes[0x3C] = std::bind(&Cpu::incA, this);
  opcodes[0x3D] = std::bind(&Cpu::decA, this);
  opcodes[0x3F] = std::bind(&Cpu::ccf, this);
  opcodes[0x40] = std::bind(&Cpu::ldBB, this);
  opcodes[0x41] = std::bind(&Cpu::ldBC, this);
  opcodes[0x42] = std::bind(&Cpu::ldBD, this);
  opcodes[0x43] = std::bind(&Cpu::ldBE, this);
  opcodes[0x44] = std::bind(&Cpu::ldBH, this);
  opcodes[0x45] = std::bind(&Cpu::ldBL, this);
  opcodes[0x47] = std::bind(&Cpu::ldBA, this);
  opcodes[0x48] = std::bind(&Cpu::ldCB, this);
  opcodes[0x49] = std::bind(&Cpu::ldCC, this);
  opcodes[0x4A] = std::bind(&Cpu::ldCD, this);
  opcodes[0x4B] = std::bind(&Cpu::ldCE, this);
  opcodes[0x4C] = std::bind(&Cpu::ldCH, this);
  opcodes[0x4D] = std::bind(&Cpu::ldCL, this);
  opcodes[0x4F] = std::bind(&Cpu::ldCA, this);
  opcodes[0x50] = std::bind(&Cpu::ldDB, this);
  opcodes[0x51] = std::bind(&Cpu::ldDC, this);
  opcodes[0x52] = std::bind(&Cpu::ldDD, this);
  opcodes[0x53] = std::bind(&Cpu::ldDE, this);
  opcodes[0x54] = std::bind(&Cpu::ldDH, this);
  opcodes[0x55] = std::bind(&Cpu::ldDL, this);
  opcodes[0x57] = std::bind(&Cpu::ldDA, this);
  opcodes[0x58] = std::bind(&Cpu::ldEB, this);
  opcodes[0x59] = std::bind(&Cpu::ldEC, this);
  opcodes[0x5A] = std::bind(&Cpu::ldED, this);
  opcodes[0x5B] = std::bind(&Cpu::ldEE, this);
  opcodes[0x5C] = std::bind(&Cpu::ldEH, this);
  opcodes[0x5D] = std::bind(&Cpu::ldEL, this);
  opcodes[0x5F] = std::bind(&Cpu::ldEA, this);
  opcodes[0x60] = std::bind(&Cpu::ldHB, this);
  opcodes[0x61] = std::bind(&Cpu::ldHC, this);
  opcodes[0x62] = std::bind(&Cpu::ldHD, this);
  opcodes[0x63] = std::bind(&Cpu::ldHE, this);
  opcodes[0x64] = std::bind(&Cpu::ldHH, this);
  opcodes[0x65] = std::bind(&Cpu::ldHL, this);
  opcodes[0x67] = std::bind(&Cpu::ldHA, this);
  opcodes[0x68] = std::bind(&Cpu::ldLB, this);
  opcodes[0x69] = std::bind(&Cpu::ldLC, this);
  opcodes[0x6A] = std::bind(&Cpu::ldLD, this);
  opcodes[0x6B] = std::bind(&Cpu::ldLE, this);
  opcodes[0x6C] = std::bind(&Cpu::ldLH, this);
  opcodes[0x6D] = std::bind(&Cpu::ldLL, this);
  opcodes[0x6F] = std::bind(&Cpu::ldLA, this);
  opcodes[0x78] = std::bind(&Cpu::ldAB, this);
  opcodes[0x79] = std::bind(&Cpu::ldAC, this);
  opcodes[0x7A] = std::bind(&Cpu::ldAD, this);
  opcodes[0x7B] = std::bind(&Cpu::ldAE, this);
  opcodes[0x7C] = std::bind(&Cpu::ldAH, this);
  opcodes[0x7D] = std::bind(&Cpu::ldAL, this);
  opcodes[0x7F] = std::bind(&Cpu::ldAA, this);
  opcodes[0x80] = std::bind(&Cpu::addAB, this);
  opcodes[0x81] = std::bind(&Cpu::addAC, this);
  opcodes[0x82] = std::bind(&Cpu::addAD, this);
  opcodes[0x83] = std::bind(&Cpu::addAE, this);
  opcodes[0x84] = std::bind(&Cpu::addAH, this);
  opcodes[0x85] = std::bind(&Cpu::addAL, this);
  opcodes[0x87] = std::bind(&Cpu::addAA, this);
  opcodes[0x88] = std::bind(&Cpu::adcAB, this);
  opcodes[0x89] = std::bind(&Cpu::adcAC, this);
  opcodes[0x8A] = std::bind(&Cpu::adcAD, this);
  opcodes[0x8B] = std::bind(&Cpu::adcAE, this);
  opcodes[0x8C] = std::bind(&Cpu::adcAH, this);
  opcodes[0x8D] = std::bind(&Cpu::adcAL, this);
  opcodes[0x8F] = std::bind(&Cpu::adcAA, this);
  opcodes[0x90] = std::bind(&Cpu::subAB, this);
  opcodes[0x91] = std::bind(&Cpu::subAC, this);
  opcodes[0x92] = std::bind(&Cpu::subAD, this);
  opcodes[0x93] = std::bind(&Cpu::subAE, this);
  opcodes[0x94] = std::bind(&Cpu::subAH, this);
  opcodes[0x95] = std::bind(&Cpu::subAL, this);
  opcodes[0x97] = std::bind(&Cpu::subAA, this);
  opcodes[0x98] = std::bind(&Cpu::sbcAB, this);
  opcodes[0x99] = std::bind(&Cpu::sbcAC, this);
  opcodes[0x9A] = std::bind(&Cpu::sbcAD, this);
  opcodes[0x9B] = std::bind(&Cpu::sbcAE, this);
  opcodes[0x9C] = std::bind(&Cpu::sbcAH, this);
  opcodes[0x9D] = std::bind(&Cpu::sbcAL, this);
  opcodes[0x9F] = std::bind(&Cpu::sbcAA, this);
  opcodes[0xAF] = std::bind(&Cpu::xorA, this);
}

void Cpu::runOpcode(uint16_t opcode)
{
  opcodes[opcode]();
  totalCycles += lastCycle;
}

void Cpu::execute()
{
  runOpcode(fetchOpcode());
}

uint16_t Cpu::fetchOpcode()
{
  return MMU.readByte(regs.pc);
}

void Cpu::reset()
{
  registers zeroed = {};
  regs = zeroed;
  totalCycles = 0;
  lastCycle = 0;
}

void Cpu::setFlag(int8_t zero, int8_t substract, int8_t halfCarry, int8_t carry, uint8_t a, uint8_t temp)
{
  //take care of zero-flag (7th bit)
  if (zero == 0)
    regs.flagZ = 0; //clear Z flag
  else if (zero == 1)
    regs.flagZ = 1; //set Z flag
  else if (zero == 2)
  {
    if (a == 0)
      regs.flagZ = 1; //set Z flag
    else
      regs.flagZ = 0; //clear Z flag
  }

  //take care of substract-flag (6th bit)
  if (substract == 0)
    regs.flagN = 0; //clear sub flag
  else if (substract == 1)
    regs.flagN = 1; //set sub flag

  //take care of half-carry-flag (and half borrow) (5th bit)
  if (halfCarry == 0)
    regs.flagH = 0; //clear half-carry-flag
  else if (halfCarry == 1)
    regs.flagH = 1;        //set the half-carry-flag
  else if (halfCarry == 2) //temp has been added to A
  {
    uint8_t aTemp = a;
    aTemp -= temp;
    if (((aTemp + temp) & 0xF) < (aTemp & 0xF))
      regs.flagH = 1; //set half-carry-flag
    else
      regs.flagH = 0; //clear the half-carry-flag
  }
  else if (halfCarry == 3) //temp has been substracted from A
  {
    uint8_t aTemp = a;
    aTemp += temp;
    if ((aTemp & 0xF) < ((aTemp - temp) & 0xF))
      regs.flagH = 1; //set half-carry-flag
    else
      regs.flagH = 0; //clear the half-carry-flag
  }

  /*
      C++ promotes uint8_t to int when using arithmetic operators.
      We can use this behaviour:
      By undoing the last operation, and checking if the value is bigger or smaller than 0, we know if an overflow has happend.
    */
  //take care of carry-flag (and borrow) (4th bit)
  if (carry == 0)
    regs.flagC = 0; //clear carryregs.flag
  else if (carry == 1)
    regs.flagC = 1;    //set carryregs.flag
  else if (carry == 2) //temp has been added to A
  {
    if (a - temp < 0)
      regs.flagC = 1; //there is a carry!
    else
      regs.flagC = 0; //there is no carry
  }
  else if (carry == 3) //temp has been substracted from A
  {
    if (a + temp > 255)
      regs.flagC = 1; //there is a borrow!
    else
      regs.flagC = 0; //no borrow
  }
}

void Cpu::setFlag(int8_t zero, int8_t substract, int8_t halfCarry, int8_t carry, uint16_t a, uint16_t temp)
{
  //take care of zero-flag (7th bit)
  if (zero == 0)
    regs.flagZ = 0; //clear Zregs.flag
  else if (zero == 1)
    regs.flagZ = 1; //set Zregs.flag
  else if (zero == 2)
  {
    if (a == 0)
      regs.flagZ = 1; //set Zregs.flag
    else
      regs.flagZ = 0;
    ; //clear Zregs.flag
  }

  //take care of substract-flag (6th bit)
  if (substract == 0)
    regs.flagN = 0; //clear subregs.flag
  else if (substract == 1)
    regs.flagN = 1; //set subregs.flag

  //take care of half-carry-flag (and half borrow) (5th bit)
  if (halfCarry == 0)
    regs.flagH = 0; //clear half-carry-flag
  else if (halfCarry == 1)
    regs.flagH = 1;        //set the half-carry-flag
  else if (halfCarry == 2) //temp has been added to A
  {
    uint16_t aTemp = a;
    aTemp -= temp;
    if (((aTemp + temp) & 0xFFF) < (aTemp & 0xFFF))
      regs.flagH = 1; //set half-carry-flag
    else
      regs.flagH = 0; //clear the half-carry-flag
  }
  else if (halfCarry == 3) //temp has been substracted from A
  {
    uint16_t aTemp = a;
    aTemp += temp;
    if ((aTemp & 0xFFF) < ((aTemp - temp) & 0xFFF))
      regs.flagH = 1; //set half-carry-flag
    else
      regs.flagH = 0; //clear the half-carry-flag
  }

  /*
      C++ promotes uint8_t to int when using arithmetic operators.
      We can use this behaviour:
      By undoing the last operation, and checking if the value is bigger or smaller than 0, we know if an overflow has happend.
    */
  //take care of carry-flag (and borrow) (4th bit)
  if (carry == 0)
    regs.flagC = 0; //clear carryregs.flag
  else if (carry == 1)
    regs.flagC = 1;    //set carryregs.flag
  else if (carry == 2) //temp has been added to A
  {
    if (a - temp < 0)
      regs.flagC = 1; //there is a carry!
    else
      regs.flagC = 0; //there is no carry
  }
  else if (carry == 3) //temp has been substracted from A
  {
    if (a + temp > 0xffff)
      regs.flagC = 1; //there is a borrow!
    else
      regs.flagC = 0; //no borrow
  }
}
