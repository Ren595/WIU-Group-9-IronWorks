#pragma once
#include <string>
#include <vector>

class Mine
{
private:
	char keyPressed;
	int playerlocationx;
	int playerlocationy;

	int orelocationx[200];
	int orelocationy[200];
	int machinelocationx[10];
	int machinelocationy[10];
	bool machineActive[10];
	int machinecount;
	int machineinventory[5];

	int startcamx;
	int startcamy;

	char change;
	int inventory[7];

	char world[100][100];
	std::vector<std::vector<char>>FOV;
	bool oreActive[200]; // AI add this line

	float oreTimer[10];
	int oreRarity;
	int orespawnRarity;

public:
	Mine();
	void update(float dt);
	void drawMine();
	void updateFOV();
	char mineInput();
	void updateMine();

	char ores[7] = { 'T','S','I','C','Z','A','D' };
	std::string orelist[7] = { "Tin", "Silver", "Iron", "Copper", "Zinc", "Aluminium", "Diamond" };
};
