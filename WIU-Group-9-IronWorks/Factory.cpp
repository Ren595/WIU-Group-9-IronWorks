#include "Factory.h"
#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>
using std::cout;
using std::endl;

Factory::Factory()
{
	// General
	factoryNo = Game::returnCurrentFactoryNo();
	keyPressed = '/';
	cursorX = 9;
	cursorY = 9;
	lastCursorX = cursorX;
	lastCursorY = cursorY;
	change = '/';
	factorySelection = factoryNo;
	finalSelectionChoice = 0;
	prevSelectionPosition = -1;
	currentMonth = 0;
	currentYear = 1950;
	

	// Resource selection menu related
	resourceSelectionOpen = false;
	resourceSelectionToggled = false;
	resourceSelectionLevel = 0;
	resourceTypeChoice = 0;
	resourceTypeIndex = -1;

	// Animations
	cursorBlinkTiming = 0.5f;
	cursorVisible = true;
	cursorMoving = false;
	errorDuration = 0.0f;
	itemMovementTimer = 1.0f;
	monthTimer = 30.0f;

	// Build menu related
	buildOn = false;
	buildToggled = false;
	entity = '/';
	machineSelectionOpen = false;
	machineSelection = "Not Selected";
	machineSelectionToggled = false;
	machineTypeChoice = 0;
	buildMenuLevel = 0;
	machinePlacementSymbolIndex = 0;
	objectRotationIndex = -1;
	machinePlacementSymbolIndex = -1;
	machineQuantityIndex = 0;

	// Error handling
	errorMsg = "None";
	prevErrorMsg = "None";
}












const void Factory::drawScreen()
{
	// Top UI
	std::cout << months[currentMonth] << " " << currentYear << std::endl;
	cout << "View Mode" << endl;

	// Creating upper border
	for (int a = 0;a < 41;a++) {
		if (a == 0 || a == 40) {
			cout << '+';
			if (a == 40) {
				cout << endl;
			}
		}
		else {
			cout << '-';
		}
	}

	// Creating board
	for (int i = 0;i < 20;i++) {
		cout << '|';
		for (int j = 0;j < 20;j++) {
			cout << Game::returnFactoryEntity(j, i, factoryNo);
			if (j == 19) {
				cout << '|' << endl;;
			}
			else {
				cout << ' ';
			}
		}
	}

	// Creating bottom border
	for (int b = 0;b < 41;b++) {
		if (b == 0 || b == 40) {
			cout << '+';
			if (b == 40) {
				cout << endl;
			}
		}
		else {
			cout << '-';
		}
	}

	// Default money value below the factory grid
	cout << "Money: 0";

	// Right screen generation
	// Control help
	Game::overwriteText("Controls:", 50, 0, true, 0x0F);
	Game::overwriteText("WASD - Move the cursor around", 50, 1, true, 0x0F);
	Game::overwriteText("B - Toggle build mode", 50, 2, true, 0x0F);

	// View mode specific controls (Default mode)
	Game::overwriteText("View mode specific controls :", 50, 4, true, 0x0F);
	Game::overwriteText("1 - Enter the Mine", 50, 5, true, 0x0F);
	Game::overwriteText("2 - Enter the Inventory", 50, 6, true, 0x0F);
	Game::overwriteText("3 - Enter the Shop", 50, 7, true, 0x0F);
	Game::overwriteText("4 - Enter the Assistant Menu", 50, 8, true, 0x0F);
	Game::overwriteText("Enter - View machine information", 50, 10, true, 0x0F);

	// System message area
	Game::overwriteText("System Message: ", 50, 23, true, 0x0F);

	// Factory Selection area
	Game::overwriteText("+-----------------------------------+", 50, 24, true, 0x0F);
	Game::overwriteText("|      Factory Navigation menu      |", 50, 25, true, 0x0F);
	Game::overwriteText("+-----------------------------------+", 50, 26, true, 0x0F);
	for (int f = 0;f < 3;f++) {
		Game::overwriteText("+---------------------+", 65, 27 + f * 3, true, 0x0F);
		Game::overwriteText("|      Factory " + std::to_string(f + 1) + "      |", 65, 28 + f * 3, true, 0x0F);
		Game::overwriteText("+---------------------+", 65, 29 + f * 3, true, 0x0F);
	}
	Game::overwriteText("--->", 55, 28 + factoryNo * 3, true, 0x0F);
}











