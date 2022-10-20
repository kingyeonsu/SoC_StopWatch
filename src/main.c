/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
#include "main.h"

#define TICK_GENERATOR_DEV_BASE_ADDR	0x44A00000
#define TICK_DATA_REG	*(uint32_t *) TICK_GENERATOR_DEV_BASE_ADDR

#define FND_CONTROLLER_DEV_BASE_ADDR	0x44A10000
#define FND_CONTROL_REG	*(uint32_t *) (FND_CONTROLLER_DEV_BASE_ADDR + 0)
#define FND_DATA_REG	*(uint32_t *) (FND_CONTROLLER_DEV_BASE_ADDR + 4)

#define IDLE	0
#define RUN		0
#define CLEAR	1
#define OFF		2

int main()
{
    init_platform();
    LedInit();
	ButtonInit();

	LedInst runLed;
	LedInst clearLed;
	LedInst powerLed;

	Led_MakeInst(&runLed, LED_0);
	Led_MakeInst(&clearLed, LED_1);
	Led_MakeInst(&powerLed, LED_2);

	ButtonInst runButton;
	ButtonInst clearButton;
	ButtonInst powerButton;

	Button_MakeInstance(&runButton, BUTTON_0);
	Button_MakeInstance(&clearButton, BUTTON_1);
	Button_MakeInstance(&powerButton, BUTTON_2);

	FND_CONTROL_REG = RUN;
	uint32_t prevFndCounterTick = IDLE;
	int counter = IDLE;

	Led_On(&runLed);

	while (1)
	{
		if (TICK_DATA_REG - prevFndCounterTick > 100)
		{
			prevFndCounterTick = TICK_DATA_REG;
			FND_DATA_REG = counter++;
		}

		if (GetButtonState(&runButton))
		{
			FND_CONTROL_REG = RUN;
			Led_On(&runLed);
			Led_Off(&clearLed);
			Led_Off(&powerLed);
		}
		else if (GetButtonState(&clearButton))
		{
			FND_CONTROL_REG = CLEAR;
			Led_Off(&runLed);
			Led_On(&clearLed);
			Led_Off(&powerLed);
		}
		else if (GetButtonState(&powerButton))
		{
			FND_CONTROL_REG = OFF;
			Led_Off(&runLed);
			Led_Off(&clearLed);
			Led_On(&powerLed);
		}
	}
	cleanup_platform();
    return 0;
}
