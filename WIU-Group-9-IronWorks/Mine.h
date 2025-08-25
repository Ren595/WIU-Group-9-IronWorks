#pragma once
#include <string>
#include <vector>

class Mine
{
private:
	char keyPressed;
	int playerlocationx;
	int playerlocationy;

	int orelocationx[5];
	int orelocationy[5];
	char change;
	int inventory[6];

	int Dminefloor;
	int Lminefloor;
	char world[20][20];
	bool oreActive[5]; // AI add this line

public:
	Mine();
	void update();
	void drawMine();
	void clearMine();
	char mineInput();

	char ores[6] = { 'I','S','G','R','A','P' };
	std::string orelist[6] = { "Iron", "Silver", "Gold", "Ruby", "Amethyst", "Platinum" };
};

