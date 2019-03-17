#pragma once

class Character
{
public:

	//Generic attack function.
	//void attack(int DMG, int TYPE, int ATKSTRT, int ATKACT, int ATKREC, /*Animation params,*/ int ATKMOV, int Direction, int ATKHBX, int ATKHBY,) {}

	//Applies damage to the character.  Returns FALSE if the damage is reflected.
	bool hurt(int DMG, int TYPE, int MOV, int DRC);


	int getHP() { return HP; }
	void setHP(int newHP) { HP = newHP; }
	int getMaxHP() { return MaxHP; }

	int getSP() { return SP; }
	void setSP(int newSP) { SP = newSP; }
	int getMaxSP() { return MaxSP; }

	int getMOVSPD() { return MOVSPD; }
	void setMOVSPD(int newMOVSPD) { MOVSPD = newMOVSPD; }

	int getDASHSPD() { return DASHSPD; }
	void setDASHSPD(int newDASHSPD) { DASHSPD = newDASHSPD; }

	int getCOLBOX() { return (COLBOXX, COLBOXY); }
	void setCOLBOX(int newCBX, int newCBY) { COLBOXX = newCBX; COLBOXY = newCBY; }
	
	bool getGHOST() { return GHOST; }
	void setGHOST(bool state) { GHOST = state; }

	int getHRTBOX() { return (HRTBOXX, HRTBOXY); }
	void setHRTBOX(int newHBX, int newHBY) { HRTBOXX = newHBX; HRTBOXY = newHBY; }

	//Returns which INVUL state is active, 0 if none are.
	int getINVUL() {
		if (INVUL3) { return 3; }
		else if (INVUL2) { return 2; }
		else if (INVUL1) { return 1; }
		else { return 0; }
	}
	void setINVUL(int state) {
		if (state = 0) { INVUL1 = false; INVUL2 = false; INVUL3 = false; }
		else if (state = 1) { INVUL1 = true; INVUL2 = false; INVUL3 = false; }
		else if (state = 2) { INVUL1 = false; INVUL2 = true; INVUL3 = false; }
		else if (state = 3) { INVUL1 = false; INVUL2 = false; INVUL3 = true; }
	}

private:
	int HP; //Hit Points, if 0 then the character is dead.
	int MaxHP; //HP cannot exceed this value.

	bool DEAD = false; //Death flag.

	float PHSRES = 1.0; //Multiply incoming physical damage by this number.
	float FIRRES = 1.0; //Multiply incoming fire damage by this number.
	float ICERES = 1.0; //Multiply incoming ice damage by this number.
	float VOLRES = 1.0; //Multiply incoming volt damage by this number.

	int SP; //Stamina Points, various actions cost this.  If 0, deduct from HP instead.
	int MaxSP; //SP cannot exceed this value.

	int MOVSPD; //How far the character moves per frame in pixels.

	int DASHSPD; //How far the character moves in pixels when performing a dash.
	int DASHTM; //How long it takes to move DASHSPD in frames once dash is initiated.
	int DASHREC; //How long in frames from when dash is initiated to when other actions can be performed.
	int DASHCST; //How much SP dashing costs.
	int IFRAME; //For how many frames of the dash is the character invulnerable to damage.

	//Collision Box, the dimensions of the character's physical space.
	int COLBOXX; //Width in pixels.
	int COLBOXY; //Height in pixels.
	bool GHOST = false; //If TRUE, disable COLBOX (can move through walls).

	//Hurt Box, the area attacks must contact to cause damage.
	int HRTBOXX; //Width in pixels.
	int HRTBOXY; //Height in pixels.
	bool INVUL1 = false; //If TRUE, attacks connect but cause 0 damage.
	bool INVUL2 = false; //If TRUE, HRTBOX is disabled (attacks cannot connect).
	bool INVUL3 = false; //If TRUE, attacks are reflected.

	//ATTACK related properties here

	//Sprite related properties here
};
