#include "../include/Cpu.h"

void Cpu::noInstruction()
{
  std::cout << "Not-implemented called !" << std::endl;
  std::cout << "  op: 0x" << std::hex << fetchOpcode() << std::endl;
  std::cout << regs << std::endl;
}

void Cpu::nop()
{
  lastCycle = 4;
  regs.pc++;
}

void Cpu::ldBCnn()
{
  regs.regC = MMU.readByte(regs.pc + 1);
  regs.regB = MMU.readByte(regs.pc + 2);
  lastCycle = 12;
  regs.pc += 3;
}

void Cpu::ldBCA()
{
  MMU.writeByte((regs.regB << 8) | regs.regC, regs.regA);
  lastCycle = 8;
  regs.pc++;
}

void Cpu::incBC()
{
  regs.regC++;
  if (!regs.regC)
    regs.regB++;

  lastCycle = 8;
  regs.pc++;
}

void Cpu::incB()
{
  regs.regB++; //increase the register

  setFlag(2, 0, 2, -1, regs.regB, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::decB()
{
  regs.regB--; //decrease the register

  setFlag(2, 1, 3, -1, regs.regB, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::ldBn()
{
  regs.regB = MMU.readByte(regs.pc + 1);
  lastCycle = 8;
  regs.pc += 2;
}

void Cpu::rlcA()
{
  uint8_t temp = regs.regA & (0x80);
  regs.regA <<= 1;
  regs.regA |= temp >> 7;
  setFlag(0, 0, 0, 3, temp, 0xff);

  lastCycle = 4;
  regs.pc++;
}

void Cpu::ldnnSP()
{
  uint16_t address = (MMU.readByte(regs.pc + 1) << 8) | MMU.readByte(regs.pc + 2);
  MMU.writeByte(address, regs.sp & 0xff);
  MMU.writeByte(address + 1, (regs.sp >> 8) & 0xff);
  lastCycle = 20;
  regs.pc += 3;
}

void Cpu::addHLBC()
{
  uint16_t total = ((regs.regH << 8) | regs.regL) + ((regs.regB << 8) | regs.regC);
  regs.regH = total >> 8;
  regs.regL = total & 0xff;
  setFlag(-1, 0, 2, 2, ((regs.regH << 8) | regs.regL), (uint16_t)((regs.regB << 8) | regs.regC)); //"- 0 H C"

  lastCycle = 8;
  regs.pc++;
}

void Cpu::ldABC()
{
  regs.regA = MMU.readByte((regs.regB << 8) | regs.regC);

  lastCycle = 8;
  regs.pc++;
}

void Cpu::decBC()
{
  if (!regs.regC)
  {
    regs.regB--;
  }
  regs.regC--;

  lastCycle = 8;
  regs.pc++;
}

void Cpu::incC()
{
  regs.regC++; //increase the register

  setFlag(2, 0, 2, -1, regs.regC, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::decC()
{
  regs.regC--; //decrease the register

  setFlag(2, 1, 3, -1, regs.regC, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::ldCn()
{
  regs.regC = MMU.readByte(regs.pc + 1);

  lastCycle = 8;
  regs.pc += 2;
}

void Cpu::rrcA()
{
  uint8_t temp = regs.regA & (0x01);
  regs.regA >>= 1;
  regs.regA |= temp << 7;
  setFlag(0, 0, 0, 3, 0xff, temp);

  lastCycle = 4;
  regs.pc++;
  ;
}

/*
****************0x1x******************
*/

void Cpu::ldDEnn()
{
  regs.regE = MMU.readByte(regs.pc + 1);
  regs.regD = MMU.readByte(regs.pc + 2);
  lastCycle = 12;
  regs.pc += 3;
}

void Cpu::ldDEA()
{
  MMU.writeByte((regs.regD << 8) | regs.regE, regs.regA);
  lastCycle = 8;
  regs.pc++;
}

void Cpu::incDE()
{
  regs.regE++;
  if (!regs.regE)
    regs.regD++;

  lastCycle = 8;
  regs.pc++;
}

void Cpu::incD()
{
  regs.regD++; //increase the register

  setFlag(2, 0, 2, -1, regs.regD, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::decD()
{
  regs.regD--; //decrease the register

  setFlag(2, 1, 3, -1, regs.regD, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::ldDn()
{
  regs.regD = MMU.readByte(regs.pc + 1);
  lastCycle = 8;
  regs.pc += 2;
}

void Cpu::rlA()
{
  uint8_t temp = regs.regA & (0x80);
  regs.regA <<= 1;
  regs.regA |= regs.flagC;
  setFlag(0, 0, 0, 3, temp, 0xff);

  lastCycle = 4;
  regs.pc++;
}

void Cpu::jrn()
{
  regs.pc = regs.pc + MMU.readByte(regs.pc + 1);
  lastCycle = 12;
}

void Cpu::addHLDE()
{
  uint16_t total = ((regs.regH << 8) | regs.regL) + ((regs.regD << 8) | regs.regE);
  regs.regH = total >> 8;
  regs.regL = total & 0xff;
  setFlag(-1, 0, 2, 2, ((regs.regH << 8) | regs.regL), (uint16_t)((regs.regD << 8) | regs.regE)); //"- 0 H C"

  lastCycle = 8;
  regs.pc++;
}

void Cpu::ldADE()
{
  regs.regA = MMU.readByte((regs.regD << 8) | regs.regE);

  lastCycle = 8;
  regs.pc++;
}

void Cpu::decDE()
{
  if (!regs.regE)
  {
    regs.regD--;
  }
  regs.regE--;

  lastCycle = 8;
  regs.pc++;
}

void Cpu::incE()
{
  regs.regE++; //increase the register

  setFlag(2, 0, 2, -1, regs.regE, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::decE()
{
  regs.regE--; //decrease the register

  setFlag(2, 1, 3, -1, regs.regE, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::ldEn()
{
  regs.regE = MMU.readByte(regs.pc + 1);

  lastCycle = 8;
  regs.pc += 2;
}

void Cpu::rrA()
{
  uint8_t temp = regs.regA & (0x01);
  regs.regA >>= 1;
  regs.regA |= regs.flagC << 7;
  setFlag(0, 0, 0, 3, temp, 0xff);

  lastCycle = 4;
  regs.pc++;
}

/*
****************0x2x******************
*/

void Cpu::ldHLnn()
{
  regs.regL = MMU.readByte(regs.pc + 1);
  regs.regH = MMU.readByte(regs.pc + 2);
  lastCycle = 12;
  regs.pc += 3;
}

void Cpu::ldiHLA()
{
  MMU.writeByte((regs.regH << 8) | regs.regL, regs.regA);

  regs.regL++;
  if (!regs.regL)
    regs.regH++;

  lastCycle = 8;
  regs.pc++;
}

void Cpu::incHL()
{
  regs.regL++;
  if (!regs.regL)
    regs.regH++;

  lastCycle = 8;
  regs.pc++;
}

void Cpu::incH()
{
  regs.regH++; //increase the register

  setFlag(2, 0, 2, -1, regs.regH, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::decH()
{
  regs.regH--; //decrease the register

  setFlag(2, 1, 3, -1, regs.regH, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::ldHn()
{
  regs.regH = MMU.readByte(regs.pc + 1);
  lastCycle = 8;
  regs.pc += 2;
}

void Cpu::addHLHL()
{
  uint16_t total = ((regs.regH << 8) | regs.regL) + ((regs.regH << 8) | regs.regL);
  regs.regH = total >> 8;
  regs.regL = total & 0xff;
  setFlag(-1, 0, 2, 2, ((regs.regH << 8) | regs.regL), (uint16_t)((regs.regH << 8) | regs.regL)); //"- 0 H C"

  lastCycle = 8;
  regs.pc++;
}

void Cpu::incL()
{
  regs.regL++; //increase the register

  setFlag(2, 0, 2, -1, regs.regL, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::decL()
{
  regs.regL--; //decrease the register

  setFlag(2, 1, 3, -1, regs.regL, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::cpl()
{
  regs.regA = ~regs.regA;
  setFlag(-1, 1, 1, -1, 0, (uint8_t)0); //"- 1 1 -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

/*
****************0x3x******************
*/

void Cpu::ldSPnn()
{
  regs.sp = (MMU.readByte(regs.pc + 1) | (MMU.readByte(regs.pc + 2) << 8));

  regs.pc += 3;
  lastCycle = 12;
}

void Cpu::ldiHLAm()
{
  MMU.writeByte((regs.regH << 8) | regs.regL, regs.regA);

  uint16_t tmp = ((regs.regH << 8) | regs.regL);
  tmp--;

  regs.regH = tmp >> 8;
  regs.regL = tmp;

  lastCycle = 8;
  regs.pc++;
}

void Cpu::incSP()
{
  regs.sp++;

  regs.pc++;
  lastCycle = 8;
}

void Cpu::scf()
{
  regs.flagC = 1;

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::decSP()
{
  regs.sp--;

  regs.pc++;
  lastCycle = 8;
}

void Cpu::incA()
{
  regs.regA++; //increase the register

  setFlag(2, 0, 2, -1, regs.regA, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::decA()
{
  regs.regA--; //decrease the register

  setFlag(2, 1, 3, -1, regs.regA, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  regs.pc++;     //increase the program regs.pc
}

void Cpu::ccf()
{
  regs.flagC = ~regs.flagC;
  regs.flagC &= 0x01;
  lastCycle = 4;
  regs.pc++;
}

/*
****************0x4x******************
*/

void Cpu::ldBB()
{
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldBC()
{
  regs.regB = regs.regC;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldBD()
{
  regs.regB = regs.regD;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldBE()
{
  regs.regB = regs.regE;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldBH()
{
  regs.regB = regs.regH;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldBL()
{
  regs.regB = regs.regL;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldBA()
{
  regs.regB = regs.regA;
  lastCycle = 4;
  regs.pc++;
}

void Cpu::ldCB()
{
  regs.regC = regs.regB;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldCC()
{
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldCD()
{
  regs.regC = regs.regD;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldCE()
{
  regs.regC = regs.regE;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldCH()
{
  regs.regC = regs.regH;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldCL()
{
  regs.regC = regs.regL;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldCA()
{
  regs.regC = regs.regA;
  lastCycle = 4;
  regs.pc++;
}

/*
****************0x5x******************
*/

void Cpu::ldDB()
{
  regs.regD = regs.regB;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldDC()
{
  regs.regD = regs.regC;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldDD()
{
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldDE()
{
  regs.regD = regs.regE;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldDH()
{
  regs.regD = regs.regH;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldDL()
{
  regs.regD = regs.regL;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldDA()
{
  regs.regD = regs.regA;
  lastCycle = 4;
  regs.pc++;
}

void Cpu::ldEB()
{
  regs.regE = regs.regB;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldEC()
{
  regs.regE = regs.regC;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldED()
{
  regs.regE = regs.regD;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldEE()
{
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldEH()
{
  regs.regE = regs.regH;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldEL()
{
  regs.regE = regs.regL;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldEA()
{
  regs.regE = regs.regA;
  lastCycle = 4;
  regs.pc++;
}

/*
****************0x6x******************
*/

void Cpu::ldHB()
{
  regs.regH = regs.regB;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldHC()
{
  regs.regH = regs.regC;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldHD()
{
  regs.regH = regs.regD;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldHE()
{
  regs.regH = regs.regE;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldHH()
{
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldHL()
{
  regs.regH = regs.regL;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldHA()
{
  regs.regH = regs.regA;
  lastCycle = 4;
  regs.pc++;
}

void Cpu::ldLB()
{
  regs.regL = regs.regB;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldLC()
{
  regs.regL = regs.regC;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldLD()
{
  regs.regL = regs.regD;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldLE()
{
  regs.regL = regs.regE;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldLH()
{
  regs.regL = regs.regH;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldLL()
{
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldLA()
{
  regs.regL = regs.regA;
  lastCycle = 4;
  regs.pc++;
}

/*
****************0x7x******************
*/

void Cpu::ldAB()
{
  regs.regA = regs.regB;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldAC()
{
  regs.regA = regs.regC;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldAD()
{
  regs.regA = regs.regD;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldAE()
{
  regs.regA = regs.regE;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldAH()
{
  regs.regA = regs.regH;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldAL()
{
  regs.regA = regs.regL;
  lastCycle = 4;
  regs.pc++;
}
void Cpu::ldAA()
{
  lastCycle = 4;
  regs.pc++;
}

/*
****************0x8x******************
*/

void Cpu::addAB()
{
  regs.regA += regs.regB;

  setFlag(2, 0, 2, 2, regs.regA, regs.regB); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::addAC()
{
  regs.regA += regs.regC;

  setFlag(2, 0, 2, 2, regs.regA, regs.regC); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::addAD()
{
  regs.regA += regs.regD;

  setFlag(2, 0, 2, 2, regs.regA, regs.regD); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::addAE()
{
  regs.regA += regs.regE;

  setFlag(2, 0, 2, 2, regs.regA, regs.regE); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::addAH()
{
  regs.regA += regs.regH;

  setFlag(2, 0, 2, 2, regs.regA, regs.regH); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::addAL()
{
  regs.regA += regs.regL;

  setFlag(2, 0, 2, 2, regs.regA, regs.regL); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::addAA()
{
  regs.regA += regs.regA;

  setFlag(2, 0, 2, 2, regs.regA, regs.regA); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::adcAB()
{
  regs.regA += regs.regB + regs.flagC;

  setFlag(2, 0, 2, 2, regs.regA, regs.regB + regs.flagC); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::adcAC()
{
  regs.regA += regs.regC + regs.flagC;

  setFlag(2, 0, 2, 2, regs.regA, regs.regC + regs.flagC); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::adcAD()
{
  regs.regA += regs.regD + regs.flagC;

  setFlag(2, 0, 2, 2, regs.regA, regs.regD + regs.flagC); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::adcAE()
{
  regs.regA += regs.regE + regs.flagC;

  setFlag(2, 0, 2, 2, regs.regA, regs.regE + regs.flagC); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::adcAH()
{
  regs.regA += regs.regH + regs.flagC;

  setFlag(2, 0, 2, 2, regs.regA, regs.regH + regs.flagC); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::adcAL()
{
  regs.regA += regs.regL + regs.flagC;

  setFlag(2, 0, 2, 2, regs.regA, regs.regL + regs.flagC); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::adcAA()
{
  regs.regA += regs.regA + regs.flagC;

  setFlag(2, 0, 2, 2, regs.regA, regs.regA + regs.flagC); //"Z 0 H C"

  lastCycle = 4;
  regs.pc++;
}

/*
****************0x9x******************
*/

void Cpu::subAB()
{
  regs.regA -= regs.regB;

  setFlag(2, 1, 3, 3, regs.regA, regs.regB); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::subAC()
{
  regs.regA -= regs.regC;

  setFlag(2, 1, 3, 3, regs.regA, regs.regC); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::subAD()
{
  regs.regA -= regs.regD;

  setFlag(2, 1, 3, 3, regs.regA, regs.regD); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::subAE()
{
  regs.regA -= regs.regE;

  setFlag(2, 1, 3, 3, regs.regA, regs.regE); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::subAH()
{
  regs.regA -= regs.regH;

  setFlag(2, 1, 3, 3, regs.regA, regs.regH); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::subAL()
{
  regs.regA -= regs.regL;

  setFlag(2, 1, 3, 3, regs.regA, regs.regL); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::subAA()
{
  regs.regA -= regs.regA;

  setFlag(2, 1, 3, 3, regs.regA, regs.regA); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::sbcAB()
{
  regs.regA -= regs.regB + regs.flagC;

  setFlag(2, 1, 3, 3, regs.regA, regs.regB + regs.flagC); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::sbcAC()
{
  regs.regA -= regs.regC + regs.flagC;

  setFlag(2, 1, 3, 3, regs.regA, regs.regC + regs.flagC); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::sbcAD()
{
  regs.regA -= regs.regD + regs.flagC;

  setFlag(2, 1, 3, 3, regs.regA, regs.regD + regs.flagC); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::sbcAE()
{
  regs.regA -= regs.regE + regs.flagC;

  setFlag(2, 1, 3, 3, regs.regA, regs.regE + regs.flagC); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::sbcAH()
{
  regs.regA -= regs.regH + regs.flagC;

  setFlag(2, 1, 3, 3, regs.regA, regs.regH + regs.flagC); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::sbcAL()
{
  regs.regA -= regs.regL + regs.flagC;

  setFlag(2, 1, 3, 3, regs.regA, regs.regL + regs.flagC); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

void Cpu::sbcAA()
{
  regs.regA -= regs.regA + regs.flagC;

  setFlag(2, 1, 3, 3, regs.regA, regs.regA + regs.flagC); //"Z 1 H C"

  lastCycle = 4;
  regs.pc++;
}

/*
****************0xAx******************
*/

void Cpu::xorA()
{
  regs.regA = regs.regA ^ regs.regA;

  setFlag(2, 0, 0, 0, regs.regA, 1);
  lastCycle = 4;
  regs.pc++;
}