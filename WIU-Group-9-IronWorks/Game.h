#pragma once
#include "Factory.h"
#include "Mine.h"
#include "Inventory.h"
#include "Shop.h"
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

	// Getters
	const static char returnFactoryEntity(int x, int y, int factoryNo);
	const static float returnMoneyCount();
	
	// Game destructor
	~Game();
private:
	// Static data members
	static char factoryWorlds[3][20][20];
	static std::vector<std::vector<int>> machineDetails;
	static float money;

	// Normal data members
	// General
	char sceneArea;
	char prevSceneArea;
	bool gameStatus;
	char keyPressed;
	std::chrono::time_point<std::chrono::steady_clock> start; // For dt calculation
	char action;
	

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

