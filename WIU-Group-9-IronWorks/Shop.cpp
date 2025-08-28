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
		while (shopChoice != 'd') {
			switch (shopChoice) {
			case 'a':
				shopArea = 'E';
				shopChoice = _getch();
				while (shopChoice != 'u') {
					switch (shopChoice) {
					case 'a':
						boughtItem = true;
						if (Game::returnMoneyCount() > 500) {
							itemInfo = "You bought Mining Machine lvl 1";
							Game::updateMachineQuantity(0, Game::returnMachineQuantity(0) + 1);
							Game::updateMoneyCount(Game::returnMoneyCount() - 500);
						}
						else {
							itemInfo = "Not enough money";
						}
						break;
					case 'b':
						boughtItem = true;
						itemInfo = "You bought Mining Machine lvl 2";
						Game::updateMachineQuantity(1, Game::returnMachineQuantity(1) + 1);
						break;
					case 'c':
						boughtItem = true;
						itemInfo = "You bought Mining Machine lvl 3";
						Game::updateMachineQuantity(2, Game::returnMachineQuantity(2) + 1);
						break;
					case 'd':
						boughtItem = true;
						itemInfo = "You bought Mining Machine lvl 4";
						Game::updateMachineQuantity(3, Game::returnMachineQuantity(3) + 1);
						break;
					case 'e':
						boughtItem = true;
						itemInfo = "You bought Mining Machine lvl 5";
						Game::updateMachineQuantity(4, Game::returnMachineQuantity(4) + 1);
						break;
					case 'f':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 1";
						Game::updateMachineQuantity(5, Game::returnMachineQuantity(5) + 1);
						break;
					case 'g':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 2";
						Game::updateMachineQuantity(6, Game::returnMachineQuantity(6) + 1);
						break;
					case 'h':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 3";
						Game::updateMachineQuantity(7, Game::returnMachineQuantity(7) + 1);
						break;
					case 'i':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 4";
						Game::updateMachineQuantity(8, Game::returnMachineQuantity(8) + 1);
						break;
					case 'j':
						boughtItem = true;
						itemInfo = "You bought Smelting Machine lvl 5";
						Game::updateMachineQuantity(9, Game::returnMachineQuantity(9) + 1);
						break;
					case 'k':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 1";
						Game::updateMachineQuantity(10, Game::returnMachineQuantity(10) + 1);
						break;
					case 'l':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 2";
						Game::updateMachineQuantity(11, Game::returnMachineQuantity(11) + 1);
						break;
					case 'm':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 3";
						Game::updateMachineQuantity(12, Game::returnMachineQuantity(12) + 1);
						break;
					case 'n':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 4";
						Game::updateMachineQuantity(13, Game::returnMachineQuantity(13) + 1);
						break;
					case 'o':
						boughtItem = true;
						itemInfo = "You bought Crafting Machine lvl 5";
						Game::updateMachineQuantity(14, Game::returnMachineQuantity(14) + 1);
						break;
					case 'p':
						boughtItem = true;
						itemInfo = "You bought Conveyor Belt";
						Game::updateMachineQuantity(15, Game::returnMachineQuantity(15) + 1);
						break;
					case 'q':
						boughtItem = true;
						itemInfo = "You bought Splitter(2-way)";
						Game::updateMachineQuantity(16, Game::returnMachineQuantity(16) + 1);
						break;
					case 'r':
						boughtItem = true;
						itemInfo = "You bought Auto-Sell Area";
						Game::updateMachineQuantity(17, Game::returnMachineQuantity(17) + 1);
						break;
					case 's':
						boughtItem = true;
						itemInfo = "You bought Storage Area";
						Game::updateMachineQuantity(18, Game::returnMachineQuantity(18) + 1);
						break;
					case 't':
						boughtItem = true;
						itemInfo = "You bought Delivery Area";
						Game::updateMachineQuantity(19, Game::returnMachineQuantity(19) + 1);
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
			case 'c':
				shopArea = 'Y';
				shopChoice = _getch();
				while (shopChoice != 'c') {
					switch (shopChoice) {
					case 'a':
						boughtItem = true;
						itemInfo = "You bought Factory 2";
						break;
					case 'b':
						boughtItem = true;
						itemInfo = "You bought Factory 3";
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
		while (shopChoice != 'e') {
			switch (shopChoice) {
			case 'a':
				shopArea = 'I';
				shopChoice = _getch();
				while (shopChoice != 'u') {
					switch (shopChoice) {
					case 'a':
						soldItem = true;
						if (Game::returnMachineQuantity(0) > 0) {
							itemInfo = "You sold Mining Machine lvl 1";
							Game::updateMachineQuantity(0, Game::returnMachineQuantity(0) - 1);
							Game::updateMoneyCount(Game::returnMoneyCount() + 500);
						}
						else {
							itemInfo = "No more items of this type to sell";
						}
						break;
					case 'b':
						soldItem = true;
						itemInfo = "You sold Mining Machine lvl 2";
						Game::updateMachineQuantity(1, Game::returnMachineQuantity(1) - 1);
						break;
					case 'c':
						soldItem = true;
						itemInfo = "You sold Mining Machine lvl 3";
						Game::updateMachineQuantity(2, Game::returnMachineQuantity(2) - 1);
						break;
					case 'd':
						soldItem = true;
						itemInfo = "You sold Mining Machine lvl 4";
						Game::updateMachineQuantity(3, Game::returnMachineQuantity(3) - 1);
						break;
					case 'e':
						soldItem = true;
						itemInfo = "You sold Mining Machine lvl 5";
						Game::updateMachineQuantity(4, Game::returnMachineQuantity(4) - 1);
						break;
					case 'f':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 1";
						Game::updateMachineQuantity(5, Game::returnMachineQuantity(5) - 1);
						break;
					case 'g':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 2";
						Game::updateMachineQuantity(6, Game::returnMachineQuantity(6) - 1);
						break;
					case 'h':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 3";
						Game::updateMachineQuantity(7, Game::returnMachineQuantity(7) - 1);
						break;
					case 'i':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 4";
						Game::updateMachineQuantity(8, Game::returnMachineQuantity(8) - 1);
						break;
					case 'j':
						soldItem = true;
						itemInfo = "You sold Smelting Machine lvl 5";
						Game::updateMachineQuantity(9, Game::returnMachineQuantity(9) - 1);
						break;
					case 'k':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 1";
						Game::updateMachineQuantity(10, Game::returnMachineQuantity(10) - 1);
						break;
					case 'l':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 2";
						Game::updateMachineQuantity(11, Game::returnMachineQuantity(11) - 1);
						break;
					case 'm':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 3";
						Game::updateMachineQuantity(12, Game::returnMachineQuantity(12) - 1);
						break;
					case 'n':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 4";
						Game::updateMachineQuantity(13, Game::returnMachineQuantity(13) - 1);
						break;
					case 'o':
						soldItem = true;
						itemInfo = "You sold Crafting Machine lvl 5";
						Game::updateMachineQuantity(14, Game::returnMachineQuantity(14) - 1);
						break;
					case 'p':
						soldItem = true;
						itemInfo = "You sold Conveyor Belt";
						Game::updateMachineQuantity(15, Game::returnMachineQuantity(15) - 1);
						break;
					case 'q':
						soldItem = true;
						itemInfo = "You sold Splitter(2-way)";
						Game::updateMachineQuantity(16, Game::returnMachineQuantity(16) - 1);
						break;
					case 'r':
						soldItem = true;
						itemInfo = "You sold Auto-Sell Area";
						Game::updateMachineQuantity(17, Game::returnMachineQuantity(17) - 1);
						break;
					case 's':
						soldItem = true;
						itemInfo = "You sold Storage Area";
						Game::updateMachineQuantity(18, Game::returnMachineQuantity(18) - 1);
						break;
					case 't':
						soldItem = true;
						itemInfo = "You sold Delivery Area";
						Game::updateMachineQuantity(19, Game::returnMachineQuantity(19) - 1);
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
						Game::updateItemQuantity(14, Game::returnItemQuantity(14) - 1);
						break;
					case 'b':
						soldItem = true;
						itemInfo = "You sold Steel";
						Game::updateItemQuantity(15, Game::returnItemQuantity(15) - 1);
						break;
					case 'c':
						soldItem = true;
						itemInfo = "You sold Bronze";
						Game::updateItemQuantity(16, Game::returnItemQuantity(16) - 1);
						break;
					case 'd':
						soldItem = true;
						itemInfo = "You sold Brass";
						Game::updateItemQuantity(17, Game::returnItemQuantity(17) - 1);
						break;
					case 'e':
						soldItem = true;
						itemInfo = "You sold Diamond-infused-alloy";
						Game::updateItemQuantity(18, Game::returnItemQuantity(18) - 1);
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
						itemInfo = "You sold Tin ingot";
						Game::updateItemQuantity(7, Game::returnItemQuantity(7) - 1);
						break;
					case 'b':
						soldItem = true;
						itemInfo = "You sold Silver ingot";
						Game::updateItemQuantity(8, Game::returnItemQuantity(8) - 1);
						break;
					case 'c':
						soldItem = true;
						itemInfo = "You sold Iron ingot";
						Game::updateItemQuantity(9, Game::returnItemQuantity(9) - 1);
						break;
					case 'd':
						soldItem = true;
						itemInfo = "You sold Copper ingot";
						Game::updateItemQuantity(10, Game::returnItemQuantity(10) - 1);
						break;
					case 'e':
						soldItem = true;
						itemInfo = "You sold Zinc ingot";
						Game::updateItemQuantity(11, Game::returnItemQuantity(11) - 1);
						break;
					case 'f':
						soldItem = true;
						itemInfo = "You sold Aluminium ingot";
						Game::updateItemQuantity(12, Game::returnItemQuantity(12) - 1);
						break;
					case 'g':
						soldItem = true;
						itemInfo = "You sold Diamond Ingots";
						Game::updateItemQuantity(13, Game::returnItemQuantity(13) - 1);
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
						itemInfo = "You sold Tin ore";
						Game::updateItemQuantity(0, Game::returnItemQuantity(0) - 1);
						break;
					case 'b':
						soldItem = true;
						itemInfo = "You sold Silver ore";
						Game::updateItemQuantity(1, Game::returnItemQuantity(1) - 1);
						break;
					case 'c':
						soldItem = true;
						itemInfo = "You sold Iron ore";
						Game::updateItemQuantity(2, Game::returnItemQuantity(2) - 1);
						break;
					case 'd':
						soldItem = true;
						itemInfo = "You sold Copper ore";
						Game::updateItemQuantity(3, Game::returnItemQuantity(3) - 1);
						break;
					case 'e':
						soldItem = true;
						itemInfo = "You sold Zinc ore";
						Game::updateItemQuantity(4, Game::returnItemQuantity(4) - 1);
						break;
					case 'f':
						soldItem = true;
						itemInfo = "You sold Aluminium ore";
						Game::updateItemQuantity(5, Game::returnItemQuantity(5) - 1);
						break;
					case 'g':
						soldItem = true;
						itemInfo = "You sold Diamond ore";
						Game::updateItemQuantity(6, Game::returnItemQuantity(6) - 1);
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
	case 'c':
		shopArea = 'e';
		return 'l';
	default:
		return '/';
	}
	return '/';
}
void Shop::setupshop()
{
	shopArea = 'Q';
}