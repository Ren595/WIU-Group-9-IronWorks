#pragma once
#include <string>

class Factory
{
public:
	Factory();
	const void drawScreen();
	void updateScreen(float dt);
	char factoryInput();
private:
	// Information
	int factoryNo;
	int cursorX;
	int cursorY;
	int lastCursorX;
	int lastCursorY;
	bool cursorMoving;
	bool buildOn;
	bool buildToggled;
	std::string machineDirection[4] = {"Up   ", "Right", "Down ", "Left "};
	char conveyorRotation[4] = { '^', '>' , 'v', '<' };
	std::string machineTypes[7] = { "Smelting Machine    ", "Crafting Machine     ", "Conveyor Belt     ", "Splitter     ", "Auto-Sell Area   ", "Inventory Area   ", "Delivery Area   " };
	std::string machineInfo[7] = { "Turns ores into ingots for use.", 
								   "Turns ingots and/or resources provided to make new products.", 
								   "Your best friend in moving items around the factory.",
								   "Alternatively makes items go in different directions.",
								   "Automatically sells items that enter here to the shop.",
								   "Automatically moves items that enter here into your inventory.",
								   "Automatically moves items specified by you from the inventory to your factory." };
	
	
	// For display
	char entity;
	std::string buildAlertUI[2] = { "View Mode ", "Build Mode" };
	std::string errorMsg;
	std::string prevErrorMsg;
	float errorDuration;

	// Build mode UI
	bool machineSelectionOpen;
	bool machineSelectionToggled;
	int finalSelectionChoice;
	std::string machineSelection;
	std::string machineTypeSelectionList[3] = { "Smelting Machine    ", "Crafting Machine     ", "Movement Machine    " };
	char machinePlacementSymbol[7] = {'S', 'C', '>', 'T', 'M', 'I', 'D'};
	int machinePlacementSymbolIndex;
	int buildMenuLevel;
	int machineTypeChoice;
	int objectRotationIndex;
	int prevSelectionPosition;
	std::string resourceMachineSelectionList[5] = { "Level 1", "Level 2", "Level 3", "Level 4", "Level 5", };
	std::string movementMachineSelectionList[5] = { "Conveyor Belt     ", "Splitter     ", "Auto-Sell Area   ", "Inventory Area   ", "Delivery Area   "};
	bool machineSelected;
	

	// animation
	float cursorBlinkTiming;
	bool cursorVisible;

	// Input related
	char keyPressed;
	char change;
};

