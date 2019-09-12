#include "../include/Cpu.h"
#include <cstdint>
#include <cstdio>

void Cpu::nop()
{
  lastCycle = 4;
  pc++;
  printf("\nNop");
}

void Cpu::ldBCnn()
{
  regC = MMU.readByte(pc + 1);
  regB = MMU.readByte(pc + 2);
  lastCycle = 12;
  pc += 3;
}

void Cpu::ldBCA()
{
  MMU.writeByte((regB << 8) | regC, regA);
  lastCycle = 8;
  pc++;
}

void Cpu::incBC()
{
  regC++;
  if (!regC)
    regB++;

  lastCycle = 8;
  pc++;
}

void Cpu::incB()
{
  regB++; //increase the register

  setFlag(2, 0, 2, -1, regB, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::decB()
{
  regB--; //decrease the register

  setFlag(2, 1, 3, -1, regB, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::ldBn()
{
  regB = MMU.readByte(pc + 1);
  lastCycle = 8;
  pc += 2;
}

void Cpu::rlcA()
{
  uint8_t temp = regA & (0x80);
  regA <<= 1;
  regA |= temp >> 7;
  setFlag(0, 0, 0, 3, temp, 0xff);

  lastCycle = 4;
  pc++;

  printf("\nregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n", regA, pc, flagZ, flagN, flagH, flagC);
}

void Cpu::ldnnSP()
{
  uint16_t address = (MMU.readByte(pc + 1) << 8) | MMU.readByte(pc + 2);
  MMU.writeByte(address, sp & 0xff);
  MMU.writeByte(address + 1, (sp >> 8) & 0xff);
  lastCycle = 20;
  pc += 3;
}

void Cpu::addHLBC()
{
  uint16_t total = ((regH << 8) | regL) + ((regB << 8) | regC);
  regH = total >> 8;
  regL = total & 0xff;
  setFlag(-1, 0, 2, 2, ((regH << 8) | regL), (uint16_t)((regB << 8) | regC)); //"- 0 H C"

  lastCycle = 8;
  pc++;
}

void Cpu::ldABC()
{
  regA = MMU.readByte((regB << 8) | regC);

  lastCycle = 8;
  pc++;
}

void Cpu::decBC()
{
  if (!regC)
  {
    regB--;
  }
  regC--;

  lastCycle = 8;
  pc++;
}

void Cpu::incC()
{
  regC++; //increase the register

  setFlag(2, 0, 2, -1, regC, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::decC()
{
  regC--; //decrease the register

  setFlag(2, 1, 3, -1, regC, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::ldCn()
{
  regC = MMU.readByte(pc + 1);

  lastCycle = 8;
  pc += 2;
}

void Cpu::rrcA()
{
  printf("\nbefore operation regA: %d", regA);
  uint8_t temp = regA & (0x01);
  regA >>= 1;
  regA |= temp << 7;
  printf("\ntemp is: %d", temp);
  setFlag(0, 0, 0, 3, 0xff, temp);

  lastCycle = 4;
  pc++;

  printf("\nregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n", regA, pc, flagZ, flagN, flagH, flagC);
}

/*
****************0x1x******************
*/

void Cpu::ldDEnn()
{
  regE = MMU.readByte(pc + 1);
  regD = MMU.readByte(pc + 2);
  lastCycle = 12;
  pc += 3;
}

void Cpu::ldDEA()
{
  MMU.writeByte((regD << 8) | regE, regA);
  lastCycle = 8;
  pc++;
}

void Cpu::incDE()
{
  regE++;
  if (!regE)
    regD++;

  lastCycle = 8;
  pc++;

  uint16_t test = (regD << 8) | regE;
  printf("DE: %d\n", test);
}

void Cpu::incD()
{
  regD++; //increase the register

  setFlag(2, 0, 2, -1, regD, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::decD()
{
  regD--; //decrease the register

  setFlag(2, 1, 3, -1, regD, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::ldDn()
{
  regD = MMU.readByte(pc + 1);
  lastCycle = 8;
  pc += 2;
}

void Cpu::rlA()
{
  uint8_t temp = regA & (0x80);
  regA <<= 1;
  regA |= flagC;
  setFlag(0, 0, 0, 3, temp, 0xff);

  lastCycle = 4;
  pc++;

  printf("\nregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n", regA, pc, flagZ, flagN, flagH, flagC);
}

void Cpu::jrn()
{
  pc = pc + MMU.readByte(pc + 1);
  lastCycle = 12;
}

void Cpu::addHLDE()
{
  uint16_t total = ((regH << 8) | regL) + ((regD << 8) | regE);
  regH = total >> 8;
  regL = total & 0xff;
  setFlag(-1, 0, 2, 2, ((regH << 8) | regL), (uint16_t)((regD << 8) | regE)); //"- 0 H C"

  lastCycle = 8;
  pc++;
}

void Cpu::ldADE()
{
  regA = MMU.readByte((regD << 8) | regE);

  lastCycle = 8;
  pc++;
}

void Cpu::decDE()
{
  if (!regE)
  {
    regD--;
  }
  regE--;

  lastCycle = 8;
  pc++;
}

void Cpu::incE()
{
  regE++; //increase the register

  setFlag(2, 0, 2, -1, regE, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::decE()
{
  regE--; //decrease the register

  setFlag(2, 1, 3, -1, regE, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::ldEn()
{
  regE = MMU.readByte(pc + 1);

  lastCycle = 8;
  pc += 2;
}

void Cpu::rrA()
{
  uint8_t temp = regA & (0x01);
  regA >>= 1;
  regA |= flagC << 7;
  setFlag(0, 0, 0, 3, temp, 0xff);

  lastCycle = 4;
  pc++;

  printf("\nregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n", regA, pc, flagZ, flagN, flagH, flagC);
}

/*
****************0x2x******************
*/

void Cpu::ldHLnn()
{
  regL = MMU.readByte(pc + 1);
  regH = MMU.readByte(pc + 2);
  lastCycle = 12;
  pc += 3;
}

void Cpu::ldiHLA()
{
  MMU.writeByte((regH << 8) | regL, regA);

  regL++;
  if (!regL)
    regH++;

  lastCycle = 8;
  pc++;
}

void Cpu::incHL()
{
  regL++;
  if (!regL)
    regH++;

  lastCycle = 8;
  pc++;
}

void Cpu::incH()
{
  regH++; //increase the register

  setFlag(2, 0, 2, -1, regH, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::decH()
{
  regH--; //decrease the register

  setFlag(2, 1, 3, -1, regH, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::ldHn()
{
  regH = MMU.readByte(pc + 1);
  lastCycle = 8;
  pc += 2;
}

void Cpu::addHLHL()
{
  uint16_t total = ((regH << 8) | regL) + ((regH << 8) | regL);
  regH = total >> 8;
  regL = total & 0xff;
  setFlag(-1, 0, 2, 2, ((regH << 8) | regL), (uint16_t)((regH << 8) | regL)); //"- 0 H C"

  lastCycle = 8;
  pc++;
}

void Cpu::incL()
{
  regL++; //increase the register

  setFlag(2, 0, 2, -1, regL, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::decL()
{
  regL--; //decrease the register

  setFlag(2, 1, 3, -1, regL, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::cpl()
{
  regA = ~regA;
  setFlag(-1, 1, 1, -1, 0, (uint8_t)0); //"- 1 1 -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

/*
****************0x3x******************
*/

void Cpu::incSP()
{
  sp++;

  pc++;
  lastCycle = 8;
}

void Cpu::scf()
{
  flagC = 1;

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::decSP()
{
  sp--;

  pc++;
  lastCycle = 8;
}

void Cpu::incA()
{
  regA++; //increase the register

  setFlag(2, 0, 2, -1, regA, 1); //"Z 0 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc

  //    printf("\nINCregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n",regA, pc, flagZ, flagN, flagH, flagC);
}

void Cpu::decA()
{
  regA--; //decrease the register

  setFlag(2, 1, 3, -1, regA, 1); //"Z 1 H -"

  lastCycle = 4; //add number of cycles
  pc++;          //increase the program pc
}

void Cpu::ccf()
{
  flagC = ~flagC;
  flagC &= 0x01;
  lastCycle = 4;
  pc++;
}

/*
****************0x4x******************
*/

void Cpu::ldBB()
{
  lastCycle = 4;
  pc++;
}
void Cpu::ldBC()
{
  regB = regC;
  lastCycle = 4;
  pc++;
}
void Cpu::ldBD()
{
  regB = regD;
  lastCycle = 4;
  pc++;
}
void Cpu::ldBE()
{
  regB = regE;
  lastCycle = 4;
  pc++;
}
void Cpu::ldBH()
{
  regB = regH;
  lastCycle = 4;
  pc++;
}
void Cpu::ldBL()
{
  regB = regL;
  lastCycle = 4;
  pc++;
}
void Cpu::ldBA()
{
  regB = regA;
  lastCycle = 4;
  pc++;
}

void Cpu::ldCB()
{
  regC = regB;
  lastCycle = 4;
  pc++;
}
void Cpu::ldCC()
{
  lastCycle = 4;
  pc++;
}
void Cpu::ldCD()
{
  regC = regD;
  lastCycle = 4;
  pc++;
}
void Cpu::ldCE()
{
  regC = regE;
  lastCycle = 4;
  pc++;
}
void Cpu::ldCH()
{
  regC = regH;
  lastCycle = 4;
  pc++;
}
void Cpu::ldCL()
{
  regC = regL;
  lastCycle = 4;
  pc++;
}
void Cpu::ldCA()
{
  regC = regA;
  lastCycle = 4;
  pc++;
}

/*
****************0x5x******************
*/

void Cpu::ldDB()
{
  regD = regB;
  lastCycle = 4;
  pc++;
}
void Cpu::ldDC()
{
  regD = regC;
  lastCycle = 4;
  pc++;
}
void Cpu::ldDD()
{
  lastCycle = 4;
  pc++;
}
void Cpu::ldDE()
{
  regD = regE;
  lastCycle = 4;
  pc++;
}
void Cpu::ldDH()
{
  regD = regH;
  lastCycle = 4;
  pc++;
}
void Cpu::ldDL()
{
  regD = regL;
  lastCycle = 4;
  pc++;
}
void Cpu::ldDA()
{
  regD = regA;
  lastCycle = 4;
  pc++;
}

void Cpu::ldEB()
{
  regE = regB;
  lastCycle = 4;
  pc++;
}
void Cpu::ldEC()
{
  regE = regC;
  lastCycle = 4;
  pc++;
}
void Cpu::ldED()
{
  regE = regD;
  lastCycle = 4;
  pc++;
}
void Cpu::ldEE()
{
  lastCycle = 4;
  pc++;
}
void Cpu::ldEH()
{
  regE = regH;
  lastCycle = 4;
  pc++;
}
void Cpu::ldEL()
{
  regE = regL;
  lastCycle = 4;
  pc++;
}
void Cpu::ldEA()
{
  regE = regA;
  lastCycle = 4;
  pc++;
}

/*
****************0x6x******************
*/

void Cpu::ldHB()
{
  regH = regB;
  lastCycle = 4;
  pc++;
}
void Cpu::ldHC()
{
  regH = regC;
  lastCycle = 4;
  pc++;
}
void Cpu::ldHD()
{
  regH = regD;
  lastCycle = 4;
  pc++;
}
void Cpu::ldHE()
{
  regH = regE;
  lastCycle = 4;
  pc++;
}
void Cpu::ldHH()
{
  lastCycle = 4;
  pc++;
}
void Cpu::ldHL()
{
  regH = regL;
  lastCycle = 4;
  pc++;
}
void Cpu::ldHA()
{
  regH = regA;
  lastCycle = 4;
  pc++;
}

void Cpu::ldLB()
{
  regL = regB;
  lastCycle = 4;
  pc++;
}
void Cpu::ldLC()
{
  regL = regC;
  lastCycle = 4;
  pc++;
}
void Cpu::ldLD()
{
  regL = regD;
  lastCycle = 4;
  pc++;
}
void Cpu::ldLE()
{
  regL = regE;
  lastCycle = 4;
  pc++;
}
void Cpu::ldLH()
{
  regL = regH;
  lastCycle = 4;
  pc++;
}
void Cpu::ldLL()
{
  lastCycle = 4;
  pc++;
}
void Cpu::ldLA()
{
  regL = regA;
  lastCycle = 4;
  pc++;
}

/*
****************0x7x******************
*/

void Cpu::ldAB()
{
  regA = regB;
  lastCycle = 4;
  pc++;
}
void Cpu::ldAC()
{
  regA = regC;
  lastCycle = 4;
  pc++;
}
void Cpu::ldAD()
{
  regA = regD;
  lastCycle = 4;
  pc++;
}
void Cpu::ldAE()
{
  regA = regE;
  lastCycle = 4;
  pc++;
}
void Cpu::ldAH()
{
  regA = regH;
  lastCycle = 4;
  pc++;
}
void Cpu::ldAL()
{
  regA = regL;
  lastCycle = 4;
  pc++;
}
void Cpu::ldAA()
{
  lastCycle = 4;
  pc++;
}

/*
****************0x8x******************
*/

void Cpu::addAB()
{
  regA += regB;

  setFlag(2, 0, 2, 2, regA, regB); //"Z 0 H C"

  lastCycle = 4;
  pc++;

  printf("\nregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n", regA, pc, flagZ, flagN, flagH, flagC);
}

void Cpu::addAC()
{
  regA += regC;

  setFlag(2, 0, 2, 2, regA, regC); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::addAD()
{
  regA += regD;

  setFlag(2, 0, 2, 2, regA, regD); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::addAE()
{
  regA += regE;

  setFlag(2, 0, 2, 2, regA, regE); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::addAH()
{
  regA += regH;

  setFlag(2, 0, 2, 2, regA, regH); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::addAL()
{
  regA += regL;

  setFlag(2, 0, 2, 2, regA, regL); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::addAA()
{
  regA += regA;

  setFlag(2, 0, 2, 2, regA, regA); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::adcAB()
{
  regA += regB + flagC;

  setFlag(2, 0, 2, 2, regA, regB + flagC); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::adcAC()
{
  regA += regC + flagC;

  setFlag(2, 0, 2, 2, regA, regC + flagC); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::adcAD()
{
  regA += regD + flagC;

  setFlag(2, 0, 2, 2, regA, regD + flagC); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::adcAE()
{
  regA += regE + flagC;

  setFlag(2, 0, 2, 2, regA, regE + flagC); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::adcAH()
{
  regA += regH + flagC;

  setFlag(2, 0, 2, 2, regA, regH + flagC); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::adcAL()
{
  regA += regL + flagC;

  setFlag(2, 0, 2, 2, regA, regL + flagC); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::adcAA()
{
  regA += regA + flagC;

  setFlag(2, 0, 2, 2, regA, regA + flagC); //"Z 0 H C"

  lastCycle = 4;
  pc++;
}

/*
****************0x9x******************
*/

void Cpu::subAB()
{
  regA -= regB;

  setFlag(2, 1, 3, 3, regA, regB); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::subAC()
{
  regA -= regC;

  setFlag(2, 1, 3, 3, regA, regC); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::subAD()
{
  regA -= regD;

  setFlag(2, 1, 3, 3, regA, regD); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::subAE()
{
  regA -= regE;

  setFlag(2, 1, 3, 3, regA, regE); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::subAH()
{
  regA -= regH;

  setFlag(2, 1, 3, 3, regA, regH); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::subAL()
{
  regA -= regL;

  setFlag(2, 1, 3, 3, regA, regL); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::subAA()
{
  regA -= regA;

  setFlag(2, 1, 3, 3, regA, regA); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::sbcAB()
{
  regA -= regB + flagC;

  setFlag(2, 1, 3, 3, regA, regB + flagC); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::sbcAC()
{
  regA -= regC + flagC;

  setFlag(2, 1, 3, 3, regA, regC + flagC); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::sbcAD()
{
  regA -= regD + flagC;

  setFlag(2, 1, 3, 3, regA, regD + flagC); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::sbcAE()
{
  regA -= regE + flagC;

  setFlag(2, 1, 3, 3, regA, regE + flagC); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::sbcAH()
{
  regA -= regH + flagC;

  setFlag(2, 1, 3, 3, regA, regH + flagC); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::sbcAL()
{
  regA -= regL + flagC;

  setFlag(2, 1, 3, 3, regA, regL + flagC); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

void Cpu::sbcAA()
{
  regA -= regA + flagC;

  setFlag(2, 1, 3, 3, regA, regA + flagC); //"Z 1 H C"

  lastCycle = 4;
  pc++;
}

/*
****************0xAx******************
*/
