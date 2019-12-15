////////////////////////////////////////////////////////////////////////
//
//  Defines every key on the GBA and provides functions to get their states.
//
//  By Kyle Halladay
//  12/12/2019
////////////////////////////////////////////////////////////////////////
#pragma once

#define REG_KEYINPUT  (* (volatile unsigned short*) 0x4000130)

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0xFC00
class input

{
public:
    input() {};
    // Polling function
    void key_poll();

    unsigned short wasKeyPressed(unsigned short key_code);

    unsigned short wasKeyReleased(unsigned short key_code);

    unsigned short getKeyState(unsigned short key_code);

private:
    unsigned short input_cur = 0x03FF;
    unsigned short input_prev = 0x03FF;
};