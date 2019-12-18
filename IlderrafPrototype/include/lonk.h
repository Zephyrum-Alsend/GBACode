/////////////////////////////////////////////////////////////////
//
// Class for the default PC.  Contains possible actions, attributes,
// and animations.
//
// By Lucas Crockett
// 14/12/2019
/////////////////////////////////////////////////////////////////
#pragma once

#include "controls.h"
#include "Hero.h"
#include "gba.h"
#include <string.h>

#define min(x,y) (x > y ? y : x)
#define max(x,y) (x < y ? y : x)

// https://knowyourmeme.com/memes/lonk
class Lonk {
    public:
        Lonk(uint32* clck, bool PC = false);

        void InitializeSprite(CharSprite* sprite, ObjectAttributes* attribs);

        void ExecuteAction(uint8 AM[10]);
        
        void UpdateSpritePosition(CharSprite* sprite);

        void TickSpriteAnimation(CharSprite* sprite);
    private:
        bool ISPC; // is controlled by player or AI?

        ObjectAttributes OAM_BACKBUFFER[128];
        CharSprite SPRITE;
        uint32* CLOCK;

        int HP; // Hit Points - if at 0, char dies
        int MAXHP = 100; // Max Hit Points - HP cannot exceed MAXHP
        int HPREC = 0; // Recovery rate of HP
        int SP; // Stamina Points - resource for actions, if at 0, actions cost HP
        int MAXSP = 100; // Max Stamina Points - SP cannot exceed MAXSP
        int SPREC = 1; // Recovery rate of SP
        int LENX = 16; // Width of char's sprite in pixels
        int LENY = 16; // Height of char's sprite in pixels
        int SPD = 2; // Speed, measured in pixels per frame
        bool ISDSH = false; // Flag to indicate if DSHMULT is in effect
        int DSHMULT = 3; // Multiplier for speed when char is dashing
        bool ISMOV = false; // Flag to indicate if char is moving or not
};