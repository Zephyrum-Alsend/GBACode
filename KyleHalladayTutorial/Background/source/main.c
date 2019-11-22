#include "tiles.h"
#include <string.h>

typedef unsigned char      		uint8;
typedef unsigned short    		uint16;
typedef unsigned int          	uint32;
typedef uint16 Tile[32];
typedef Tile TileBlock[256];
typedef uint16 ScreenBlock[1024];


#define REG_DISPLAYCONTROL		*((volatile uint32*)(0x04000000))
#define REG_VCOUNT              (*(volatile uint16*) 0x04000006)
#define VIDEOMODE_0				0x0000
#define BACKGROUND_0   			0x0100
#define BACKGROUND_1   			0x0200
#define BACKGROUND_3   			0x0400
#define BACKGROUND_4   			0x0800
#define VIDEOMODE_3     	    0x0003
#define BGMODE_2 			    0x0400

#define REG_BG0_CONTROL        *((volatile uint16*)(0x04000008))
#define REG_BG1_CONTROL        *((volatile uint16*)(0x0400000A))
#define REG_BG2_CONTROL        *((volatile uint16*)(0x0400000C))
#define REG_BG3_CONTROL        *((volatile uint16*)(0x0400000E))

#define REG_BG0_SCROLL_H       *((volatile uint16*)(0x04000010))
#define REG_BG0_SCROLL_V       *((volatile uint16*)(0x04000012))
#define REG_BG1_SCROLL_H       *((volatile uint16*)(0x04000014))
#define REG_BG1_SCROLL_V       *((volatile uint16*)(0x04000016))
#define REG_BG2_SCROLL_H       *((volatile uint16*)(0x04000018))
#define REG_BG2_SCROLL_V       *((volatile uint16*)(0x0400001A))
#define REG_BG3_SCROLL_H       *((volatile uint16*)(0x0400001C))
#define REG_BG3_SCROLL_V       *((volatile uint16*)(0x0400001E))

#define MEM_BG_PALETTE    		((uint16*)(0x05000000))
#define MEM_OBJ_PALETTE   		((uint16*)(0x05000200))
#define MEM_VRAM                ((volatile uint32*)0x6000000)
#define MEM_TILE                ((TileBlock*)0x6000000)
#define MEM_SCREENBLOCKS        ((ScreenBlock*)0x6000000)

#define SCREENBUFFER            ((volatile uint16*)0x06000000)
#define SCREEN_W                240
#define SCREEN_H                160

void UploadPaletteMem();
void UploadTileMem();
void UploadScreenBlock();
inline uint16 MakeCol(uint32 red, uint32 green, uint32 blue);
void GenerateGradient();
void vsync();

int main()
{
	UploadPaletteMem();
	UploadTileMem();
	UploadScreenBlock();
	
	GenerateGradient();

	// Size 00, Screen Block 1, Color Mode 1, Tile Block 0, Depth 0
	REG_BG0_CONTROL = 0x0180; // 0000 0001 1000 0000
	// Size 01, Screen Block 2, Color Mode 1, Tile Block 1, Priority 1
	REG_BG1_CONTROL = 0x4285; // 0100 0010 1000 0101

    REG_DISPLAYCONTROL = VIDEOMODE_0 | BACKGROUND_0 | BACKGROUND_1;

	int hScroll = 0;
	int h2Scroll = 0;
    while(1)
	{
		vsync();
		
		REG_BG0_SCROLL_H = -hScroll;
		REG_BG1_SCROLL_H = h2Scroll;
		h2Scroll += 2;
		hScroll = h2Scroll/3;
	}
    return 0;
}   





void UploadPaletteMem()
{
    memcpy(MEM_BG_PALETTE, bgPal, bgPalLen);
}

void UploadTileMem()
{
    memcpy(&MEM_TILE[0][0], bgTiles, bgTilesLen);
}

// It's up to us to be sure the screen blocks and tile sets don't overwrite each other in memory.
void UploadScreenBlock()
{
    //checkerBg is the ScreenBlock data from the gist
    memcpy(&MEM_SCREENBLOCKS[1], checkerBg, checkerBgLen);
}

inline uint16 MakeCol(uint32 red, uint32 green, uint32 blue)
{
    return red | (green<<5) | (blue<<10);
}

void GenerateGradient()
{
    //we've uploaded 4 colours to palette memory
    //so make sure we don't overwrite those
    for (uint16 i = 0; i < 32; i++)
    {
        *((uint16*)(MEM_BG_PALETTE+(4+i))) = MakeCol(i,i,i);
    }

    //every tile is 64 palette indices
    //we have 32 grayscale values from above
    uint8 tile[64];
    for (uint16 i = 0; i < 32; ++i)
    {
        for (int j = 0; j < 64; j++)
        {
            tile[j] = 4 + (i);
        }
        memcpy(MEM_TILE[1][i], tile, 64);
    }

    //generate 2 screen blocks,
    //each gray value getting two tiles of width
    for (int block = 0; block < 2; ++block)
    {
        uint16 screenBlock[1024];

        //screen block data is row by row, top to bottom
        for (uint16 i = 0; i < 32; ++i)
        {
            for (uint16 j = 0; j < 32; ++j)
            {
                //each block gets 16 colours, 2 tiles wide for each
                screenBlock[i * 32 + j] =  (j/2) + (block*16);
            }
        }
        memcpy(MEM_SCREENBLOCKS[block+2], &screenBlock[0], 2048);
    }
}

void vsync()
{
	while(REG_VCOUNT >= 160);
	while(REG_VCOUNT < 160);
}