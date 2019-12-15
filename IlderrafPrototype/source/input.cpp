#include "input.h"

void input::key_poll()
{
    input_prev = input_cur;
    input_cur = REG_KEYINPUT | KEY_MASK;
};

unsigned short input::wasKeyPressed(unsigned short key_code)
{
    return (key_code) & (~input_cur & input_prev);
}

unsigned short input::wasKeyReleased(unsigned short key_code)
{
    return  (key_code) & (input_cur & ~input_prev);
}

unsigned short input::getKeyState(unsigned short key_code)
{
    return !(key_code & (input_cur) );
}