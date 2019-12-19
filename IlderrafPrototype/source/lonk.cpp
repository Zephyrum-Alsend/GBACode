#include "lonk.h"

/**/
/*
Lonk::Lonk()

NAME

Lonk::Lonk - class constructor.

SYNOPSIS

Lonk::Lonk(uint32* clck, bool PC = false);
clck                 --> the global clock, measuring time in frames.
PC                  --> controlled by the player or by AI

DESCRIPTION

This function initializes the character Lonk, loading it's
animations into VRAM, initializing it's own sprite and values.

RETURNS

Returns nothing.

AUTHOR

Lucas Crockett

DATE

16/12/2019

*/
/**/
Lonk::Lonk(uint32* clck, bool PC)
{
    ISPC = PC;
    CLOCK = clck;

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

/**/
/*
Lonk::InitializeSprite()

NAME

Lonk::InitializeSprite - initializes sprite data.

SYNOPSIS

Lonk::InitializeSprite(CharSprite* sprite, ObjectAttributes* attribs);
sprite               --> struct containing high level sprite data.
attribs              --> struct containing low level sprite data.

DESCRIPTION

This function assigns attribs to sprite and initializes
sprite's values.

RETURNS

Returns nothing.

AUTHOR

Kyle Halladay

*/
/**/
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

/**/
/*
Lonk::ExecuteAction()

NAME

Lonk::ExecuteAction - main routine for Lonk.

SYNOPSIS

Lonk::ExecuteAction(uint8 AM[10]);
AM[10]               --> array containing player input flags.

DESCRIPTION

This function reads the player's input and executes on them
(if ISPC) or runs an AI package, the updates internal stats
and updates Lonk's sprite position and animation.

RETURNS

Returns nothing.

AUTHOR

Lucas Crockett

DATE

18/12/2019

*/
/**/
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
        
        // Reset values that could be modified
        SPREC = 1;
        HPREC = 0;

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
            ISATK = ATKDUR;
        }
        
        // Heal/Dash
        if(AM[2] == 1)
        {
            // Action 5
            ISDSH = true;
            if (ISMOV)
            {
                SPREC -= 5;
            }
            else
            {
                // Heal code here
                SPREC -= 2;
                HPREC += 2;
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

    SP += SPREC;
    max(SP, MAXSP);
    if(SP < 0)
    {
        HP += SP;
        SP = 0;
    }
    HP += HPREC;
    max(MAXHP, HP);
    if(HP <= 0)
    {
        // Run death code
    }

    UpdateSpritePosition(&SPRITE);
    TickSpriteAnimation(&SPRITE);

    MEM_OAM[0] = OAM_BACKBUFFER[0];
}


/**/
/*
Lonk::UpdateSpritePosition()

NAME

Lonk::UpdateSpritePosition - updates a sprite's position.

SYNOPSIS

Lonk::UpdateSpritePosition(CharSprite* sprite);
sprite               --> the sprite to be updated.

DESCRIPTION

This function updates the low level sprite data with the high
level data.

RETURNS

Returns nothing.

AUTHOR

Kyle Halladay

*/
/**/
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

/**/
/*
Lonk::TickSpriteAnimation()

NAME

Lonk::TickSpriteAnimation - updates a sprite's animation.

SYNOPSIS

Lonk::TickSpriteAnimation(CharSprite* sprite);
sprite               --> the sprite to be updated.

DESCRIPTION

This function updates the sprite's animation frame based on it's
high level data.

RETURNS

Returns nothing.

AUTHOR

Kyle Halladay, Lucas Crockett

*/
/**/
void Lonk::TickSpriteAnimation(CharSprite* sprite)
{
    ObjectAttributes* spriteAttribs = sprite->spriteAttribs;

    // Attack animation
    if(ISATK)
    {
        sprite->firstAnimCycleFrame = 56;
	    sprite->animFrame = ISATK > ATKREC ? 0 : 1;
        ISATK--;
    }
    else
    {
        // Movement animations
        if (sprite->velX != 0 || sprite->velY != 0)
        {
            sprite->firstAnimCycleFrame = 32;
            sprite->animFrame = (++sprite->animFrame) % 3;
        }
        // Idle animation
        else
        {
            sprite->firstAnimCycleFrame = 0;
            // Slows down the animation
            if (!(*CLOCK % IDLEDELAY))
            {
                sprite->animFrame = (++sprite->animFrame) % 4;
            }
        }
    }

    spriteAttribs->attr2 = sprite->firstAnimCycleFrame + (sprite->animFrame * 8);    

}
