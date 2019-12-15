#pragma once
class arraygetter
{
public:
	arraygetter();
	~arraygetter();

	void GetArray(int arg[10]);

	int* OGetArray() { return arr; };

	void SetArray();

private:
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
};

