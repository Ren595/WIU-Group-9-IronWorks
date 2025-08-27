#include "Inventory.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

Inventory::Inventory()
{
	// Set initial state to choosing inventory
	isChoosingInventory = true;
	inventoryChoice = 0;

	// Initialize the selection matrix to false (no item selected)
	for (int r = 0; r < 20; r++) {
		for (int c = 0; c < 5; c++) {
			isSelected[r][c] = false;
		}
	}

	// Initialize the headings for machine inventory
	inactiveMachineInventoryDisplay[0][0] = "Mining machines";
	inactiveMachineInventoryDisplay[0][1] = "Smelting machines";
	inactiveMachineInventoryDisplay[0][2] = "Crafting machines";
	inactiveMachineInventoryDisplay[0][3] = "Extra machines";

	// Initialize headings for ore inventory
	oreInventoryDisplay[0][0] = "Tier 1";
	oreInventoryDisplay[0][1] = "Tier 2";
	oreInventoryDisplay[0][2] = "Tier 3";
	oreInventoryDisplay[0][3] = "Tier 4";
	oreInventoryDisplay[0][4] = "Tier 5";

	// Initialize headings for resource inventory
	resourceInventoryDisplay[0][0] = "Tier 1";
	resourceInventoryDisplay[0][1] = "Tier 2";
	resourceInventoryDisplay[0][2] = "Tier 3";
	resourceInventoryDisplay[0][3] = "Tier 4";
	resourceInventoryDisplay[0][4] = "Tier 5";

	// Initialize separator rows for headings
	for (int c = 0; c < 4; c++) {
		inactiveMachineInventoryDisplay[1][c] = "-------------------------";
	}
	for (int c = 0; c < 5; c++) {
		oreInventoryDisplay[1][c] = "----------";
	}

	for (int c = 0; c < 5; c++) {
		resourceInventoryDisplay[1][c] = "-------------------------";
	}

	// Fill the rest of the machine inventory with empty spaces
	for (int r = 2; r < 20; r++) {
		for (int c = 0; c < 4; c++) {
			inactiveMachineInventoryDisplay[r][c] = " ";
		}
	}

	// Fill the rest of the ore inventory with empty spaces
	for (int r = 2; r < 20; r++) {
		for (int c = 0; c < 5; c++) {
			oreInventoryDisplay[r][c] = " ";
		}
	}

	// Fill the rest of the resource inventory with empty spaces
	for (int r = 2; r < 20; r++) {
		for (int c = 0; c < 5; c++) {
			resourceInventoryDisplay[r][c] = " ";
		}
	}

	// Set specific ores in the ore inventory
	oreInventoryDisplay[2][0] = "Tin";
	oreInventoryDisplay[3][0] = "Silver";
	oreInventoryDisplay[4][0] = "Iron";
	oreInventoryDisplay[2][1] = "Copper";
	oreInventoryDisplay[2][2] = "Zinc";
	oreInventoryDisplay[2][3] = "Aluminium";
	oreInventoryDisplay[2][4] = "Diamond";

	// Set specific resources in the resource inventory
	resourceInventoryDisplay[2][0] = "Steel";
	resourceInventoryDisplay[2][1] = "Pewter";
	resourceInventoryDisplay[2][2] = "Bronze";
	resourceInventoryDisplay[2][3] = "Brass";
	resourceInventoryDisplay[2][4] = "Diamond-Infused alloy";

	// Set specific machines in the inactive machine inventory
	inactiveMachineInventoryDisplay[2][0] = "Mining machine level 1";
	inactiveMachineInventoryDisplay[3][0] = "Mining machine level 2";
	inactiveMachineInventoryDisplay[4][0] = "Mining machine level 3";
	inactiveMachineInventoryDisplay[5][0] = "Mining machine level 4";
	inactiveMachineInventoryDisplay[6][0] = "Mining machine level 5";

	inactiveMachineInventoryDisplay[2][1] = "Smelting machine level 1";
	inactiveMachineInventoryDisplay[3][1] = "Smelting machine level 2";
	inactiveMachineInventoryDisplay[4][1] = "Smelting machine level 3";
	inactiveMachineInventoryDisplay[5][1] = "Smelting machine level 4";
	inactiveMachineInventoryDisplay[6][1] = "Smelting machine level 5";

	inactiveMachineInventoryDisplay[2][2] = "Crafting machine level 1";
	inactiveMachineInventoryDisplay[3][2] = "Crafting machine level 2";
	inactiveMachineInventoryDisplay[4][2] = "Crafting machine level 3";
	inactiveMachineInventoryDisplay[5][2] = "Crafting machine level 4";
	inactiveMachineInventoryDisplay[6][2] = "Crafting machine level 5";

	inactiveMachineInventoryDisplay[2][3] = "Conveyor belt";
	inactiveMachineInventoryDisplay[3][3] = "Splitter";
	inactiveMachineInventoryDisplay[4][3] = "Auto sell area";
	inactiveMachineInventoryDisplay[5][3] = "Storage area";
	inactiveMachineInventoryDisplay[6][3] = "Delivery area";

	// Initially select the first cell
	isSelected[0][0] = true;
	row = 0;
	col = 0;

}

