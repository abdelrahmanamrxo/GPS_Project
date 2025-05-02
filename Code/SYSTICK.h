#ifndef SYSTICK_H
#define SYSTICK_H

#include "tm4c123gh6pm.h"

void SysTick_Init(void);
void delay(unsigned int delay);
void SYSTICK_wait_1ms(void);

#endif
