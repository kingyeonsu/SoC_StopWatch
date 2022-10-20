/*
 * led.h
 *
 *  Created on: 2022. 10. 19.
 *      Author: kccistc
 */

#ifndef SRC_HW_LED_H_
#define SRC_HW_LED_H_

#include "xparameters.h"
#include "xgpio.h"

#define LED_0	0
#define LED_1	1
#define LED_2	2
#define LED_3	3

typedef struct _ledInst
{
	int ledNum;
}LedInst;


#define CHANNEL_1	1
#define OUTPUT		0


void Led_MakeInst(LedInst *led, int ledNum);
void LedInit();
void Led_On(LedInst *led);
void Led_Off(LedInst *led);
void Led_Toggle(LedInst *led);

#endif /* SRC_HW_LED_H_ */
