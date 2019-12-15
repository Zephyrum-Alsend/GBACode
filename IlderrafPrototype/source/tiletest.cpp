#include "tiletest.h"

void LoadTileData()
{
    //each letter is 32 tiles
    memcpy(MEM_PALETTE, Pal,  PalLen );
    memcpy(&MEM_TILE[4][0], ATiles, TileLen);
    memcpy(&MEM_TILE[4][32], BTiles, TileLen);
    memcpy(&MEM_TILE[4][64], SelectTiles, TileLen);
    memcpy(&MEM_TILE[4][96], StartTiles, TileLen);
    memcpy(&MEM_TILE[4][128], RIGHTTiles, TileLen);
    memcpy(&MEM_TILE[4][160], LEFTTiles, TileLen);
    memcpy(&MEM_TILE[4][192], UPTiles, TileLen);
    memcpy(&MEM_TILE[4][224], DOWNTiles, TileLen);
    memcpy(&MEM_TILE[5][0], LTiles, TileLen);
    memcpy(&MEM_TILE[5][32], RTiles, TileLen);

    volatile ObjectAttributes *spriteAttribs = &MEM_OAM[0];

    spriteAttribs->attr0 = 0x602F;
    spriteAttribs->attr1 = 0xC04F;
    spriteAttribs->attr2 = 0;
}
void ClearSprite()
{
    volatile ObjectAttributes *spriteAttribs = &MEM_OAM[0];
    spriteAttribs->attr0 = 0x60AF;
    MEM_BG_PALETTE[0] = 0;

}

void DrawSprite(uint16 key_code)
{
    const uint16 keys[] = {KEY_A, KEY_B, KEY_SELECT, KEY_START, KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN, KEY_L, KEY_R};
    const uint16 bgCols[] = {RGB15(16,0,0), RGB15(0,16,0), RGB15(0,0,16),RGB15(16,16,0),RGB15(16,16,16),RGB15(32,16,0),RGB15(32,0,16),RGB15(16,0,32),RGB15(16,32,0),RGB15(32,0,32)};

    int idx = 0;
    for (int i = 0; i < 10; ++i)
    {
        if (keys[i] == key_code)
        {
            idx = i;
            break;
        }
    }

    volatile ObjectAttributes *spriteAttribs = &MEM_OAM[0];
    spriteAttribs->attr0 = 0x602F;
    spriteAttribs->attr1 = 0xC04F;
    spriteAttribs->attr2 = idx * 32 * 2;

    MEM_BG_PALETTE[0] = bgCols[idx];

}

void CreateBackground()
{
    MEM_BG_PALETTE[0] = RGB15(0,0,0);

    uint8 tile[64];
    for (int j = 0; j < 64; j++)
    {
        tile[j] = 0;
    }
    memcpy(MEM_TILE[0][0], tile, 64);

    uint16 screenBlock[1024];
    for (int i = 0; i < 1024; i++)
    {
        screenBlock[i] = 0;
    }

    memcpy(MEM_SCREENBLOCKS[1], &screenBlock[0], 2048);

    REG_BG0_CONTROL = 0x0180;

}

void TileTest()
{
    Controls c;

    CreateBackground();
    LoadTileData();
    uint8 buttons_pressed[10] = {0,0,0,0,0,0,0,0,0,0};

    REG_DISPLAYCONTROL =  VIDEOMODE_0 | ENABLE_OBJECTS | BACKGROUND_0 | MAPPINGMODE_1D;
    c.UpdateActions();
    ClearSprite();

    const uint16 keys[] = {KEY_A, KEY_B, KEY_L, KEY_R, KEY_SELECT, 
                                KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_START};

    while(1)
    {
        vsync();
        c.UpdateActions();
        c.GetActions(buttons_pressed);

        for (int i = 0; i < 10; ++i)
        {
            if (buttons_pressed[i] == 1)
            {
                DrawSprite(keys[i]);
            }
        }
    }
}