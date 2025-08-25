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
	std::string machineSelectionList[3] = { "Smelting Machine    ", "Crafting Machine    ", "Conveyor Belt    " };
	char machinePlacementSymbol[3] = {'S', 'C', '>'};
	int machinePlacementSymbolIndex;
	int buildMenuLevel;
	int machineTypeChoice;
	char objectRotation;
	int prevSelectionPosition;
	

	// animation
	float cursorBlinkTiming;
	bool cursorVisible;

	// Input related
	char keyPressed;
	char change;
};

