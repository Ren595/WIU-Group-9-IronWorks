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
	int machinelocationx[50];
	int machinelocationy[50];
	bool machineActive[50];
	int machineplaced;

	int startcamx;
	int startcamy;

	char change;

	char world[100][100];
	std::vector<std::vector<char>>FOV;
	bool oreActive[200]; // AI add this line

	float oreTimer[50];
	int oreRarity;
	int orespawnRarity;

	int getAllowedMachineCount() const;

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