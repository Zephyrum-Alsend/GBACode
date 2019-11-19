#include "sprite.h"
#include <string.h>

typedef unsigned char      		uint8;
typedef unsigned short    		uint16;
typedef unsigned int          	uint32;

typedef uint32 Tile[16];
typedef Tile TileBlock[256];

typedef struct ObjectAttributes {
    uint16 attr0;
    uint16 attr1;
    uint16 attr2;
    uint16 pad;
} __attribute__((packed, aligned(4))) ObjectAttributes;

#define REG_DISPLAYCONTROL		*((volatile uint32*)(0x04000000))
#define REG_VCOUNT              (*(volatile uint16*) 0x04000006)
#define VIDEOMODE_3     	    0x0003
#define VIDEOMODE_0    			0x0000
#define BGMODE_2 			    0x0400
#define ENABLE_OBJECTS 			0x1000
#define MAPPINGMODE_1D 			0x0040

#define MEM_PALETTE   			((uint16*)(0x05000200))
#define MEM_VRAM        		((volatile uint32*)0x06000000)
#define MEM_TILE        		( (TileBlock*)MEM_VRAM )
#define MEM_OAM  				((volatile ObjectAttributes *)0x07000000)

#define SCREENBUFFER            ((volatile uint16*)0x06000000)
#define SCREEN_W                240
#define SCREEN_H                160

inline void vsync();
void UploadPaletteMem();
void UploadTileMem();

int main()
{
    REG_DISPLAYCONTROL =  VIDEOMODE_0 | ENABLE_OBJECTS | MAPPINGMODE_1D;
	
	memcpy(MEM_PALETTE, spritePal,  spritePalLen );
    memcpy(&MEM_TILE[4][1], spriteTiles, spriteTilesLen);
	
	volatile ObjectAttributes *spriteAttribs = &MEM_OAM[0];

	spriteAttribs->attr0 = 0x2032; // 8bpp tiles, SQUARE shape
	spriteAttribs->attr1 = 0x4064; // 16x16 size when using the SQUARE shape
	spriteAttribs->attr2 = 2;      // Start at [4][1]

    int x = 0;
    while(1)
    {
        vsync();
        x = (x+1) % (SCREEN_W);
        spriteAttribs->attr1 = 0x4000 | (0x1FF & x);

    }
    return 0;
}





inline void vsync()
{
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);
}

void UploadPaletteMem()
{
    memcpy(MEM_PALETTE, spritePal, spritePalLen);
	// MEM_PALETTE is usually called MEM_OBJ_PAL because palette memory is divided into 2 sections, but we're using only 1 here so for simplicity...
}

void UploadTileMem()
{
    memcpy(&MEM_TILE[4][1], spriteTiles, spriteTilesLen);
}