void Factory::updateScreen(float dt)
{
	if (change != 'F') {
		// Updating values with dt
		Game::updateMoneyCount(Game::returnMoneyCount() + dt);
		errorDuration -= dt;
		monthTimer -= dt;

		// Cursor blinking animation control
		if (!cursorMoving) {
			cursorBlinkTiming -= dt;
			// Cursor blinking
			if (change == '/' && cursorBlinkTiming < 0.0f) {
				cursorBlinkTiming += 0.5f;
				cursorVisible = !cursorVisible;
				change = cursorVisible ? 'A' : 'R';
			}
		}

		// Main display updates
		if (change != '/') {
			switch (change) {
				// Removing an entity
			case 'R':
				Game::overwriteText(std::string(1, Game::returnFactoryEntity(cursorX, cursorY, factoryNo)), cursorX * 2 + 1, cursorY + 3, true, 0x0F);
				break;
				// Adding an entity
			case 'A':
				Game::overwriteText(std::string(1, Game::returnFactoryEntity(cursorX, cursorY, factoryNo)), cursorX * 2 + 1, cursorY + 3, true, 0x8F);
				if (machinePlacementSymbolIndex != -1) {
					Game::overwriteText("   ", 15, 27, false, 0x0F);
					Game::overwriteText(std::to_string(Game::returnMachineQuantity(machineQuantityIndex)), 15, 27, true, 0x0F);
				}
				break;
				// Moving an item
			case 'M':
				// Replace old location
				Game::overwriteText(std::string(1, Game::returnFactoryEntity(lastCursorX, lastCursorY, factoryNo)), lastCursorX * 2 + 1, lastCursorY + 3, true, 0x0F);
				// Add new position
				Game::overwriteText(std::string(1, Game::returnFactoryEntity(cursorX, cursorY, factoryNo)), cursorX * 2 + 1, cursorY + 3, true, 0x8F);
				break;
				// Doing the display for machine information
			case 'D':
				Game::clearArea(0, 25, 50, 10);
				entity = Game::returnFactoryEntity(cursorX, cursorY, factoryNo);
				if (entity != ' ') {
					int tempDetails[3] = { factoryNo, cursorX, cursorY };
					int machineTypeNo = Game::returnEntityDetail(tempDetails, 0);
					Game::overwriteText("Machine information:", 0, 25, true, 0x0F);
					cout << endl;
					cout << "Type: " << machineTypes[machineTypeNo] << endl;
					cout << "Rotation: " << machineDirection[Game::returnEntityDetail(tempDetails, 1)] << endl;
					cout << "Machine Information: " << machineInfo[machineTypeNo] << endl;
					if (machineTypeNo == 6) {
						cout << "Type of resource spawned:" << endl;
						int oreTypeIndex = Game::returnEntityDetail(tempDetails, 2);
						if (oreTypeIndex < 7) {
							cout << metalTypeList[oreTypeIndex] << " Ore" << endl;
						}
						else if (oreTypeIndex < 14) {
							cout << metalTypeList[oreTypeIndex-7] << " Ingot" << endl;
						}
						else {
							cout << metalTypeList[oreTypeIndex-7] << endl;
						}
						cout << "Press Q here to change the type of resource \nspawned by the Delivery Area" << endl;
					}
					else if (machineTypeNo < 2) {
						cout << "Level: " << std::to_string(Game::returnEntityDetail(tempDetails, 2)) << endl;
					}
				}
				else {
					Game::overwriteText("There is nothing here.", 0, 25, true, 0x0F);
				}
				break;
			case 'S':
				// For selection of what machine to place
				Game::overwriteText(machineSelection, 27, 25, true, 0x0F);
				break;
			case 'm':
				if (buildOn || resourceSelectionOpen) {
					// Replace old location
					if (resourceSelectionOpen) {
						Game::overwriteText(">", 0, 26 + prevSelectionPosition, false, 0x0F);
					}
					else {
						Game::overwriteText(">", 0, 27 + prevSelectionPosition, false, 0x0F);
					}
					
					// Add new position
					if (buildMenuLevel == 1) {
						Game::overwriteText(">", 0, 27 + machineTypeChoice, true, 0x0F);
					}
					else if (resourceSelectionLevel == 1) {
						Game::overwriteText(">", 0, 26 + resourceTypeChoice, true, 0x0F);
					}
					else if (resourceSelectionOpen) {
						Game::overwriteText(">", 0, 26 + finalSelectionChoice, true, 0x0F);
					}
					else {
						Game::overwriteText(">", 0, 27 + finalSelectionChoice, true, 0x0F);
					}
				}
				else {
					// Replace old location
					Game::overwriteText("--->", 55, 28 + prevSelectionPosition * 3, false, 0x0F);
					// Add new position
					Game::overwriteText("--->", 55, 28 + factorySelection * 3, true, 0x0F);
				}

				break;
			case 'r':
				Game::overwriteText(machineDirection[objectRotationIndex], 10, 26, true, 0x0F);
				break;
			default:
				errorMsg = "Error in program change detected";
				break;
			}
			change = '/';
		}

		// Updating money count
		Game::overwriteText(std::to_string(Game::returnMoneyCount()), 7, 24, true, 0x0F);

		// Toggling build mode
		if (buildToggled) {
			toggleBuildMode();
		}

		// Toggling machine selection menu
		if (machineSelectionToggled) {
			toggleMachineMenu();
		}

		// Toggling resource selection menu
		if (resourceSelectionToggled) {
			toggleResourceSelectionMenu();
		}

		// Part of machine selection menu
		if (buildMenuLevel == 2) {
			machineSelectionLevel2();
		}

		// Part of resource selection menu
		if (resourceSelectionLevel == 2) {
			resourceSelectionLevel2();
		}

		// Checking duration of error
		if (errorDuration < 0.0f && prevErrorMsg != "None") {
			Game::overwriteText(prevErrorMsg, 66, 23, false, 0x0F);
			prevErrorMsg = "None";
		}

		if (!buildOn && itemMovementTimer < 0.0f) {
			for (int v = 0;v < Game::returnDeliveryAreaSize();v++) {
				int deliveryFactoryNo = Game::returnDeliveryAreaDetail(v, 0);
				int deliveryX = Game::returnDeliveryAreaDetail(v, 1);
				int deliveryY = Game::returnDeliveryAreaDetail(v, 2);
				int deliveryDirection = Game::returnDeliveryAreaDetail(v, 3);
				if (pathFinder(deliveryFactoryNo, deliveryX, deliveryY, deliveryDirection)) {
					std::vector<int> itemDetail = { deliveryFactoryNo, deliveryX, deliveryY, deliveryDirection, };
					itemDetails.push_back(itemDetail);
				}
			}
			for (int v = 0;v < itemDetails.size();v++) {
				int itemFactoryNo = itemDetails[v][0];
				int itemX = itemDetails[v][1];
				int itemY = itemDetails[v][2];
				int itemDirection = itemDetails[v][3];
				if (pathFinder(itemFactoryNo, itemX, itemY, itemDirection)) {
					moveItem(itemFactoryNo, itemX, itemY, itemDirection, false);
				}
			}
		}

		// Checking time spent
		if (monthTimer < 0.0f) {
			Game::overwriteText(months[currentMonth] + " " + std::to_string(currentYear), 0, 0, false, 0x0F);

			monthTimer = 30.0f; // Reset month timer for next month
			currentMonth++; // Move to the next month

			if (currentMonth > 11) {
				currentMonth = 0; // Reset to January
				currentYear++; // Increment the year
			}

			// Display the current month and year
			Game::overwriteText(months[currentMonth] + " " + std::to_string(currentYear), 0, 0, true, 0x0F);
		}

		// Making error visible to player
		if (errorMsg != "None") {
			if (errorMsg != prevErrorMsg) {
				Game::overwriteText(prevErrorMsg, 66, 23, false, 0x0F);
			}
			Game::overwriteText(errorMsg, 66, 23, true, 0x04);
			prevErrorMsg = errorMsg;
			errorDuration = 1.5f;
			errorMsg = "None";
		}

		// Miscellaneous
		cursorMoving = false;
	}
	else {
		system("cls");
		drawScreen();
		change = '/';
	}
}













