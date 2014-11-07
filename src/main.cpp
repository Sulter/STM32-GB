#include "../include/Cpu.h"
#include <iostream>
#include <cstdint>
#include <cstdio>

int main()
{
    uint8_t a,b;
    a= 200;
    b= 57;
    //detect overflow
    if(a+b>255)
	printf("overflow\n");
    if(a-b<0)
	printf("underflow\n");


    Cpu myCpu;
    return 0;
}
