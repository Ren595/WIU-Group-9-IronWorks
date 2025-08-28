#pragma once
#include "Factory.h"
#include "Mine.h"
#include "Inventory.h"
#include "Shop.h"
#include "assistantSelection.h"
#include <string>
#include <chrono>
#include <vector>

class Game
{
public:
	// Game constructor
	Game();

	// Integral functions
	// General
	void gameDisplay();
	void gameInput();
	void fullsc();
	float obtainDeltaTime();
	static void PlayMusic(const std::wstring& filename, bool repeat);
	static void StopMusic(std::string type);
	static void SetVolume(const std::wstring& alias, int volume);

	// For UI
	void menuScreen();
	void saveScreen();
	void pauseScreen();
	void storyScreen();
	static void overwriteText(const std::string& text, int x, int y, bool show, int colour);
	static void clearArea(int x, int y, int width, int height);
	void ShowConsoleCursor(bool showCursor);


	// Setters
	static void updateFactoryWorld(int x, int y, int factoryNo, char value);
	static void updateMoneyCount(float value);
	
	// pos info is [factoryNo, x, y]
	static void updateEntityDetails(int posInfo[3], int index, int newValue);
	static void updateMachineDetailsVector(bool add, int details[8]);
	static void updateMachineQuantity(int index, int newValue);
	static void updateItemQuantity(int index, int newValue);
	static void updateFactoryActivity(int index, bool newState);
	static void updateCurrentFactoryNo(int newValue);

	// Getters
	const static char returnFactoryEntity(int x, int y, int factoryNo);
	const static float returnMoneyCount();
	const static int returnEntityDetail(int posInfo[3], int infoIndex);
	const static int returnMachineQuantity(int index);
	const static int returnItemQuantity(int index);
	const static bool returnFactoryActivity(int index);
	const static bool returnCurrentFactoryNo();

	// Game destructor
	~Game();
private:
	// Static data members
	static char factoryWorlds[3][20][20];
	static bool activeFactories[3];
	static float money;
	static int factoryNo;
	
	// Format if its resource machine: {factoryNo, x, y, machineTypesIndex, directionIndex, machineLevel, machineHealth, noOfWorkers}
	// Format if its movement machine: {factoryNo, x, y, machineTypesIndex, directionIndex, 0, 0, 0}
	// Format if its Delivery Area: {factoryNo, x, y, machineTypesIndex, directionIndex, resourceIndex, 0, 0}
	static std::vector<std::vector<int>> machineDetails;
	
	// Format for layout of machineQuantity array: {5 levels of mining machine, 5 levels of smelting machine, 5 levels of crafting machine, 5 different types of movement machines}
	static int machineQuantity[20];
	
	// Format for layout of itemQuantity array: {7 Types of ores, 7 Types of ingots, 5 types of resources}
	static int itemQuantity[19];

	static std::vector<std::vector<int>> deliveryAreas;
	

	// Normal data members
	// General
	char sceneArea;
	char prevSceneArea;
	bool gameStatus;
	char keyPressed;
	std::chrono::time_point<std::chrono::steady_clock> start; // For dt calculation
	char action;
	float dt;

	// Menu screen
	int menuChoice;
	bool visible;
	std::string options[3] = { "Start New Game", "Continue Game", "Exit" };
	char destinations[3] = { 'N', 'C', 'E' };
	int choiceColours[3] = { 0x0F , 0x02, 0x04 };

	// Save screen menu
	// to be added later

	// Story
	bool lineFinished;
	bool storyDone;
	bool goNextLine;
	bool skip;

	// Factory
	
	// Inventory
	bool inInventory;

	// obtaining objects
	Factory factory;
	Mine mine;
	Inventory inventory;
	Shop shop;
};