void Factory::toggleBuildMode()
{
	Game::clearArea(0, 25, 70, 10);
	Game::clearArea(50, 5, 60, 15);
	Game::clearArea(50, 24, 60, 12);
	Game::overwriteText(buildAlertUI[buildOn], 0, 1, true, 0x0F);
	machineSelection = "Not Selected";
	machinePlacementSymbolIndex = -1;
	objectRotationIndex = -1;
	buildToggled = false;
	if (buildOn) {
		clearItemsFromFactory();
		// For selection UI
		Game::overwriteText("Current machine selection: " + machineSelection, 0, 25, true, 0x0F);

		// Build mode specific controls
		Game::overwriteText("Build mode specific controls:", 50, 4, true, 0x0F);
		Game::overwriteText("Q - Open machine placement menu", 50, 5, true, 0x0F);

		Game::overwriteText("While in machine placement menu:", 50, 7, true, 0x0F);
		Game::overwriteText("Arrow keys(Up and Down) - Navigate machine placement menu", 50, 8, true, 0x0F);
		Game::overwriteText("Space - Confirm choice in menu", 50, 9, true, 0x0F);

		Game::overwriteText("Outside machine placement menu:", 50, 11, true, 0x0F);
		Game::overwriteText("Arrow keys - Decide machine orientation", 50, 12, true, 0x0F);
		Game::overwriteText("Enter - Add machine to grid", 50, 13, true, 0x0F);
		Game::overwriteText("Backspace - Remove machine from grid", 50, 14, true, 0x0F);

	}
	else {
		// View mode specific controls
		Game::overwriteText("View mode specific controls :", 50, 4, true, 0x0F);
		Game::overwriteText("1 - Enter the Mine", 50, 5, true, 0x0F);
		Game::overwriteText("2 - Enter the Inventory", 50, 6, true, 0x0F);
		Game::overwriteText("3 - Enter the Shop", 50, 7, true, 0x0F);
		Game::overwriteText("4 - Enter the Assistant Menu", 50, 8, true, 0x0F);
		Game::overwriteText("Enter - View machine information", 50, 10, true, 0x0F);

		// Factory Selection area
		Game::overwriteText("+-----------------------------------+", 50, 24, true, 0x0F);
		Game::overwriteText("|      Factory Navigation menu      |", 50, 25, true, 0x0F);
		Game::overwriteText("+-----------------------------------+", 50, 26, true, 0x0F);
		for (int f = 0;f < 3;f++) {
			Game::overwriteText("+---------------------+", 65, 27 + f * 3, true, 0x0F);
			Game::overwriteText("|      Factory " + std::to_string(f + 1) + "      |", 65, 28 + f * 3, true, 0x0F);
			Game::overwriteText("+---------------------+", 65, 29 + f * 3, true, 0x0F);
		}
		Game::overwriteText("--->", 55, 28 + factoryNo * 3, true, 0x0F);
	}
}