// Display inventory selection menu
void Inventory::displayWhichInventory()
{
	std::cout << "Which inventory do you want to open?" << std::endl;
	std::cout << "1. Ore inventory" << std::endl;
	std::cout << "2. Resources inventory" << std::endl;
	std::cout << "3. Inactive Machine inventory" << std::endl;
}

// Display the contents of the selected inventory
void Inventory::displayInventory()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (inventoryChoice) {
	case '1': // Ore inventory
		std::cout << "+------------------------------------------------------+" << std::endl;
		for (int r = 0; r < 20; r++) {
			for (int c = 0; c < 5; c++) {
				const int cellWidth = 10; // fixed width for each cell in the ore inventory
				std::string item = oreInventoryDisplay[r][c];
				std::cout << '|';
				if (isSelected[r][c] == true && r >= 2) { // dont show green background in the headings and the separator rows
					SetConsoleTextAttribute(h, 0x20); // set green background
					if (item != " ") {
						std::cout << item; // show ore
					}
					else {
						std::cout << ' ';
					}
					SetConsoleTextAttribute(h, 0x0f); // reset colour
				}
				else {
					std::cout << item; // show the ore or a blank with no green background
				}
				for (int i = item.length(); i < cellWidth; i++) {
					std::cout << ' ';
					// The loop basically prints spaces to fill the remaining width of the cell (maintain column width)
				}
			}
			std::cout << '|' << std::endl;
		}
		std::cout << "+------------------------------------------------------+" << std::endl;
		break;

	case '2': // Resource inventory
		std::cout << "+---------------------------------------------------------------------------------------------------------------------------------+" << std::endl;
		for (int r = 0; r < 20; r++) {
			for (int c = 0; c < 5; c++) {
				std::cout << '|';
				const int cellWidth = 25; // fixed width for each cell in the resource inventory
				std::string item = resourceInventoryDisplay[r][c];
				if (isSelected[r][c] == true && r >= 2) { // dont show green background in the headings and the separator rows
					SetConsoleTextAttribute(h, 0x20); // set green background
					std::cout << item; // show resource
					SetConsoleTextAttribute(h, 0x0f); // reset colour
				}
				else {
					std::cout << item; // show the resource or a blank with no green background
				}
				for (int i = item.length(); i < cellWidth; i++) {
					std::cout << ' ';
					// The loop basically prints spaces to fill the remaining width of the cell (maintain column width)
				}
			}
			std::cout << '|' << std::endl;
		}
		std::cout << "+---------------------------------------------------------------------------------------------------------------------------------+" << std::endl;
		break;
	case '3': // Inactive machine inventory
		std::cout << "+-------------------------------------------------------------------------------------------------------+" << std::endl;
		for (int r = 0; r < 20; r++) {
			for (int c = 0; c < 4; c++) {
				const int cellWidth = 25; // fixed width for each cell in the inactive machine inventory
				std::cout << '|';
				std::string item = inactiveMachineInventoryDisplay[r][c];
				if (isSelected[r][c] == true && r >= 2) { // dont show green background in the headings and the separator rows
					SetConsoleTextAttribute(h, 0x20); // set green background
					if (item != " ") {
						std::cout << item; // show resource
					}
					else {
						std::cout << ' ';
					}
					SetConsoleTextAttribute(h, 0x0f);
				}
				else {
					std::cout << item; // show the resource or a blank with no green background
				}
				for (int i = item.length(); i < cellWidth; i++) {
					std::cout << ' ';
					// The loop basically prints spaces to fill the remaining width of the cell
				}
			}
			std::cout << '|' << std::endl;
		}
		std::cout << "+-------------------------------------------------------------------------------------------------------+" << std::endl;
		break;
	default:
		std::cout << "Invalid input. Default case." << std::endl;
	}
}


