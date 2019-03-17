#include "Character.h"

//Applies damage to the character.  Returns FALSE if reflected.
bool Character::hurt(int DMG, int TYPE, int MOV, int DRC) {
	//Attack is reflected.
	if (INVUL3) { return false; }
	//Attack does nothing.
	else if (INVUL2) { return true; }
	//Apply knockback, but not damage.
	else if (INVUL1) {
		
		return true;
	}
	//Apply knockback and damage.
	else {
		//Apply damage.
		if (TYPE == 0) {
			HP -= ( DMG * PHSRES );
		}
		else if (TYPE == 1) {
			HP -= ( DMG * FIRRES );
		}
		else if (TYPE == 2) {
			HP -= ( DMG * ICERES );
		}
		else if (TYPE == 3) {
			HP -= (DMG * VOLRES);
		}
		//Untyped damage.
		else {
			HP -= DMG;
		}
		//Check for HP bounds.
		if (HP <= 0) {
			DEAD = true;
			//call death process.
		}
		else if (HP >= MaxHP) {
			HP = MaxHP;
		}

		//Apply knockback.
		return true;
	}
	//If you got here, something went very wrong.
	return false;
}
