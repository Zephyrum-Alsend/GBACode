#include "gba.h"
#include "TileTest.h"
#include "controls.h"
#include "input.h"
#include "lonk.h"



int main()
{
    // Function for testing input, does not exit
	//TileTest();

    Controls inpu;

	REG_DISPLAYCONTROL =  VIDEOMODE_0 | BACKGROUND_0 | ENABLE_OBJECTS | MAPPINGMODE_1D;
	uint8 action_map[10];

	Lonk hero(true);

	while(1)
	{
		vsync();
		
		inpu.UpdateActions();
		inpu.GetActions(action_map);

		hero.ExecuteAction(action_map);
	}

	// Never ever reach here, because there is NOTHING to return to. No OS, only BIOS.
	return 0;
}