void Factory::toggleMachineMenu()
{
	machineSelectionToggled = false;
	if (machineSelectionOpen) {
		machineTypeChoice = 0;
		finalSelectionChoice = 0;
		objectRotationIndex = -1;
		machinePlacementSymbolIndex = -1;
		buildMenuLevel = 1;
		machineSelection = "Not Selected      ";
		Game::overwriteText(machineSelection, 27, 25, true, 0x0F);
		Game::overwriteText("Select type of machine to place:", 0, 26, true, 0x0F);
		for (int d = 0;d < 3;d++) {
			Game::overwriteText("  " + machineTypeSelectionList[d], 0, 27 + d, true, 0x0F);
		}
		Game::overwriteText(">", 0, 27 + machineTypeChoice, true, 0x0F);
	}
	else {
		Game::clearArea(0, 26, 50, 6);
		if (objectRotationIndex != -1) {
			Game::overwriteText("Rotation: " + machineDirection[objectRotationIndex], 0, 26, true, 0x0F);
			if (machineTypeChoice < 2) {
				machineQuantityIndex = 5 + machineTypeChoice * 5 + finalSelectionChoice;
				Game::overwriteText("Quantity left: " + std::to_string(Game::returnMachineQuantity(machineQuantityIndex)), 0, 27, true, 0x0F);
			}
			else {
				machineQuantityIndex = 15 + finalSelectionChoice;
				Game::overwriteText("Quantity left: " + std::to_string(Game::returnMachineQuantity(machineQuantityIndex)), 0, 27, true, 0x0F);
			}
			
		}
	}
}









void Factory::machineSelectionLevel2()
{
	Game::clearArea(0, 26, 50, 6);
	switch (machineTypeChoice) {
	case 0:
	case 1:
		Game::overwriteText("Select level of machine to place:", 0, 26, true, 0x0F);
		for (int d = 0;d < 5;d++) {
			Game::overwriteText("  " + resourceMachineSelectionList[d], 0, 27 + d, true, 0x0F);
		}
		break;
	case 2:
		Game::overwriteText("Select type of movement machine to place:", 0, 26, true, 0x0F);
		for (int d = 0;d < 5;d++) {
			Game::overwriteText("  " + movementMachineSelectionList[d], 0, 27 + d, true, 0x0F);
		}
		break;
	default:
		errorMsg = "Error in selecting machine type.";
		break;
	}
	Game::overwriteText(">", 0, 27 + finalSelectionChoice, true, 0x0F);
	buildMenuLevel++;
}









void Factory::toggleResourceSelectionMenu()
{
	Game::clearArea(0, 25, 50, 12);
	resourceSelectionToggled = false;
	if (resourceSelectionOpen) {
		resourceTypeChoice = 0;
		finalSelectionChoice = 0;
		resourceTypeIndex = -1;
		resourceSelectionLevel = 1;
		Game::overwriteText("Select type of item to spawn:", 0, 25, true, 0x0F);
		for (int d = 0;d < 3;d++) {
			Game::overwriteText("  " + resourceTypeList[d], 0, 26 + d, true, 0x0F);
		}
		Game::overwriteText(">", 0, 26 + resourceTypeChoice, true, 0x0F);
	}
}






