///////////////////////////////////////////////////////////////////////
//
//  Parent class for all character objects
//  i.e. Player Character, Enemies, Non-Hostile Characters, Destructable objects
//
//  By Lucas Crockett
//  14/12/2019
///////////////////////////////////////////////////////////////////////
#pragma once

#include "gba.h"
#include <vector>

class Char {

public:

    void move(uint8 dir);

private:
    bool PC = false; // Player Character - is Char controlled by the player?

    int HP; // Hit Points - if 0, Char is dead.
    int SP; // Stamina Points - resource for actions, if 0, actions cost HP.
    
    int posX; // Char's X position.
    int posY; // Char's Y position.
    int lenX; // Char's width.
    int lenY; // Char's height.
    int SPD; // Speed - number of pixels per frame the Char moves.

    // The starting memory address of every animation in the spriteblock.
    std::vector<uint8> ANIM_START;
};