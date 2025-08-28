#include "Shop.h"
#include "Game.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <map>
#include <Windows.h>

Shop::Shop() {
	shopChoice = '/';
	shopArea = 'Q';
	for (int i = 0; i < 6; i++) {
		assistantsHired[i] = false;
	}
}

void Shop::shopDisplay() {
	system("cls"); // clear screen for redraw
	// Initial state → show main menu
	switch (shopArea) {
	case 'Q':
		std::cout << MAIN_MENU_ART << std::endl;
		while (shopArea == 'Q') {
			continue;
		}
		break;
	case 'W':
		std::cout << BUY_MENU_ART << std::endl;
		while (shopArea == 'W') {
			continue;
		}
		break;
	case 'E':
		std::cout << BUY_MACHINE_MENU_ART << std::endl;
		while (shopArea == 'E') {
			if (boughtItem) {
				std::cout << itemInfo << std::endl;
				boughtItem = false;
			}
			Sleep(10);
		}
		break;
	case 'T':
		std::cout << BUY_ASSISTANT_MENU_ART << std::endl;
		while (shopArea == 'T') {
			if (boughtItem) {
				std::cout << itemInfo << std::endl;
				boughtItem = false;
			}
			Sleep(10);
		}
		break;
	case 'Y':
		std::cout << BUY_FACTORY_MENU_ART << std::endl;
		while (shopArea == 'Y') {
			if (boughtItem) {
				std::cout << itemInfo << std::endl;
				boughtItem = false;
			}
			Sleep(10);
		}
		break;
	case 'U':
		std::cout << SELL_MENU_ART << std::endl;
		while (shopArea == 'U') {
			continue;
		}
		break;
	case 'I':
		std::cout << SELL_MACHINE_MENU_ART << std::endl;
		while (shopArea == 'I') {
			if (soldItem) {
				std::cout << itemInfo << std::endl;
				soldItem = false;
			}
			Sleep(10);
		}
		break;
	case 'O':
		std::cout << SELL_CRAFTED_ITEM_MENU_ART << std::endl;
		while (shopArea == 'O') {
			if (soldItem) {
				std::cout << itemInfo << std::endl;
				soldItem = false;
			}
			Sleep(10);
		}
		break;
	case 'P':
		std::cout << SELL_SMELTED_ITEMS_MENU_ART << std::endl;
		while (shopArea == 'P') {
			if (soldItem) {
				std::cout << itemInfo << std::endl;
				soldItem = false;
			}
			Sleep(10);
		}
		break;
	case 'A':
		std::cout << SELL_MINED_ORES_MENU_ART << std::endl;
		while (shopArea == 'A') {
			if (soldItem) {
				std::cout << itemInfo << std::endl;
				soldItem = false;
			}
			Sleep(10);
		}
		break;
	case 'e':
		break;
	default:
		std::cout << "Display error" << std::endl;
		break;
	}
}