void Factory::resourceSelectionLevel2()
{
	Game::clearArea(0, 25, 50, 12);
	switch (resourceTypeChoice) {
	case 0:
		Game::overwriteText("Select type of ore to spawn:", 0, 25, true, 0x0F);
		for (int d = 0;d < 7;d++) {
			Game::overwriteText("  " + metalTypeList[d], 0, 26 + d, true, 0x0F);
		}
		break;
	case 1:
		Game::overwriteText("Select type of ingot to spawn:", 0, 25, true, 0x0F);
		for (int d = 0;d < 7;d++) {
			Game::overwriteText("  " + metalTypeList[d], 0, 26 + d, true, 0x0F);
		}
		break;
	case 2:
		Game::overwriteText("Select type of resource to spawn:", 0, 25, true, 0x0F);
		for (int d = 0;d < 5;d++) {
			Game::overwriteText("  " + metalTypeList[7+d], 0, 26 + d, true, 0x0F);
		}
		break;
	default:
		errorMsg = "Error in selecting item type.";
		break;
	}
	Game::overwriteText(">", 0, 26 + finalSelectionChoice, true, 0x0F);
	resourceSelectionLevel++;
}









bool Factory::pathFinder(int factoryNo, int itemX, int itemY, int directionIndex)
{
	int newX, newY;
	newX = itemX;
	newY = itemY;
	switch (directionIndex) {
	case 0:
		newY--;
		break;
	case 1:
		newX++;
		break;
	case 2:
		newY++;
		break;
	case 3:
		newX--;
		break;
	default:
		errorMsg = "Error in detecting collisions";
		break;
	}

	if (newX > 19 || newX < 0 || newY > 19 || newY < 0) {
		return false;
	}
	else if (Game::returnFactoryEntity(newX, newY, factoryNo) == ' ' || Game::returnFactoryEntity(newX, newY, factoryNo) == 'D') {
		return false;
	}
	else if (Game::returnFactoryEntity(newX, newY, factoryNo) == 'A' || Game::returnFactoryEntity(newX, newY, factoryNo) == 'I') {
		return true;
	}
	else if (itemAtGrid(factoryNo, newX, newY)) {
		return false;
	}
	int tempArrDetails[3] = { factoryNo, newX, newY };
	int adjMachineIndex = Game::returnEntityDetail(tempArrDetails, 0);
	int adjMachineDirection = Game::returnEntityDetail(tempArrDetails, 1);
	if (adjMachineIndex == 3 && adjMachineDirection != directionIndex) {
		errorMsg = "Splitter orientation incorrect";
		return false;
	}
	int directionCheck = directionIndex + 2;
	if (directionCheck > 3) {
		directionCheck -= 4;
	}
	if (directionCheck == adjMachineDirection) {
		return false;
	}
	else if (adjMachineIndex < 2) {
		return pathFinder(factoryNo, newX, newY, adjMachineDirection);
	}
	else {
		return true;
	}
}











bool Factory::itemAtGrid(int factoryNo, int itemX, int itemY)
{
	for (int v = 0;v < itemDetails.size();v++) {
		if (itemDetails[v][0] == factoryNo && itemDetails[v][1] == itemX && itemDetails[v][2] == itemY) {
			return true;
		}
	}
	return false;
}
















void Factory::moveItem(int factoryNo, int itemX, int itemY, int directionIndex, bool second)
{
	int newX, newY;
	newX = itemX;
	newY = itemY;
	switch (directionIndex) {
	case 0:
		newY--;
		break;
	case 1:
		newX++;
		break;
	case 2:
		newY++;
		break;
	case 3:
		newX--;
		break;
	default:
		errorMsg = "Error in detecting collisions";
		break;
	}
	if (second) {
		updateItemDetail(factoryNo, itemX, itemY, 3, directionIndex);
		if (Game::returnFactoryEntity(newX, newY, factoryNo) == 'A') {
			Game::updateMoneyCount(Game::returnMoneyCount()+500);
			deleteItem(factoryNo, itemX, itemY);
		}
		else if (Game::returnFactoryEntity(newX, newY, factoryNo) == 'I') {
			int itemQuantityIndex = returnItemDetail(factoryNo, itemX, itemY, 4);
			Game::updateItemQuantity(itemQuantityIndex, Game::returnItemQuantity(itemQuantityIndex));
			deleteItem(factoryNo, itemX, itemY);
		}
		else {
			int tempArray[3] = { factoryNo, newX, newY };
			updateItemDetail(factoryNo, itemX, itemY, 3, Game::returnEntityDetail(tempArray, 1));
			Game::overwriteText(displayItem(returnItemDetail(factoryNo, itemX, itemY, 4)), newX * 2 + 1, newY + 3, true, 0x0F);
			updateItemDetail(factoryNo, itemX, itemY, 1, newX);
			updateItemDetail(factoryNo, newX, itemY, 2, newY);
		}
	}
	else if (Game::returnFactoryEntity(itemX, itemY, factoryNo) != 'D') {
		Game::overwriteText(std::string(1, Game::returnFactoryEntity(itemX, itemY, factoryNo)), itemX * 2 + 1, itemY + 3, true, 0x0F);
	}
	else if (Game::returnFactoryEntity(newX, newY, factoryNo) == 'S') {
		updateItemDetail(factoryNo, itemX, itemY, 4, returnItemDetail(factoryNo, newX, newY, 4)+7);
		updateItemDetail(factoryNo, itemX, itemY, 1, newX);
		updateItemDetail(factoryNo, newX, itemY, 2, newY);
		int tempArray[3] = {factoryNo, newX, newY};
		moveItem(factoryNo, newX, newY, Game::returnEntityDetail(tempArray, 1), true);
	}
	else {
		int tempArray[3] = { factoryNo, newX, newY };
		updateItemDetail(factoryNo, itemX, itemY, 3, Game::returnEntityDetail(tempArray, 1));
		Game::overwriteText(displayItem(returnItemDetail(factoryNo, itemX, itemY, 4)), newX * 2 + 1, newY + 3, true, 0x0F);
		updateItemDetail(factoryNo, itemX, itemY, 1, newX);
		updateItemDetail(factoryNo, newX, itemY, 2, newY);
	}
}








