#include "controls.h"

/**/
/*
Controls::GetActions()

NAME

Controls::GetActions - gets the flag states for actions.

SYNOPSIS

Controls::GetActions(uint8 arr[10]);
arr[10]             --> the array to copy m_ACTION_MAP into.

DESCRIPTION

This function copies ACTION_MAP into the passed array, so
other functions can view ACTION_MAP.

RETURNS

Returns nothing.

AUTHOR

Lucas Crockett

DATE

15/12/2019

*/
/**/
void Controls::GetActions(uint8 arr[10])
{
    for(int i = 0; i < 10; i++)
    {
        arr[i] = m_ACTION_MAP[i];
    }
}

/**/
/*
Controls::UpdateActions()

NAME

Controls::UpdateActions - gets key states and sets flags in ACTION_MAP.

SYNOPSIS

Controls::UpdateActions();

DESCRIPTION

This function reads the state of every key on the GBA and maps their
states (pressed, released, held) to ACTION_MAP, according to BUTTON_MAP.
ACTION_MAP is then ready to be read by the PC class.

RETURNS

Returns nothing.

AUTHOR

Lucas Crockett

DATE

12/12/2019

*/
/**/
void Controls::UpdateActions()
{
    // Reset m_ACTION_MAP
    for (int i = 0; i < 10; i++)
    {
        m_ACTION_MAP[i] = 0;
    }

    // Get a copy of the input register
    inp.key_poll();

    // Check if START was pressed
    if (inp.wasKeyPressed(KEY_START)) 
    {
        m_ACTION_MAP[9] = 1;
    }

    // Check if buttons assigned to ACTIONS were used
    for (int i = 0; i < 5; i++)
    {
        // Set the current button to check for.
        uint16 button = m_BUTTON_MAP[i];

        if (inp.wasKeyPressed(button))
        {
            m_ACTION_MAP[i] = 1;
        }
        else if (inp.wasKeyReleased(button))
        {
            m_ACTION_MAP[i] = 2;
        }
    }

    // Check if buttons assigned to MOVE are held
    for (int i = 5; i < 9; i++)
    {
        uint16 button = m_BUTTON_MAP[i];

        if (inp.getKeyState(button))
        {
            m_ACTION_MAP[i] = 1;
        }
    }

};

/**/
/*
Controls::ChangeControls()

NAME

Controls::ChangeControls - swaps two buttons' actions.

SYNOPSIS

Controls::ChangeControls(uint8 ButtonNum);
ButtonNum       --> The button to be swapped.

DESCRIPTION

This function takes a button of the player's choice and swaps it's
functionality with another button of the player's choice.  START
cannot be swapped.

RETURNS

Returns nothing.

AUTHOR

Lucas Crockett

DATE

12/12/2019

*/
/**/
bool Controls::ChangeControls(int ButtonNum)
{
    // ButtonNum refers to the index on ACTION_MAP
    // The menu will handle prompting the player, so we only need to swap the input with ButtonNum
    
    UpdateActions();

    uint16 swapkey;
    for (int i = 0; i < 9; i++)
    {
        // Check if a button is pressed/held.
        if (m_ACTION_MAP[i] == 1)
        {
            swapkey = m_BUTTON_MAP[i];
            m_BUTTON_MAP[i] = m_BUTTON_MAP[ButtonNum];
            m_BUTTON_MAP[ButtonNum] = swapkey;
            return true;
        }
    }

    return false; // The system is waiting for an input, and this is a way around interrupts.
};