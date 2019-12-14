///////////////////////////////////////////////////////////////
//
//  By Lucas Crockett
//  12/12/2019
///////////////////////////////////////////////////////////////
#pragma once
#include "input.h"
#include "gba.h"

class Controls {

public:

    int GetActions()
    {
        // Get a copy of the input register
        key_poll();

        // Check if START was pressed
        if (wasKeyPressed(KEY_START)) m_ACTION_MAP[9] = 1;

        // Check if buttons assigned to ACTIONS were used
        for (int i = 0; i < 5; i++)
        {
            uint16 button = m_BUTTON_MAP[i];

            if (wasKeyPressed(button))
            {
                m_ACTION_MAP[i] = 1;
            }
            else if (wasKeyReleased(button))
            {
                m_ACTION_MAP[i] = 2;
            }
            else
            {
                m_ACTION_MAP[i] = 0;
            }
        }

        // Check if buttons assigned to MOVE are held
        for (int i = 5; i < 9; i++)
        {
            uint16 button = m_BUTTON_MAP[i];

            if (getKeyState(button))
            {
                m_ACTION_MAP[i] = 1;
            }
            else
            {
                m_ACTION_MAP[i] = 0;
            }
            
        }

        return 0;
    };

    void ChangeControls(int ButtonNum)
    {
        return;
    };

private:

    // Array of remappable buttons.  These correspond directly to the ACTION_MAP.
    // START is not remappable, as it is used to access options menus.
    uint16 m_BUTTON_MAP [9] = {KEY_A, KEY_B, KEY_L, KEY_R, KEY_SELECT, 
                                KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};

    // Contains flags for character actions.
    // Index 0 - 4 are ACTIONS, can be press (1), release (2) or neither (0).
    // Index 5 - 9 are MOVE, are either held (1) or not (0).
    uint8 m_ACTION_MAP [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}