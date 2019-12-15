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
#include <vector>

class Lonk {
    public:
        void executeAction(uint8 AM[10]);
    private:

        int HP;
        int SP;
        int posX;
        int posY;
        int lenX;
        int lenY;
        int SPD;

        std::vector<int> ANIM_START;
};