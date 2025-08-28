#pragma once
#include <string>
#include <Windows.h>
class Inventory
{
private:
        std::string oreInventoryDisplay[20][5];
        std::string resourceInventoryDisplay[20][5];
        std::string inactiveMachineInventoryDisplay[20][3];
       

public:
	bool needsRedraw;
	char inventoryChoice;
	int row;
	int col;
	bool isSelected[20][20];
	bool isChoosingInventory;
	Inventory();
	void displayWhichInventory();
	void displayInventory();
	bool moveAround();
	void displayOreInfo(); // show ore info
	void displayResourceInfo(); // show resource info
	void displayMachineInfo(); // show inactive machine info
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
};

