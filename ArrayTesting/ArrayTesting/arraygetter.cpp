#include "arraygetter.h"



arraygetter::arraygetter()
{
}


arraygetter::~arraygetter()
{
}

void arraygetter::GetArray(int arg[10])
{
	for (int i = 0; i < 10; i++)
	{
		arg[i] = arr[i];
	}

	return;
}

void arraygetter::SetArray()
{
	for (int i = 0; i < 10; i++) 
	{
		if (false)
		{
			arr[i] = 1;
		}
	}
}