void Factory::updateItemDetail(int factoryNo, int itemX, int itemY, int index, int newValue)
{
	for (int v = 0;v < itemDetails.size();v++) {
		if (itemDetails[v][0] == factoryNo && itemDetails[v][1] == itemX && itemDetails[v][2] == itemY) {
			itemDetails[v][index] = newValue;
			break;
		}
	}
}







int Factory::returnItemDetail(int factoryNo, int itemX, int itemY, int index)
{
	for (int v = 0;v < itemDetails.size();v++) {
		if (itemDetails[v][0] == factoryNo && itemDetails[v][1] == itemX && itemDetails[v][2] == itemY) {
			return itemDetails[v][index];
		}
	}
}






void Factory::deleteItem(int factoryNo, int itemX, int itemY)
{
	int vectorIndex = 0;
	for (int v = 0;v < itemDetails.size();v++) {
		if (itemDetails[v][0] == factoryNo && itemDetails[v][1] == itemX && itemDetails[v][2] == itemY) {
			vectorIndex = v;
			break;
		}
	}
	itemDetails.erase(itemDetails.begin() + vectorIndex);
}







std::string Factory::displayItem(int itemIndex)
{
	if (itemIndex < 7) {
		return std::string(1, 'o');
	}
	else if (itemIndex < 14) {
		return std::string(1, 'i');
	}
	else {
		return std::string(1, 'r');
	}
}









void Factory::clearItemsFromFactory()
{
	if (!itemDetails.empty()) {
		for (int v = 0;v < itemDetails.size();v++) {
			std::vector<int> tempDetails = itemDetails[v];
			Game::updateItemQuantity(tempDetails[4], Game::returnItemQuantity(tempDetails[3]) + 1);
		}
		while (!itemDetails.empty()) {
			itemDetails.pop_back();
		}
	}
}