// Handle movement and selection inside inventory
bool Inventory::moveAround()
{
	char input = _getch(); // get key press without pressing enter
	if (isChoosingInventory == true) { // selecting which inventory
		if (input == '1' || input == '2' || input == '3') {
			inventoryChoice = input;
			isChoosingInventory = false; // no longer selecting inventory
			needsRedraw = true;
		}
		else if (input == 8) { // Backspace to exit program	
			std::cout << "Exiting program..." << std::endl;
			Sleep(500);
			return false;
		}
		else {
			std::cout << "No inventory exists for this input." << std::endl;
		}
		return true;
	}

	if (isChoosingInventory == false) { // moving around inside inventory
		int newR = row;
		int newC = col;


		switch (input) {
		case 'w':
		case 'W':
			newR--;
			needsRedraw = true;
			break;
		case 'a':
		case 'A':
			newC--;
			needsRedraw = true;
			break;
		case 's':
		case 'S':
			newR++;
			needsRedraw = true;
			break;
		case 'd':
		case 'D':
			newC++;
			needsRedraw = true;
			break;
		case 8: // Backspace to go back to inventory selection
			// Clear all previous selections
			for (int r = 0; r < 20; r++) {
				for (int c = 0; c < 5; c++) {
					isSelected[r][c] = false;
				}
				for (int c = 0; c < 4; c++) { // for machine inventory
					isSelected[r][c] = false;
				}
			}
			isChoosingInventory = true;
			needsRedraw = true;
			row = 0;
			col = 0;
			return true;
		default:
			break;

		}
		if (newR >= 0 && newR < 20 && newC >= 0 && newC < 20) { // checking bounds
			if (inventoryChoice == '3' && newR < 2) {
				newR = 2;
			}  // prevent selecting headings and dashed lines in Machine Inventory
			if (inventoryChoice == '3' && newC >= 4) {
				newC = 3;
			} // prevent going outside the last column
			if (inventoryChoice == '1' && newC >= 5) {
				newC = 4;
			} // prevent going outside the last column
			if (inventoryChoice == '1' && newR < 2) {
				newR = 2;
			} // prevent selecting headings and dashed lines in Ore Inventory
			if (inventoryChoice == '2' && newC >= 5) {
				newC = 4;
			} // prevent going outside the last column
			if (inventoryChoice == '2' && newR < 2) {
				newR = 2;
			} // prevent selecting headings and dashed lines in Resource Inventory
			isSelected[row][col] = false;

			row = newR;
			col = newC;

			isSelected[row][col] = true;
		}
		else {
			std::cout << "Cannot move out of bounds." << std::endl;
		}
	}
	return true;
}

// Display info about currently selected ore
void Inventory::displayOreInfo()
{
	if (inventoryChoice != '1') {
		return;
	}

	std::cout << std::endl;
	std::string ore = oreInventoryDisplay[row][col];
	if (ore == "Tin") {
		std::cout << "Tin ore" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $1000 per unit" << std::endl;
	}
	else if (ore == "Iron") {
		std::cout << "Iron ore" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price : $2700 per unit" << std::endl;

	}
	else if (ore == "Silver") {
		std::cout << "Silver ore" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $1800 per unit" << std::endl;
	}
	else if (ore == "Copper") {
		std::cout << "Copper ore" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $4200 per unit" << std::endl;
	}
	else if (ore == "Zinc") {
		std::cout << "Zinc ore" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $6300 per unit" << std::endl;
	}
	else if (ore == "Aluminium") {
		std::cout << "Aluminium ore" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $8100 per unit" << std::endl;
	}
	else if (ore == "Diamond") {
		std::cout << "Diamond ore" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $10000 per unit" << std::endl;
	}
	else {
		std::cout << "There is nothing here." << std::endl;
	}


}

