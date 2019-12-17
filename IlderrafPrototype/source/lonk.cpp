#include "lonk.h"

Lonk::Lonk(bool PC)
{
    ISPC = PC;

    // Put our sprite data into VRAM
    memcpy(&MEM_TILE[4][0], HeroTiles, HeroTilesLen);
    memcpy(MEM_PALETTE, HeroPal, HeroPalLen);

    InitializeSprite(&SPRITE, &OAM_BACKBUFFER[0]);
    
    // Dimensions are determined by size of sprite
    LENX = 16;
    LENY = 16;

    // Set modifiable stats
    HP = MAXHP;
    SP = MAXSP;
}

void Lonk::InitializeSprite(CharSprite* sprite, ObjectAttributes* attribs)
{
    sprite->spriteAttribs = attribs;
    sprite->facingRight = 1;
    sprite->firstAnimCycleFrame = 0;
    sprite->animFrame = 0;
    sprite->posX = 0;
    sprite->posY = SCREEN_H - LENY;
    sprite->velX = 0;
    sprite->velY = 0;
}

void Lonk::ExecuteAction(uint8 AM[10])
{
    if (ISPC)
    {
        // Check if START was pressed
        if(AM[9] == 1)
        {
            // Open menu
        }

        // Check movement
        int speed;
        if(ISDSH) {speed = SPD*DSHMULT;}
        else {speed = SPD;}

        ISMOV = false;
        if(AM[5] == 1)
        {
            // Move UP
            SPRITE.velY = -speed;
            ISMOV = true;
        }
        if(AM[6] == 1)
        {
            // Move DOWN
            SPRITE.velY = speed;
            ISMOV = true;
        }
        if(AM[7] == 1)
        {
            // Move LEFT
            SPRITE.facingRight = 0;
            SPRITE.velX = -speed;
            ISMOV = true;
        }
        if(AM[8] == 1)
        {
            // Move RIGHT
            SPRITE.facingRight = 1;
            SPRITE.velX = speed;
            ISMOV = true;
        }
        if(!ISMOV)
        {
            // Make sure we stop when the button is released!
            SPRITE.velX = 0;
            SPRITE.velY = 0;
        }

        // Check which actions are to be performed
        
        // Toggle ability
        if(AM[0] == 1)
        {
            // Action 1
        }
        else if(AM[0] == 2)
        {
            // Action 2
        }
        
        // Attack
        if(AM[1] == 1)
        {
            // Action 3
        }
        else if(AM[1] == 2)
        {
            // Action 4
        }
        
        // Heal/Dash
        if(AM[2] == 1)
        {
            // Action 5
            if (ISMOV)
            {
                ISDSH = true;
            }
            else
            {
                // Heal code here
            }
        }
        else if(AM[2] == 2)
        {
            // Action 6
            ISDSH = false;

            // Terminate healing, if active
        }
        
        // Change element
        if(AM[3] == 1)
        {
            // Action 7
        }
        else if(AM[3] == 2)
        {
            // Action 8
        }
        
        // Emote toggle
        if(AM[4] == 1)
        {
            // Action 9
        }
        else if(AM[4] == 2)
        {
            // Action 10
        }

        
    }
    else
    {
        // Run AI package
    }
    
    UpdateSpritePosition(&SPRITE);
    TickSpriteAnimation(&SPRITE);

    MEM_OAM[0] = OAM_BACKBUFFER[0];
}

void Lonk::UpdateSpritePosition(CharSprite* sprite)
{
    sprite->posX += sprite->velX;
    sprite->posX = min((SCREEN_W - LENX), sprite->posX);
    sprite->posX = max(sprite->posX, 0);

    sprite->posY += sprite->velY;
    sprite->posY = min(sprite->posY, (SCREEN_H - LENY));
    sprite->posY = max(sprite->posY, 0);

    sprite->spriteAttribs->attr0 = 0x2000 + sprite->posY;
    sprite->spriteAttribs->attr1 = (sprite->facingRight? 0x4000 : 0x5000) + sprite->posX;
}

void Lonk::TickSpriteAnimation(CharSprite* sprite)
{
    ObjectAttributes* spriteAttribs = sprite->spriteAttribs;

    if (sprite->velX != 0)
    {
        sprite->firstAnimCycleFrame = 32;
        sprite->animFrame = (++sprite->animFrame) % 3;

    }
    else
    {
        sprite->firstAnimCycleFrame = 0;
        sprite->animFrame = (++sprite->animFrame) % 4;
    }

    spriteAttribs->attr2 = sprite->firstAnimCycleFrame + (sprite->animFrame * 8);    

}
