typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;

#define REG_DISPLAYCONTROL	*((volatile uint32*)(0x04000000))
#define REG_VCOUNT      	*((volatile uint16*)(0x04000006))
#define VIDEOMODE_3     	0x0003
#define BGMODE_2 			0x0400

#define SCREENBUFFER        ((volatile uint16*)0x06000000)
#define SCREEN_W            240
#define SCREEN_H            160

inline uint16 MakeCol(uint8 red, uint8 green, uint8 blue);
inline void vsync();
void drawRect(int left, int top, int width, int height, uint16 clr);

int main()
{
    REG_DISPLAYCONTROL = VIDEOMODE_3 | BGMODE_2;
	
	uint8 R = 31;
	uint8 G = 31;
	uint8 B = 0;
    for (int i = 0; i < SCREEN_W * SCREEN_H; ++i)
    {
    	SCREENBUFFER[i] = MakeCol(R,G,B);
		
		if (R == 0 || R > 31) // Leaving out this clamp and using the unsafe MakeCol function surprisingly runs, but the colors are a bit off.
			R = 31;
		else
			R -= 1;
			
		if (G == 0 || G > 31)
			G = 31;
		else
			G -= 2;
    }

    int x = 0;
	int inc = 23;
    while(1)
    {
    	vsync();
		
		// "Erase" the rectangle's last position.
		if (x)
		{
			int last = x - inc;
			drawRect(last % SCREEN_W, (last / SCREEN_W) * 10, 10, 10,MakeCol(0,0,0));
		}
		
		// Wrap the rectangle's position.
		if ( x > SCREEN_W * (SCREEN_H/10)) x = 0;
		
		// Draw the rectangle's current position.
		drawRect(x % SCREEN_W, (x / SCREEN_W) * 10, 10, 10,MakeCol(31,31,31));
		x += inc; // Update position.
		
    }

    return 0;
}





inline uint16 MakeCol(uint8 red, uint8 green, uint8 blue)
{
    //return (red & 0x1F) | (green & 0x1F) << 5 | (blue & 0x1F) << 10;
	return red | green << 5 | blue << 10;
}

inline void vsync()
{
  while (REG_VCOUNT >= 160);
  while (REG_VCOUNT < 160);
}

void drawRect(int left, int top, int width, int height, uint16 clr)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
    	   SCREENBUFFER[(top + y) * SCREEN_W + left + x] = clr;
        }
    }
}