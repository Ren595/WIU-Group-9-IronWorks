#include "Shop.h"
#include "Inventory.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <map>
#include <Windows.h>
#include "Game.h"

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
	case 'R':
		std::cout << BUY_WORKER_MENU_ART << std::endl;
		while (shopArea == 'R') {
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
		std::cout << SELL_MINED_ORES_MENU_ART << std::endl;
		while (shopArea == 'P') {
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
		while (shopChoice != 'd') {
			switch (shopChoice) {
			case 'a':
				shopArea = 'E';
				shopChoice = _getch();
				while (shopChoice != 'u') {

					switch (shopChoice) {
					case 'a':
						boughtItem = true;
						itemInfo = "You bought Mining Machine lvl 1";	
						break;
					case 'b':
						boughtItem = true;
						itemInfo = "You bought Mining Machine lvl 2";
						break;
					case 'c':
						boughtItem = true;
						itemInfo = "You bought Mining Machine lvl 3";
						break;
					case 'd':
						boughtItem = true;
						itemInfo = "You bought Mining Machine lvl 4";
						break;
					case 'e':
						boughtItem = true;
						itemInfo = "You bought Mining Machine lvl 5";
						break;
					case 'f':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 1";
						break;
					case 'g':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 2";
						break;
					case 'h':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 3";
						break;
					case 'i':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 4";
						break;
					case 'j':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 5";
						break;
					case 'k':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 1";
						break;
					case 'l':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 2";
						break;
					case 'm':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 3";
						break;
					case 'n':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 4";
						break;
					case 'o':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 5";
						break;
					case 'p':
						boughtItem = true;
						itemInfo = "You bought Conveyor Belt";
						break;
					case 'q':
						boughtItem = true;
						itemInfo = "You bought Splitter(2-way)";
						break;
					case 'r':
						boughtItem = true;
						itemInfo = "You bought Auto-Sell Area";
						break;
					case 's':
						boughtItem = true;
						itemInfo = "You bought Storage Area";
						break;
					case 't':
						boughtItem = true;
						itemInfo = "You bought Delivery Area";
						break;;
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
				shopArea = 'R';
				shopChoice = _getch();
				while (shopChoice != 'b') {
					switch (shopChoice) {
					case 'a':
						boughtItem = true;
						itemInfo = "You bought a Worker";
						break;
					default:
						break;
					}
					if (shopChoice != 'b') {
						shopChoice = _getch();
					}
				}
				shopArea = 'W';
				shopChoice = '/';
				break;
			case 'c':
				shopArea = 'T';
				shopChoice = _getch();
				while (shopChoice != 'g') {
					switch (shopChoice) {
					case 'a':
						if (!assistantsHired[0]) {
							boughtItem = true;
							itemInfo = "You hired Emilia.";
							assistantsHired[0] = true;
						}
						else {
							boughtItem = true;
							itemInfo = "You already hired Emilia.";
						}

						break;
					case 'b':
						if (!assistantsHired[1]) {
							boughtItem = true;
							itemInfo = "You hired Alice.";
							assistantsHired[1] = true;
						}
						else {
							boughtItem = true;
							itemInfo = "You already hired Alice.";
						}
						break;
					case 'c':
						if (!assistantsHired[2]) {
							boughtItem = true;
							itemInfo = "You hired Adelheid.";
							assistantsHired[2] = true;
						}
						else {
							boughtItem = true;
							itemInfo = "You already hired Adelheid.";
						}
						break;
					case 'd':
						if (!assistantsHired[3]) {
							boughtItem = true;
							itemInfo = "You hired Bernard.";
							assistantsHired[3] = true;
						}
						else {
							boughtItem = true;
							itemInfo = "You already hired Bernard.";
						}
						break;
					case 'e':
						if (!assistantsHired[4]) {
							boughtItem = true;
							itemInfo = "You hired Karl.";
							assistantsHired[4] = true;
						}
						else {
							boughtItem = true;
							itemInfo = "You already hired Karl.";
						}
						break;
					case 'f':
						if (!assistantsHired[5]) {
							boughtItem = true;
							itemInfo = "You hired Adler.";
							assistantsHired[5] = true;
						}
						else {
							boughtItem = true;
							itemInfo = "You already hired Adler.";
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
			}
			if (shopChoice != 'd') {
				shopChoice = _getch();
			}
		}
		shopArea = 'Q';
		shopChoice = '/';
		break;
	case 'b':
		shopArea = 'U';
		shopChoice = _getch();
		while (shopChoice != 'd') {
			switch (shopChoice) {
			case 'a':
				shopArea = 'I';
				shopChoice = _getch();
				while (shopChoice != 'u') {
					switch (shopChoice) {
					case 'a':
						soldItem = true;
						itemInfo = "You sold Mining Machine lvl 1";
						break;
					case 'b':
						soldItem = true;
						itemInfo = "You sold Mining Machine lvl 2";
						break;
					case 'c':
						soldItem = true;
						itemInfo = "You sold Mining Machine lvl 3";
						break;
					case 'd':
						soldItem = true;
						itemInfo = "You sold Mining Machine lvl 4";
						break;
					case 'e':
						soldItem = true;
						itemInfo = "You sold Mining Machine lvl 5";
						break;
					case 'f':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 1";
						break;
					case 'g':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 2";
						break;
					case 'h':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 3";
						break;
					case 'i':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 4";
						break;
					case 'j':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 5";
						break;
					case 'k':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 1";
						break;
					case 'l':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 2";
						break;
					case 'm':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 3";
						break;
					case 'n':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 4";
						break;
					case 'o':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 5";
						break;
					case 'p':
						soldItem = true;
						itemInfo = "You sold Conveyor Belt";
						break;
					case 'q':
						soldItem = true;
						itemInfo = "You sold Splitter(2-way)";
						break;
					case 'r':
						soldItem = true;
						itemInfo = "You sold Auto-Sell Area";
						break;
					case 's':
						soldItem = true;
						itemInfo = "You sold Storage Area";
						break;
					case 't':
						soldItem = true;
						itemInfo = "You sold Delivery Area";
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
						soldItem = true;
						itemInfo = "You sold Pewter";
						break;
					case 'b':
						soldItem = true;
						itemInfo = "You sold Steel";
						break;
					case 'c':
						soldItem = true;
						itemInfo = "You sold Bronze";
						break;
					case 'd':
						soldItem = true;
						itemInfo = "You sold Brass";
						break;
					case 'e':
						soldItem = true;
						itemInfo = "You sold Diamond-infused-alloy";
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
						soldItem = true;
						itemInfo = "You sold Tin ore";
						break;
					case 'b':
						soldItem = true;
						itemInfo = "You sold Silver ore";
						break;
					case 'c':
						soldItem = true;
						itemInfo = "You sold Iron ore";
						break;
					case 'd':
						soldItem = true;
						itemInfo = "You sold Copper ore";
						break;
					case 'e':
						soldItem = true;
						itemInfo = "You sold Zinc ore";
						break;
					case 'f':
						soldItem = true;
						itemInfo = "You sold Aluminium ore";
						break;
					case 'g':
						soldItem = true;
						itemInfo = "You sold Diamond ore";
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
			if (shopChoice != 'd') {
				shopChoice = _getch();
			}
		}
		shopArea = 'Q';
		shopChoice = '/';
		break;
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


