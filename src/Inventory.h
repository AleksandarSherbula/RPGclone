#ifndef INVENTORY_H
#define INVENTORY_H

#include <array>
#include <string>

class Inventory
{
public:
	std::array<std::wstring, 16> slots;
public:
	Inventory();

	void Draw();
};

#endif // !INVENTORY_H