char Factory::factoryInput()
{
	keyPressed = _getch();
	int changeX = 0;
	int changeY = 0;

	switch (keyPressed) {
	case 'W':
	case 'w':
		// move the cursor up
		if (!resourceSelectionOpen) {
			changeY--;
		}
		else {
			errorMsg = "Cannot move while selecting resource type.";
		}
		break;
	case 'S':
	case 's':
		// move the cursor down
		if (!resourceSelectionOpen) {
			changeY++;
		}
		else {
			errorMsg = "Cannot move while selecting resource type.";
		}
		break;
	case 'A':
	case 'a':
		// move the cursor left
		if (!resourceSelectionOpen) {
			changeX--;
		}
		else {
			errorMsg = "Cannot move while selecting resource type.";
		}
		break;
	case 'D':
	case 'd':
		// move the cursor right
		if (!resourceSelectionOpen) {
			changeX++;
		}
		else {
			errorMsg = "Cannot move while selecting resource type.";
		}
		break;
	case 8:
		// If build mode is on and backspace key is pressed, remove the machine
		if (buildOn) {
			if (Game::returnFactoryEntity(cursorX, cursorY, factoryNo) != ' ') {
				int tempArray[3] = {factoryNo, cursorX, cursorY};
				int machineTypeIndex = Game::returnEntityDetail(tempArray, 0);
				int RmachineQuantityIndex = 0;
				if (machineTypeIndex < 2) {
					RmachineQuantityIndex = 5 + machineTypeIndex * 5 + Game::returnEntityDetail(tempArray, 2)-1;
					Game::updateMachineQuantity(RmachineQuantityIndex, Game::returnMachineQuantity(RmachineQuantityIndex) + 1);
				}
				else {
					RmachineQuantityIndex = 15 + machineTypeIndex - 2;
					Game::updateMachineQuantity(RmachineQuantityIndex, Game::returnMachineQuantity(RmachineQuantityIndex) + 1);
				}
				//errorMsg = std::to_string(machineQuantityIndex);
				Game::updateFactoryWorld(cursorX, cursorY, factoryNo, ' ');
				change = 'A';
				int tempDetails[8] = { factoryNo, cursorX, cursorY, 0,0,0,0,0 };
				Game::updateMachineDetailsVector(false, tempDetails);
				if (machineTypeIndex == 6) {
					int tempDetails[5] = { factoryNo, cursorX, cursorY, 0,0};
					Game::updateDeliveryAreasVector(false, tempDetails);
				}
			}
			else {
				errorMsg = "There is nothing to remove here";
			}
		}
		break;
	case 13:
		// Display machine information if build mode is off and enter key is pressed
		// If build mode is on, place the machine
		if (buildOn) {
			if (machinePlacementSymbolIndex == -1) {
				errorMsg = "Please select a machine to place.";
			}
			else if (Game::returnFactoryEntity(cursorX, cursorY, factoryNo) != ' ') {
				errorMsg = "There is an existing machine at this grid";
			}
			else {
				if (machineTypeChoice < 2) {
					machineQuantityIndex = 5 + machineTypeChoice * 5 + finalSelectionChoice;
				}
				else {
					machineQuantityIndex = 15 + finalSelectionChoice;
				}

				if (Game::returnMachineQuantity(machineQuantityIndex) > 0) {
					Game::updateMachineQuantity(machineQuantityIndex, Game::returnMachineQuantity(machineQuantityIndex) - 1);
					change = 'A';
					int tempDetails[6] = { factoryNo, cursorX, cursorY, machinePlacementSymbolIndex,objectRotationIndex,0};
					if (machinePlacementSymbolIndex == 2) {
						Game::updateFactoryWorld(cursorX, cursorY, factoryNo, conveyorRotation[objectRotationIndex]);
					}
					else {
						Game::updateFactoryWorld(cursorX, cursorY, factoryNo, machinePlacementSymbol[machinePlacementSymbolIndex]);
					}
					if (machinePlacementSymbolIndex < 2) {
						tempDetails[5] = finalSelectionChoice + 1;
					}
					Game::updateMachineDetailsVector(true, tempDetails);
					if (machinePlacementSymbolIndex == 6) {
						int deliveryAreaDetail[4] = { factoryNo, cursorX, cursorY, objectRotationIndex };
						Game::updateDeliveryAreasVector(true, deliveryAreaDetail);
					}
				}
				else {
					errorMsg = "Not enough machines to place";
				}
			}
		}
		else if (!resourceSelectionOpen) {
			change = 'D';
		}
		else {
			errorMsg = "Cannot view machine details while editing";
		}
		break;
	case 32:
		// Only used for selecting an option while the machine selection menu is open
		if (machineSelectionOpen) {
			if (buildMenuLevel == 1) {
				buildMenuLevel++;
			}
			else {
				machineSelectionOpen = !machineSelectionOpen;
				machineSelectionToggled = true;
				objectRotationIndex = 1;

				switch (machineTypeChoice) {
				case 0:
					machineSelection = "Smelting Machine";
					break;
				case 1:
					machineSelection = "Crafting Machine";
					break;
				case 2:
					machineSelection = movementMachineSelectionList[finalSelectionChoice];
					break;
				}
				machinePlacementSymbolIndex = machineTypeChoice;
				if (machineTypeChoice == 2) {
					machinePlacementSymbolIndex += finalSelectionChoice;
				}
				change = 'S';
			}
		}
		else if (resourceSelectionOpen) {
			if (resourceSelectionLevel == 1) {
				resourceSelectionLevel++;
			}
			else {
				resourceSelectionOpen = !resourceSelectionOpen;
				resourceSelectionToggled = true;

				int tempArray[3] = { factoryNo, cursorX, cursorY };
				resourceTypeIndex = resourceTypeChoice * 7 + finalSelectionChoice;
				Game::updateEntityDetails(tempArray, 2, resourceTypeIndex);
				Game::updateDeliveryAreaDetail(tempArray, 4, resourceTypeIndex);
			}
		}
		else {
			if (factorySelection == factoryNo) {
				errorMsg = "You are already at this factory";
			}
			else if (Game::returnFactoryActivity(factorySelection) == false) {
				errorMsg = "You do not yet own this factory";
			}
			else {
				Game::updateCurrentFactoryNo(factorySelection);
				factoryNo = factorySelection;
				change = 'F';
			}
		}
		break;
	case 'Q':
	case 'q':
		// Toggling the machine selection menu if q was pressed
		if (buildOn) {
			machineSelectionOpen = !machineSelectionOpen;
			machineSelectionToggled = true;
		}
		else if (Game::returnFactoryEntity(cursorX, cursorY, factoryNo) == 'D') {
			resourceSelectionOpen = !resourceSelectionOpen;
			resourceSelectionToggled = true;
		}
		break;
	case 'B':
	case 'b':
		// Toggling the build menu if b was pressed
		buildOn = !buildOn;
		buildToggled = true;
		break;
	case 'P':
	case 'p':
		// Navigating to pause menu if build mode is off and p is pressed
		if (!buildOn) {
			return 'P';
		}
		break;
	case '1':
		// Navigating to Mine if build mode is off and 1 is pressed
		// If build mode is on and machine selection is open, select Smelting machine
		if (!buildOn) {
			return 'M';
		}
		break;
	case '2':
		// Navigating to Inventory if build mode is off and 2 is pressed
		// If build mode is on and machine selection is open, select Crafting machine
		if (!buildOn) {
			return 'I';
		}
		break;
	case '3':
		// Navigating to Shop if build mode is off and 3 is pressed
		// If build mode is on and machine selection is open, select Conveyor Belt
		if (!buildOn) {
			return 'S';
		}
		break;
	case '4':
		// Navigating to Assistant selection menu if build mode is off and 4 is pressed
		if (!buildOn) {
			return 'A';
		}
		break;
	case 0:
	case -32:
	case 224:
		keyPressed = _getch();
		switch (keyPressed) {
		case 72:
			// Up arrow key pressed
			if (machineSelectionOpen) {
				if (buildMenuLevel == 1) {
					prevSelectionPosition = machineTypeChoice--;
					if (machineTypeChoice < 0) {
						machineTypeChoice = 2;
					}
				}
				else {
					prevSelectionPosition = finalSelectionChoice--;
					if (finalSelectionChoice < 0) {
						finalSelectionChoice = 4;
					}
				}
				change = 'm';
			}
			else if (objectRotationIndex != -1) {
				objectRotationIndex = 0;
				change = 'r';
			}
			else if (resourceSelectionOpen) {
				if (resourceSelectionLevel == 1) {
					prevSelectionPosition = resourceTypeChoice--;
					if (resourceTypeChoice < 0) {
						resourceTypeChoice = 2;
					}
				}
				else {
					prevSelectionPosition = finalSelectionChoice--;
					if (finalSelectionChoice < 0) {
						if (resourceTypeChoice == 2) {
							finalSelectionChoice = 4;
						}
						else {
							finalSelectionChoice = 6;
						}
					}
				}
				change = 'm';
			}
			else {
				prevSelectionPosition = factorySelection--;
				if (factorySelection < 0) {
					factorySelection = 2;
				}
				change = 'm';
			}
			break;
		case 80:
			// Down arrow key pressed
			if (machineSelectionOpen) {
				if (buildMenuLevel == 1) {
					prevSelectionPosition = machineTypeChoice++;
					if (machineTypeChoice > 2) {
						machineTypeChoice = 0;
					}
				}
				else {
					prevSelectionPosition = finalSelectionChoice++;
					if (finalSelectionChoice > 4) {
						finalSelectionChoice = 0;
					}
				}
				change = 'm';
			}
			else if (objectRotationIndex != -1) {
				objectRotationIndex = 2;
				change = 'r';
			}
			else if (resourceSelectionOpen) {
				if (resourceSelectionLevel == 1) {
					prevSelectionPosition = resourceTypeChoice++;
					if (resourceTypeChoice > 2) {
						resourceTypeChoice = 0;
					}
				}
				else {
					prevSelectionPosition = finalSelectionChoice++;
					if (finalSelectionChoice > 6 || finalSelectionChoice > 4 && resourceTypeChoice == 2) {
						finalSelectionChoice = 0;
					}
				}
				change = 'm';
			}
			else {
				prevSelectionPosition = factorySelection++;
				if (factorySelection > 2) {
					factorySelection = 0;
				}
				change = 'm';
			}
			break;
		case 75:
			// Left arrow key pressed
			if (objectRotationIndex != -1) {
				objectRotationIndex = 3;
				change = 'r';
			}
			break;
		case 77:
			// Right arrow key pressed
			if (objectRotationIndex != -1) {
				objectRotationIndex = 1;
				change = 'r';
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	
	// Checking player movement
	if (changeX != 0 || changeY != 0) {
		int newX = cursorX + changeX;
		int newY = cursorY + changeY;
		// Checking border and if changes made are finished
		if (newX < 20 && newX > -1 && newY < 20 && newY > -1 && change == '/') {
			lastCursorX = cursorX;
			lastCursorY = cursorY;
			cursorX = newX;
			cursorY = newY;

			cursorVisible = true;
			cursorBlinkTiming = 0.5f;
			cursorMoving = true;

			change = 'M';
		}	
	}

	// Returning '/' as the player is still in the factory
	return '/';
}
