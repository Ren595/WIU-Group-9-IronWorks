#pragma once
#include <string>

class Factory
{
public:
	Factory();
	const void drawScreen();
	void updateScreen(float dt);
	void toggleBuildMode();
	void toggleMachineMenu();
	void machineSelectionLevel2();
	void toggleResourceSelectionMenu();
	void resourceSelectionLevel2();
	void pathFinder();
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
	
	bool resourceSelectionOpen;
	bool resourceSelectionToggled;
	int resourceSelectionLevel;
	int resourceTypeChoice;
	int resourceTypeIndex;
	int prevSelectionPosition;
	int finalSelectionChoice;
	int factorySelection;
	
	
	// For display
	char entity;
	std::string buildAlertUI[2] = { "View Mode ", "Build Mode" };
	std::string errorMsg;
	std::string prevErrorMsg;
	float errorDuration;
	float itemMovementTimer;

	// In View Mode
	std::string machineDirection[4] = { "Up   ", "Right", "Down ", "Left " };
	char conveyorRotation[4] = { '^', '>' , 'v', '<' };
	std::string machineTypes[7] = { "Smelting Machine    ", "Crafting Machine     ", "Conveyor Belt     ", "Splitter     ", "Auto-Sell Area   ", "Inventory Area   ", "Delivery Area   " };
	std::string machineInfo[7] = { "Turns ores into ingots for \nuse. More types of ores can be smelted with \nhigher leveled machines",
								   "Turns ingots and/or \nresources provided to make new products. More \nvariety unlocked with higher levels.",
								   "Your best friend in moving \nitems around the factory.",
								   "Alternatively makes items go \nin different directions.",
								   "Automatically sells items \nthat enter here to the shop.",
								   "Automatically moves items \nthat enter here into your inventory.",
								   "Automatically moves items \nspecified by you from your inventory to \nyour factory." };
	std::string resourceTypeList[3] = {"Ores", "Ingots", "Crafted materials"};
	std::string metalTypeList[12] = { "Tin", "Silver", "Iron", "Copper", "Zinc", "Aluminium", "Diamond", "Pewter", "Steel", "Bronze", "Brass", "Diamond-Infused Alloy" };

	// Build mode UI
	bool machineSelectionOpen;
	bool machineSelectionToggled;
	std::string machineSelection;
	std::string machineTypeSelectionList[3] = { "Smelting Machine", "Crafting Machine", "Movement Machine" };
	char machinePlacementSymbol[7] = {'S', 'C', '>', 'T', 'A', 'I', 'D'};
	int machinePlacementSymbolIndex;
	int buildMenuLevel;
	int machineTypeChoice;
	int objectRotationIndex;
	std::string resourceMachineSelectionList[5] = { "Level 1", "Level 2", "Level 3", "Level 4", "Level 5", };
	std::string movementMachineSelectionList[5] = { "Conveyor Belt   ", "Splitter        ", "Auto-Sell Area  ", "Inventory Area  ", "Delivery Area   "};
	int machineQuantityIndex;
	

	// animation
	float cursorBlinkTiming;
	bool cursorVisible;

	// Input related
	char keyPressed;
	char change;
};

