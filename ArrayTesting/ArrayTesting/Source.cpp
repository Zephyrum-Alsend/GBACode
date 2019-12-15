#include "arraygetter.h"
#include <iostream>
using namespace std;

int main()
{
	arraygetter a;
	int arge[10] = { 0 };

	a.SetArray();
	a.GetArray(arge);
	
	return 0;
}