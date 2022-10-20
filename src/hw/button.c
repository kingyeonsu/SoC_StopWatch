#include "button.h"

XGpio	GPIO_BUTTON;

void ButtonInit()
{
	XGpio_Initialize(&GPIO_BUTTON, XPAR_AXI_GPIO_1_DEVICE_ID);
	XGpio_SetDataDirection(&GPIO_BUTTON, CHANNEL_1, 0x0f);
}


void Button_MakeInstance(ButtonInst* button, int buttonNum)
{
	button->prevState = RELEASED;
	button->buttonNum = buttonNum;
}

int GetButtonState(ButtonInst* button)
{
	int curState = XGpio_DiscreteRead(&GPIO_BUTTON, CHANNEL_1) & (1<<button->buttonNum);

	if ((curState != RELEASED) && (button->prevState == RELEASED))
	{
		usleep(20000);
		button->prevState = PUSHED;
		return FALSE;
	}
	else if ((curState == RELEASED) && (button->prevState != RELEASED))
	{
		usleep(20000);
		button->prevState = RELEASED;
		return TRUE;
	}
	return FALSE;
}
