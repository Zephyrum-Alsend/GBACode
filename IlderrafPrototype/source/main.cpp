#include "gba.h"
#include <string.h>
#include "TileTest.h"
#include "controls.h"
using namespace std;

int main()
{
	TileTest();
    // REG_DISPLAYCONTROL = VIDEOMODE_3 | BACKGROUND_2;

	// for (int i = 0; i < SCREEN_W * SCREEN_H; ++i)
	// {
	// 	SCREENBUFFER[i] = 0x0000;
	// }

	// Controls c;
	// c.UpdateActions();
	// uint8 actions[10];
    // while(1)
	// {
	// 	vsync();
	// 	c.UpdateActions();
	// 	c.GetActions(actions);

	// 	for (int i = 0; i < 10; ++i)
	// 	{
	// 		if(actions[i])
	// 		{
	// 			for (int j = 0; j < SCREEN_W * SCREEN_H; ++j)
	// 			{
	// 				SCREENBUFFER[j] = 0x0000 + i*100;
	// 			}
	// 		}
	// 	}
	// }
    // return 0;
}