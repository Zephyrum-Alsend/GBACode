///////////////////////////////////////////////////////////////
//
//  All button inputs are handled through this class, so remapping
//  is possible on a broader scale.
//
//  By Lucas Crockett
//  12/12/2019
///////////////////////////////////////////////////////////////
#pragma once

#include "input.h"
#include "gba.h"

class Controls {

public:

    // Constructor
    Controls() {};

    // Gets a copy of ACTION_MAP
    void GetActions(uint8 arr[10]);

    // Turns state of buttons into ACTION_MAP other characters can use
    void UpdateActions();

    // Swaps one button with another on the ACTION_MAP, so A can do what
    // B did, etc.  START is not allowed to be remapped.
    bool ChangeControls(int ButtonNum);

private:
    // Input class, to read the registers for us.
    input INP;

    // Array of remappable buttons.  These correspond directly to the ACTION_MAP.
    // START is not remappable, as it is used to access options menus.
    uint16 BUTTON_MAP [9] = {KEY_A, KEY_B, KEY_L, KEY_R, KEY_SELECT, 
                                KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};

    // Contains flags for character actions.
    // Index 0 - 4 are ACTIONS, can be press (1), release (2) or neither (0).
    // Index 5 - 8 are MOVE, are either held (1) or not (0).
    // Index 9 is START, either press (1) or not (0).
    uint8 ACTION_MAP [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};