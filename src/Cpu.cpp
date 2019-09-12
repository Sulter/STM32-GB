#include "../include/Cpu.h"

Cpu::Cpu() : opcodeMap{&Cpu::nop, &Cpu::nop}
{
  reset();
}

void Cpu::reset()
{
  //set stack pointer, program counter, and the registers to 0
  pc = sp = regA = regB = regC = regD = regE = regH = regL = 0;
  //set all the flags to 0
  flagZ = flagN = flagH = flagC = 0;
}

void Cpu::setFlag(int8_t zero, int8_t substract, int8_t halfCarry, int8_t carry, uint8_t a, uint8_t temp)
{
  //take care of zero-flag (7th bit)
  if (zero == 0)
    flagZ = 0; //clear Z flag
  else if (zero == 1)
    flagZ = 1; //set Z flag
  else if (zero == 2)
  {
    if (a == 0)
      flagZ = 1; //set Z flag
    else
      flagZ = 0; //clear Z flag
  }

  //take care of substract-flag (6th bit)
  if (substract == 0)
    flagN = 0; //clear sub flag
  else if (substract == 1)
    flagN = 1; //set sub flag

  //take care of half-carry-flag (and half borrow) (5th bit)
  if (halfCarry == 0)
    flagH = 0; //clear half-carry-flag
  else if (halfCarry == 1)
    flagH = 1;             //set the half-carry-flag
  else if (halfCarry == 2) //temp has been added to A
  {
    uint8_t aTemp = a;
    aTemp -= temp;
    if (((aTemp + temp) & 0xF) < (aTemp & 0xF))
      flagH = 1; //set half-carry-flag
    else
      flagH = 0; //clear the half-carry-flag
  }
  else if (halfCarry == 3) //temp has been substracted from A
  {
    uint8_t aTemp = a;
    aTemp += temp;
    if ((aTemp & 0xF) < ((aTemp - temp) & 0xF))
      flagH = 1; //set half-carry-flag
    else
      flagH = 0; //clear the half-carry-flag
  }

  /*
      C++ promotes uint8_t to int when using arithmetic operators.
      We can use this behaviour:
      By undoing the last operation, and checking if the value is bigger or smaller than 0, we know if an overflow has happend.
    */
  //take care of carry-flag (and borrow) (4th bit)
  if (carry == 0)
    flagC = 0; //clear carry flag
  else if (carry == 1)
    flagC = 1;         //set carry flag
  else if (carry == 2) //temp has been added to A
  {
    if (a - temp < 0)
      flagC = 1; //there is a carry!
    else
      flagC = 0; //there is no carry
  }
  else if (carry == 3) //temp has been substracted from A
  {
    if (a + temp > 255)
      flagC = 1; //there is a borrow!
    else
      flagC = 0; //no borrow
  }
}

void Cpu::setFlag(int8_t zero, int8_t substract, int8_t halfCarry, int8_t carry, uint16_t a, uint16_t temp)
{
  //take care of zero-flag (7th bit)
  if (zero == 0)
    flagZ = 0; //clear Z flag
  else if (zero == 1)
    flagZ = 1; //set Z flag
  else if (zero == 2)
  {
    if (a == 0)
      flagZ = 1; //set Z flag
    else
      flagZ = 0;
    ; //clear Z flag
  }

  //take care of substract-flag (6th bit)
  if (substract == 0)
    flagN = 0; //clear sub flag
  else if (substract == 1)
    flagN = 1; //set sub flag

  //take care of half-carry-flag (and half borrow) (5th bit)
  if (halfCarry == 0)
    flagH = 0; //clear half-carry-flag
  else if (halfCarry == 1)
    flagH = 1;             //set the half-carry-flag
  else if (halfCarry == 2) //temp has been added to A
  {
    uint16_t aTemp = a;
    aTemp -= temp;
    if (((aTemp + temp) & 0xFFF) < (aTemp & 0xFFF))
      flagH = 1; //set half-carry-flag
    else
      flagH = 0; //clear the half-carry-flag
  }
  else if (halfCarry == 3) //temp has been substracted from A
  {
    uint16_t aTemp = a;
    aTemp += temp;
    if ((aTemp & 0xFFF) < ((aTemp - temp) & 0xFFF))
      flagH = 1; //set half-carry-flag
    else
      flagH = 0; //clear the half-carry-flag
  }

  /*
      C++ promotes uint8_t to int when using arithmetic operators.
      We can use this behaviour:
      By undoing the last operation, and checking if the value is bigger or smaller than 0, we know if an overflow has happend.
    */
  //take care of carry-flag (and borrow) (4th bit)
  if (carry == 0)
    flagC = 0; //clear carry flag
  else if (carry == 1)
    flagC = 1;         //set carry flag
  else if (carry == 2) //temp has been added to A
  {
    if (a - temp < 0)
      flagC = 1; //there is a carry!
    else
      flagC = 0; //there is no carry
  }
  else if (carry == 3) //temp has been substracted from A
  {
    if (a + temp > 0xffff)
      flagC = 1; //there is a borrow!
    else
      flagC = 0; //no borrow
  }
}