// Input function only handles keypress and returns it
char Shop::shopInput()
{
	shopChoice = _getch(); // blocking here is fine since this is input thread
	switch (shopChoice) {
	case 'a':
		shopArea = 'W';
		shopChoice = _getch();
		while (shopChoice != 'e') {
			switch (shopChoice) {
			case 'a':
				shopArea = 'E';
				shopChoice = _getch();
				while (shopChoice != 'u') {
					switch (shopChoice) {
					case 'a':
						if (Game::returnMoneyCount() >= 500.0f) {
							boughtItem = true;
							itemInfo = "You bought Mining Machine lvl 1";
							Game::updateMachineQuantity(0, Game::returnMachineQuantity(0) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 500.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'b':
						if (Game::returnMoneyCount() >= 2650.0f) {
							boughtItem = true;
							itemInfo = "You bought Mining Machine lvl 2";
							Game::updateMachineQuantity(1, Game::returnMachineQuantity(1) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 1000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'c':
						if (Game::returnMoneyCount() >= 11500.0f) {
							boughtItem = true;
							itemInfo = "You bought Mining Machine lvl 3";
							Game::updateMachineQuantity(2, Game::returnMachineQuantity(2) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 11500.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
							break;
						}
						break;
					case 'd':
						if (Game::returnMoneyCount() >= 30000.0f) {
							boughtItem = true;
							itemInfo = "You bought Mining Machine lvl 4";
							Game::updateMachineQuantity(3, Game::returnMachineQuantity(3) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 30000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'e':
						if (Game::returnMoneyCount() >= 75000.0f) {
							boughtItem = true;
							itemInfo = "You bought Mining Machine lvl 5";
							Game::updateMachineQuantity(4, Game::returnMachineQuantity(4) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 75000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'f':
						if (Game::returnMoneyCount() >= 750.0f) {
							boughtItem = true;
							itemInfo = "You bought Smelting Machine lvl 1";
							Game::updateMachineQuantity(5, Game::returnMachineQuantity(5) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 750.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'g':
						if (Game::returnMoneyCount() >= 2500.0f) {
							boughtItem = true;
							itemInfo = "You bought Smelting Machine lvl 2";
							Game::updateMachineQuantity(6, Game::returnMachineQuantity(6) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 2500.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'h':
						if (Game::returnMoneyCount() >= 7250.0f) {
							boughtItem = true;
							itemInfo = "You bought Smelting Machine lvl 3";
							Game::updateMachineQuantity(7, Game::returnMachineQuantity(7) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 7250.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'i':
						if (Game::returnMoneyCount() >= 15500.0f) {
							boughtItem = true;
							itemInfo = "You bought Smelting Machine lvl 4";
							Game::updateMachineQuantity(8, Game::returnMachineQuantity(8) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 15500.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'j':
						if (Game::returnMoneyCount() >= 40000.0f) {
							boughtItem = true;
							itemInfo = "You bought Smelting Machine lvl 5";
							Game::updateMachineQuantity(9, Game::returnMachineQuantity(9) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 40000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
					case 'k':
						if (Game::returnMoneyCount() >= 3000.0f) {
							boughtItem = true;
							itemInfo = "You bought Crafting Machine lvl 1";
							Game::updateMachineQuantity(10, Game::returnMachineQuantity(10) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 3000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'l':
						if (Game::returnMoneyCount() >= 10000.0f) {
							boughtItem = true;
							itemInfo = "You bought Crafting Machine lvl 2";
							Game::updateMachineQuantity(11, Game::returnMachineQuantity(11) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 10000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'm':
						if (Game::returnMoneyCount() >= 23000.0f) {
							boughtItem = true;
							itemInfo = "You bought Crafting Machine lvl 3";
							Game::updateMachineQuantity(12, Game::returnMachineQuantity(12) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 23000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'n':
						if (Game::returnMoneyCount() >= 46500.0f) {
							boughtItem = true;
							itemInfo = "You bought Crafting Machine lvl 4";
							Game::updateMachineQuantity(13, Game::returnMachineQuantity(13) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 46500.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'o':
						if (Game::returnMoneyCount() >= 90000.0f) {
							boughtItem = true;
							itemInfo = "You bought Crafting Machine lvl 5";
							Game::updateMachineQuantity(14, Game::returnMachineQuantity(14) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 90000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'p':
						if (Game::returnMoneyCount() >= 600.0f) {
							boughtItem = true;
							itemInfo = "You bought Conveyor Belt";
							Game::updateMachineQuantity(15, Game::returnMachineQuantity(15) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 600.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'q':
						if (Game::returnMoneyCount() >= 850.0f) {
							boughtItem = true;
							itemInfo = "You bought Splitter(2-way)";
							Game::updateMachineQuantity(16, Game::returnMachineQuantity(16) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 850.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'r':
						if (Game::returnMoneyCount() >= 5000.0f) {
							boughtItem = true;
							itemInfo = "You bought Auto-Sell Area";
							Game::updateMachineQuantity(17, Game::returnMachineQuantity(17) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 5000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 's':
						if (Game::returnMoneyCount() >= 1000.0f) {
							boughtItem = true;
							itemInfo = "You bought Storage Area";
							Game::updateMachineQuantity(18, Game::returnMachineQuantity(18) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 1000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 't':
						if (Game::returnMoneyCount() >= 1000.0f) {
							boughtItem = true;
							itemInfo = "You bought Delivery Area";
							Game::updateMachineQuantity(19, Game::returnMachineQuantity(19) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 1000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					default:
						break;
					}
					if (shopChoice != 'u') {
						shopChoice = _getch();
					}
				}
				shopArea = 'W';
				shopChoice = '/';
				break;
			case 'b':
				shopArea = 'T';
				shopChoice = _getch();
				while (shopChoice != 'g') {
					switch (shopChoice) {
					case 'a':
						if (!assistantsHired[0] && Game::returnMoneyCount() >= 17500.0f) {
							boughtItem = true;
							itemInfo = "You hired Emilia";
							assistantsHired[0] = true;
							Game::updateMoneyCount(Game::returnMoneyCount() - 17500.0f);
						}
						else if (Game::returnMoneyCount() >= 17500.0f) {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						else if (!assistantsHired[0]) {
							boughtItem = true;
							itemInfo = "You already hired Emilia.";
						}
						break;
					case 'b':
						if (!assistantsHired[1] && Game::returnMoneyCount() >= 20000.0f) {
							boughtItem = true;
							itemInfo = "You hired Alice";
							assistantsHired[1] = true;
							Game::updateMoneyCount(Game::returnMoneyCount() - 20000.0f);
						}
						else if (Game::returnMoneyCount() >= 20000.0f) {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						else if (!assistantsHired[1]) {
							boughtItem = true;
							itemInfo = "You already hired Alice.";
						}
						break;
					case 'c':
						if (!assistantsHired[2] && Game::returnMoneyCount() >= 27000.0f) {
							boughtItem = true;
							itemInfo = "You hired Adelheid";
							assistantsHired[2] = true;
							Game::updateMoneyCount(Game::returnMoneyCount() - 27000.0f);
						}
						else if (Game::returnMoneyCount() >= 27000.0f) {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						else if (!assistantsHired[2]) {
							boughtItem = true;
							itemInfo = "You already hired Adelheid.";
						}
						break;
					case 'd':
						if (!assistantsHired[3] && Game::returnMoneyCount() >= 18500.0f) {
							boughtItem = true;
							itemInfo = "You hired Bernard";
							assistantsHired[3] = true;
							Game::updateMoneyCount(Game::returnMoneyCount() - 18500.0f);
						}
						else if (Game::returnMoneyCount() >= 20000.0f) {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						else if (!assistantsHired[3]) {
							boughtItem = true;
							itemInfo = "You already hired Bernard.";
						}
					case 'e':
						if (!assistantsHired[4] && Game::returnMoneyCount() >= 22500.0f) {
							boughtItem = true;
							itemInfo = "You hired Adler";
							assistantsHired[4] = true;
							Game::updateMoneyCount(Game::returnMoneyCount() - 22500.0f);
						}
						else if (Game::returnMoneyCount() >= 20000.0f) {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						else if (!assistantsHired[4]) {
							boughtItem = true;
							itemInfo = "You already hired Adler.";
						}
						break;
					case 'f':
						if (!assistantsHired[5] && Game::returnMoneyCount() >= 25000.0f) {
							boughtItem = true;
							itemInfo = "You hired Karl";
							assistantsHired[5] = true;
							Game::updateMoneyCount(Game::returnMoneyCount() - 25000.0f);
						}
						else if (Game::returnMoneyCount() >= 25000.0f) {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						else if (!assistantsHired[5]) {
							boughtItem = true;
							itemInfo = "You already hired Karl.";
						}
						break;
					default:
						break;
					}
					if (shopChoice != 'g') {
						shopChoice = _getch();
					}
				}
				shopArea = 'W';
				shopChoice = '/';
				break;
			case 'c':
				shopArea = 'Y';
				shopChoice = _getch();
				while (shopChoice != 'c') {
					switch (shopChoice) {
					case 'a':
						if (Game::returnMoneyCount() >= 100000.0f) {
							boughtItem = true;
							itemInfo = "You bought Factory 2";
							Game::updateMoneyCount(Game::returnMoneyCount() - 100000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					case 'b':
						if (Game::returnMoneyCount() >= 100000.0f) {
							boughtItem = true;
							itemInfo = "You bought Factory 3";
							Game::updateMoneyCount(Game::returnMoneyCount() - 100000.0f);
						}
						else {
							boughtItem = true;
							itemInfo = "Not enough money!";
						}
						break;
					default:
						break;
					}
					if (shopChoice != 'c') {
						shopChoice = _getch();
					}
				}
				shopArea = 'W';
				shopChoice = '/';
				break;
			case 'd':
				if (Game::returnMoneyCount() >= 1000000.0f) {
					boughtItem = true;
					itemInfo = "You bought German Miner Association Ownership";
					itemInfo = "Congratulations! You beat the game!";
					Game::updateMoneyCount(Game::returnMoneyCount() - 1000000.0f);
				}
				else {
					boughtItem = true;
					itemInfo = "Not enough money!";
				}
				break;

			}
			if (shopChoice != 'e') {
				shopChoice = _getch();
			}
		}
		shopArea = 'Q';
		shopChoice = '/';
		break;
	case 'b':
		shopArea = 'U';
		shopChoice = _getch();
		while (shopChoice != 'e') {
			switch (shopChoice) {
			case 'a':
				shopArea = 'I';
				shopChoice = _getch();
				while (shopChoice != 'u') {
					switch (shopChoice) {
					case 'a':
						if (Game::returnMachineQuantity(0) > 0) {
							soldItem = true;
							itemInfo = "You sold Mining Machine lvl 1";
							Game::updateMachineQuantity(0, Game::returnMachineQuantity(0) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 500.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Mining Machine lvl 1 to sell!";
						}
						break;
					case 'b':
						if (Game::returnMachineQuantity(1) > 0) {
							soldItem = true;
							itemInfo = "You sold Mining Machine lvl 2";
							Game::updateMachineQuantity(1, Game::returnMachineQuantity(1) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 2650.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Mining Machine lvl 2 to sell!";
						}
					case 'c':
						if (Game::returnMachineQuantity(2) > 0) {
							soldItem = true;
							itemInfo = "You sold Mining Machine lvl 3";
							Game::updateMachineQuantity(2, Game::returnMachineQuantity(2) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 11500.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Mining Machine lvl 3 to sell!";
						}
						break;
					case 'd':
						if (Game::returnMachineQuantity(3) > 0) {
							soldItem = true;
							itemInfo = "You sold Mining Machine lvl 4";
							Game::updateMachineQuantity(3, Game::returnMachineQuantity(3) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 30000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Mining Machine lvl 4 to sell!";
						}
						break;
					case 'e':
						if (Game::returnMachineQuantity(4) > 0) {
							soldItem = true;
							itemInfo = "You sold Mining Machine lvl 5";
							Game::updateMachineQuantity(4, Game::returnMachineQuantity(4) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 75000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Mining Machine lvl 5 to sell!";
						}
						break;
					case 'f':
						if (Game::returnMachineQuantity(5) > 0) {
							soldItem = true;
							itemInfo = "You sold Smelting Machine lvl 1";
							Game::updateMachineQuantity(5, Game::returnMachineQuantity(5) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 750.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Smelting Machine lvl 1 to sell!";
						}
						break;
					case 'g':
						if (Game::returnMachineQuantity(6) > 0) {
							soldItem = true;
							itemInfo = "You sold Smelting Machine lvl 2";
							Game::updateMachineQuantity(6, Game::returnMachineQuantity(6) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 2500.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Smelting Machine lvl 2 to sell!";
						}
						break;
					case 'h':
						if (Game::returnMachineQuantity(7) > 0) {
							soldItem = true;
							itemInfo = "You sold Smelting Machine lvl 3";
							Game::updateMachineQuantity(7, Game::returnMachineQuantity(7) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 7250.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Smelting Machine lvl 3 to sell!";
						}
						break;
					case 'i':
						if (Game::returnMachineQuantity(8) > 0) {
							soldItem = true;
							itemInfo = "You sold Smelting Machine lvl 4";
							Game::updateMachineQuantity(8, Game::returnMachineQuantity(8) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 15500.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Smelting Machine lvl 4 to sell!";
							break;
					case 'j':
						if (Game::returnMachineQuantity(9) > 0) {
							soldItem = true;
							itemInfo = "You sold Smelting Machine lvl 5";
							Game::updateMachineQuantity(9, Game::returnMachineQuantity(9) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 40000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Smelting Machine lvl 5 to sell!";
						}
						break;
					case 'k':
						if (Game::returnMachineQuantity(10) > 0) {
							soldItem = true;
							itemInfo = "You sold Crafting Machine lvl 1";
							Game::updateMachineQuantity(10, Game::returnMachineQuantity(10) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 3000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Crafting Machine lvl 1 to sell!";
						}
						break;
					case 'l':
						if (Game::returnMachineQuantity(11) > 0) {
							soldItem = true;
							itemInfo = "You sold Crafting Machine lvl 2";
							Game::updateMachineQuantity(11, Game::returnMachineQuantity(11) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 10000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Crafting Machine lvl 2 to sell!";
						}
						break;
					case 'm':
						if (Game::returnMachineQuantity(12) > 0) {
							soldItem = true;
							itemInfo = "You sold Crafting Machine lvl 3";
							Game::updateMachineQuantity(12, Game::returnMachineQuantity(12) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 23000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Crafting Machine lvl 3 to sell!";
						}
						break;
					case 'n':
						if (Game::returnMachineQuantity(13) > 0) {
							soldItem = true;
							itemInfo = "You sold Crafting Machine lvl 4";
							Game::updateMachineQuantity(13, Game::returnMachineQuantity(13) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 46500.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Crafting Machine lvl 4 to sell!";
						}
						break;
					case 'o':
						if (Game::returnMachineQuantity(14) > 0) {
							soldItem = true;
							itemInfo = "You sold Crafting Machine lvl 5";
							Game::updateMachineQuantity(14, Game::returnMachineQuantity(14) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 90000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Crafting Machine lvl 5 to sell!";
						}
						break;
					case 'p':
						if (Game::returnMachineQuantity(15) > 0) {
							soldItem = true;
							itemInfo = "You sold Conveyor Belt";
							Game::updateMachineQuantity(15, Game::returnMachineQuantity(15) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 600.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Conveyor Belt to sell!";
						}
						break;
					case 'q':
						if (Game::returnMachineQuantity(16) > 0) {
							soldItem = true;
							itemInfo = "You sold Splitter(2-way)";
							Game::updateMachineQuantity(16, Game::returnMachineQuantity(16) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 850.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Splitter(2-way) to sell!";
						}
						break;
					case 'r':
						if (Game::returnMachineQuantity(17) > 0) {
							soldItem = true;
							itemInfo = "You sold Auto-Sell Area";
							Game::updateMachineQuantity(17, Game::returnMachineQuantity(17) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 5000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Auto-Sell Area to sell!";
						}
						break;
					case 's':
						if (Game::returnMachineQuantity(18) > 0) {
							soldItem = true;
							itemInfo = "You sold Storage Area";
							Game::updateMachineQuantity(18, Game::returnMachineQuantity(18) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 1000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Storage Area to sell!";
						}
						break;
					case 't':
						if (Game::returnMachineQuantity(19) > 0) {
							soldItem = true;
							itemInfo = "You sold Delivery Area";
							Game::updateMachineQuantity(19, Game::returnMachineQuantity(19) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 1000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Delivery Area to sell!";
						}
						break;
					default:
						break;
						}
						if (shopChoice != 'u') {
							shopChoice = _getch();
						}
					}
					shopArea = 'U';
					shopChoice = '/';
					break;
			case 'b':
				shopArea = 'O';
				shopChoice = _getch();
				while (shopChoice != 'f') {
					switch (shopChoice) {
					case 'a':
						if (Game::returnItemQuantity(14) > 0) {
							soldItem = true;
							itemInfo = "You sold Pewter";
							Game::updateItemQuantity(14, Game::returnItemQuantity(14) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 960.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Pewter to sell!";
						}
						break;
					case 'b':
						if (Game::returnItemQuantity(15) > 0) {
							soldItem = true;
							itemInfo = "You sold Steel";
							Game::updateItemQuantity(15, Game::returnItemQuantity(15) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 1100.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Steel to sell!";
						}
						break;
					case 'c':
						if (Game::returnItemQuantity(16) > 0) {
							soldItem = true;
							itemInfo = "You sold Bronze";
							Game::updateItemQuantity(16, Game::returnItemQuantity(16) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 1450.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Bronze to sell!";
						}
						break;
					case 'd':
						if (Game::returnItemQuantity(17) > 0) {
							soldItem = true;
							itemInfo = "You sold Brass";
							Game::updateItemQuantity(17, Game::returnItemQuantity(17) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 2150.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Brass to sell!";
							break;
					case 'e':
						if (Game::returnItemQuantity(18) > 0) {
							soldItem = true;
							itemInfo = "You sold Diamond-infused-alloy";
							Game::updateItemQuantity(18, Game::returnItemQuantity(18) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 3000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Diamond-infused-alloy to sell!";
						}
						break;
					default:
						break;
						}
						if (shopChoice != 'f') {
							shopChoice = _getch();
						}
					}
					shopArea = 'U';
					shopChoice = '/';
					break;
			case 'c':
				shopArea = 'P';
				shopChoice = _getch();
				while (shopChoice != 'h') {
					switch (shopChoice) {
					case 'a':
						if (Game::returnItemQuantity(7) > 0) {
							soldItem = true;
							itemInfo = "You sold Tin ingot";
							Game::updateItemQuantity(7, Game::returnItemQuantity(7) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 50.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Tin ingot to sell!";
						}
						break;
					case 'b':
						if (Game::returnItemQuantity(8) > 0) {
							soldItem = true;
							itemInfo = "You sold Silver ingot";
							Game::updateItemQuantity(8, Game::returnItemQuantity(8) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 360.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Silver ingot to sell!";
						}
						break;
					case 'c':
						if (Game::returnItemQuantity(9) > 0) {
							soldItem = true;
							itemInfo = "You sold Iron ingot";
							Game::updateItemQuantity(9, Game::returnItemQuantity(9) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 540.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Iron ingot to sell!";
						}
						break;
					case 'd':
						if (Game::returnItemQuantity(10) > 0) {
							soldItem = true;
							itemInfo = "You sold Copper ingot";
							Game::updateItemQuantity(10, Game::returnItemQuantity(10) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 840.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Copper ingot to sell!";
						}
						break;
					case 'e':
						if (Game::returnItemQuantity(11) > 0) {
							soldItem = true;
							itemInfo = "You sold Zinc ingot";
							Game::updateItemQuantity(11, Game::returnItemQuantity(11) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 1250.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Zinc ingot to sell!";
						}
						break;
					case 'f':
						if (Game::returnItemQuantity(12) > 0) {
							soldItem = true;
							itemInfo = "You sold Aluminium ingot";
							Game::updateItemQuantity(12, Game::returnItemQuantity(12) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 1650.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Aluminium ingot to sell!";
						}
						break;
					case 'g':
						if (Game::returnItemQuantity(13) > 0) {
							soldItem = true;
							itemInfo = "You sold Diamond ingot";
							Game::updateItemQuantity(13, Game::returnItemQuantity(13) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 2200.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Diamond ingot to sell!";
						}
						break;
					default:
						break;
					}
					if (shopChoice != 'h') {
						shopChoice = _getch();
					}
				}
				shopArea = 'U';
				shopChoice = '/';
				break;
			case 'd':
				shopArea = 'A';
				shopChoice = _getch();
				while (shopChoice != 'h') {
					switch (shopChoice) {
					case 'a':
						soldItem = true;
						if (Game::returnItemQuantity(0) > 0) {
							soldItem = true;
							itemInfo = "You sold Tin ore";
							Game::updateItemQuantity(0, Game::returnItemQuantity(0) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 25.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Tin ore to sell!";
						}
						break;
					case 'b':
						if (Game::returnItemQuantity(1) > 0) {
							soldItem = true;
							itemInfo = "You sold Silver ore";
							Game::updateItemQuantity(1, Game::returnItemQuantity(1) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 180.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Silver ore to sell!";
						}
						break;
					case 'c':
						if (Game::returnItemQuantity(2) > 0) {
							soldItem = true;
							itemInfo = "You sold Iron ore";
							Game::updateItemQuantity(2, Game::returnItemQuantity(2) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 270.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Iron ore to sell!";
						}
						break;
					case 'd':
						if (Game::returnItemQuantity(3) > 0) {
							soldItem = true;
							itemInfo = "You sold Copper ore";
							Game::updateItemQuantity(3, Game::returnItemQuantity(3) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 420.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Copper ore to sell!";
						}
						break;
					case 'e':
						if (Game::returnItemQuantity(4) > 0) {
							soldItem = true;
							itemInfo = "You sold Zinc ore";
							Game::updateItemQuantity(4, Game::returnItemQuantity(4) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 630.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Zinc ore to sell!";
						}
						break;
					case 'f':
						if (Game::returnItemQuantity(5) > 0) {
							soldItem = true;
							itemInfo = "You sold Aluminium ore";
							Game::updateItemQuantity(5, Game::returnItemQuantity(5) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 810.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Aluminium ore to sell!";
						}
						break;
					case 'g':
						if (Game::returnItemQuantity(6) > 0) {
							soldItem = true;
							itemInfo = "You sold Diamond ore";
							Game::updateItemQuantity(6, Game::returnItemQuantity(6) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 1000.0f);
						}
						else {
							soldItem = true;
							itemInfo = "You don't have Diamond ore to sell!";
						}
						break;
					default:
						break;
					}
					if (shopChoice != 'h') {
						shopChoice = _getch();
					}
				}
				shopArea = 'U';
				shopChoice = '/';
				break;
				}
				if (shopChoice != 'e') {
					shopChoice = _getch();
				}
				}
				shopArea = 'Q';
				shopChoice = '/';
				break;
			}
		}
	case 'c':
		shopArea = 'e';
		return 'E';
	default:
		break;
	}
	return '/';
}
void Shop::setupshop()
{
	shopArea = 'Q';
}