// Display info about currently selected resource
void Inventory::displayResourceInfo()
{
	if (inventoryChoice != '2') {
		return;
	}
	std::cout << std::endl;
	std::string resource = resourceInventoryDisplay[row][col];
	if (resource == "Steel") {
		std::cout << "Steel" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Made from 2 pieces of iron" << std::endl;
		std::cout << "Price: $5600 per unit" << std::endl;
	}
	else if (resource == "Pewter") {
		std::cout << "Pewter" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Made from 2 pieces of tin and 1 piece of copper" << std::endl;
		std::cout << "Price: $6300 per unit" << std::endl;
	}
	else if (resource == "Bronze") {
		std::cout << "Bronze" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Made from 1 piece of iron and 1 piece of copper" << std::endl;
		std::cout << "Price: $7000 per unit" << std::endl;
	}
	else if (resource == "Brass") {
		std::cout << "Brass" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Made from 1 piece of copper and 1 piece of zinc" << std::endl;
		std::cout << "Price: $11000 per unit" << std::endl;
	}
	else if (resource == "Diamond-Infused alloy") {
		std::cout << "Diamond-Infused alloy" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Made from 1 piece of diamond and 2 other pieces of any other metal or alloy" << std::endl;
		std::cout << "Price: $16500 per unit" << std::endl;
	}
	else {
		std::cout << "There is nothing here." << std::endl;
	}

}

// Display info about currently selected machine
void Inventory::displayMachineInfo()
{
	if (inventoryChoice != '3') {
		return;
	}
	std::cout << std::endl;
	std::string machine = inactiveMachineInventoryDisplay[row][col];
	if (machine == "Mining machine level 1") {
		std::cout << "Mining machine level 1" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Base price: $500 per machine" << std::endl;
	}
	else if (machine == "Mining machine level 2") {
		std::cout << "Mining machine level 2" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $2650 per machine" << std::endl;
	}
	else if (machine == "Mining machine level 3") {
		std::cout << "Mining machine level 3" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $11500 per machine" << std::endl;
	}
	else if (machine == "Mining machine level 4") {
		std::cout << "Mining machine level 4" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $30000 per machine" << std::endl;
	}
	else if (machine == "Mining machine level 5") {
		std::cout << "Mining machine level 5" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $75000 per machine" << std::endl;
	}
	else if (machine == "Smelting machine level 1") {
		std::cout << "Smelting machine level 1" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: 1st is free the rest after it is $750 per machine" << std::endl;
	}
	else if (machine == "Smelting machine level 2") {
		std::cout << "Smelting machine level 2" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $2500 per machine" << std::endl;
	}
	else if (machine == "Smelting machine level 3") {
		std::cout << "Smelting machine level 3" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $7250 per machine" << std::endl;
	}
	else if (machine == "Smelting machine level 4") {
		std::cout << "Smelting machine level 4" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $15500 per machine" << std::endl;
	}
	else if (machine == "Smelting machine level 5") {
		std::cout << "Smelting machine level 5" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $40000 per machine" << std::endl;
	}
	else if (machine == "Crafting machine level 1") {
		std::cout << "Crafting machine level 1" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Base price: $3000 per machine" << std::endl;
	}
	else if (machine == "Crafting machine level 2") {
		std::cout << "Crafting machine level 2" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $10000 per machine" << std::endl;
	}
	else if (machine == "Crafting machine level 3") {
		std::cout << "Crafting machine level 3" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $23000 per machine" << std::endl;
	}
	else if (machine == "Crafting machine level 4") {
		std::cout << "Crafting machine level 4" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $46500 per machine" << std::endl;
	}
	else if (machine == "Crafting machine level 5") {
		std::cout << "Crafting machine level 5" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Value of machine after upgrade: $90000 per machine" << std::endl;
	}
	else if (machine == "Conveyor belt") {
		std::cout << "Conveyor belt" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $600 per piece" << std::endl;
	}
	else if (machine == "Splitter") {
		std::cout << "Splitter" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $850 per piece" << std::endl;
	}
	else if (machine == "Auto sell area") {
		std::cout << "Auto sell area" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $5000 per piece" << std::endl;
		std::cout << "Automatically sell materials" << std::endl;
	}
	else if (machine == "Storage area") {
		std::cout << "Storage area" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $1000 per piece" << std::endl;
		std::cout << "Pull from inventory" << std::endl;
	}
	else if (machine == "Delivery area") {
		std::cout << "Delivery area" << std::endl;
		std::cout << "Quantity: 1" << std::endl;
		std::cout << "Price: $1000 per piece" << std::endl;
		std::cout << "Back to inventory" << std::endl;
	}
	else {
		std::cout << "There is nothing here." << std::endl;
	}
}