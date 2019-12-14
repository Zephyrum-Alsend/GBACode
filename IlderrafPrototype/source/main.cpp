#include "gba.h"
#include "input.h"
#include <string.h>

int main()
{
    REG_DISPLAYCONTROL = VIDEOMODE_3 | BACKGROUND_2;

	for (int i = 0; i < SCREEN_W * SCREEN_H; ++i)
	{
		SCREENBUFFER[i] = 0x0000;
	}

    while(1){}
    return 0;
}