/////////////////////////////////////////////////////////////////////////////
//  
//  Displays on the screen what button was last pressed.  Used for testing.
//  
//  By Kyle Halladay, edited by Lucas Crockett
//  14/12/2019
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string.h>
#include "tiles.h"
#include "controls.h"

    void LoadTileData();

    void ClearSprite();

    void DrawSprite(uint16 key_code);

    void CreateBackground();

    void TileTest();