#include "../platform.h"
#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

#define CHANNEL_1	1

#define PUSHED		1
#define RELEASED	0
#define BUTTON_0	0
#define BUTTON_1	1
#define BUTTON_2	2
#define BUTTON_3	3

typedef struct _buttonInst{
	int prevState;
	int buttonNum;
}ButtonInst;


void ButtonInit();
void Button_MakeInstance(ButtonInst* button, int buttonNum);
int GetButtonState(ButtonInst* button);

