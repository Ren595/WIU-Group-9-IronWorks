#include "assistantSelection.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <map>
#include <Windows.h>
#include "Game.h"

assistantselection::assistantselection() {
	selectionChoice = '/';
	selectionArea = 'Q';
	for (int i = 0; i < 6; i++) {
		assistantAssigned[i] = false;
	}
	for (int i = 0; i < 3; i++) {
		factoryAssigned[i] = false;
	}
}

void assistantselection::selectionDisplay() {
	system("cls");
	switch (selectionArea) {
	case 'Q':
		std::cout << FACTORY_SELECTION_MENU_ART << std::endl;
		while (selectionArea == 'Q') {
			continue;
		}
		break;
	case 'W':
		std::cout << ASSISTANT_SELECTION_MENU1_ART << std::endl;
		while (selectionArea == 'W') {
			if (assistantSelected) {
				std::cout << assignmentInfo << std::endl;
				assistantSelected = false;
			}
			Sleep(10);
		}
		break;
	case 'E':
		std::cout << ASSISTANT_SELECTION_MENU2_ART << std::endl;
		while (selectionArea == 'E') {
			if (assistantSelected) {
				std::cout << assignmentInfo << std::endl;
				assistantSelected = false;
			}
			Sleep(10);
		}
		break;
	case 'R':
		std::cout << ASSISTANT_SELECTION_MENU3_ART << std::endl;
		while (selectionArea == 'R') {
			if (assistantSelected) {
				std::cout << assignmentInfo << std::endl;
				assistantSelected = false;
			}
			Sleep(10);
		}
		break;
	case 'T':
		break;
	default:
		std::cout << "Display error" << std::endl;
		break;
	}
		
}

char assistantselection::selectionInput()
{
	selectionChoice = _getch();
	switch (selectionChoice) {
	case 'a':
		selectionArea = 'W';
		selectionChoice = _getch();
		while (selectionChoice != 'g') {
			switch (selectionChoice) {
			case 'a':
				if (factoryAssigned[0]) {
					assistantSelected = true;
					assignmentInfo = "Factory 1 already has an assistant!";
				}
				else if (!assistantAssigned[0]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Emilia to factory 1.";
					assistantAssigned[0] = true;
					factoryAssigned[0] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Emilia to a factory.";
				}
				break;
			case 'b':
				if (factoryAssigned[0]) {
					assistantSelected = true;
					assignmentInfo = "Factory 1 already has an assistant!";
				}
				else if (!assistantAssigned[1]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Alice to factory 1.";
					assistantAssigned[1] = true;
					factoryAssigned[0] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Alice to a factory.";
				}
				break;
			case 'c':
				if (factoryAssigned[0]) {
					assistantSelected = true;
					assignmentInfo = "Factory 1 already has an assistant!";
				}
				else if (!assistantAssigned[2]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Adelheid to factory 1.";
					assistantAssigned[2] = true;
					factoryAssigned[0] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Adelheid to a factory.";
				}
				break;
			case 'd':
				if (factoryAssigned[0]) {
					assistantSelected = true;
					assignmentInfo = "Factory 1 already has an assistant!";
				}
				else if (!assistantAssigned[3]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Bernard to factory 1.";
					assistantAssigned[3] = true;
					factoryAssigned[0] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Bernard to a factory.";
				}
				break;
			case 'e':
				if (factoryAssigned[0]) {
					assistantSelected = true;
					assignmentInfo = "Factory 1 already has an assistant!";
				}
				else if (!assistantAssigned[4]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Adler to factory 1.";
					assistantAssigned[4] = true;
					factoryAssigned[0] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Adler to a factory.";
				}
				break;
			case 'f':
				if (factoryAssigned[0]) {
					assistantSelected = true;
					assignmentInfo = "Factory 1 already has an assistant!";
				}
				else if (!assistantAssigned[5]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Karl to factory 1.";
					assistantAssigned[5] = true;
					factoryAssigned[0] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Karl to a factory.";
				}
				break;
			default:
				break;
			}
			if (selectionChoice != 'g') {
				selectionChoice = _getch();
			}
		}
		selectionArea = 'Q';
		selectionChoice = '/';
		break;
	case 'b':
		selectionArea = 'E';
		selectionChoice = _getch();
		while (selectionChoice != 'g') {
			switch (selectionChoice) {
			case 'a':
				if (factoryAssigned[1]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[0]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Emilia to factory 2.";
					assistantAssigned[0] = true;
					factoryAssigned[1] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Emilia to a factory.";
				}
			case 'b':
				if (factoryAssigned[1]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[1]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Alice to factory 2.";
					assistantAssigned[1] = true;
					factoryAssigned[1] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Alice to a factory.";
				}
				break;
			case 'c':
				if (factoryAssigned[1]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[2]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Adelheid to factory 2.";
					assistantAssigned[2] = true;
					factoryAssigned[1] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Adelheid to a factory.";
				}
				break;
			case 'd':
				if (factoryAssigned[1]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[3]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Bernard to factory 2.";
					assistantAssigned[3] = true;
					factoryAssigned[1] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Bernard to a factory.";
				}
				break;
			case 'e':
				if (factoryAssigned[1]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[4]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Adler to factory 2.";
					assistantAssigned[4] = true;
					factoryAssigned[1] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Adler to a factory.";
				}
				break;
			case 'f':
				if (factoryAssigned[1]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[5]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Karl to factory 2.";
					assistantAssigned[5] = true;
					factoryAssigned[1] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Karl to a factory.";
				}
				break;
			default:
				break;
			}
			if (selectionChoice != 'g') {
				selectionChoice = _getch();
			}
		}
		selectionArea = 'Q';
		selectionChoice = '/';
		break;
	case 'c':
		selectionArea = 'R';
		selectionChoice = _getch();
		while (selectionChoice != 'g') {
			switch (selectionChoice) {
			case 'a':
				if (factoryAssigned[2]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[0]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Emilia to factory 3.";
					assistantAssigned[0] = true;
					factoryAssigned[2] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Emilia to a factory.";
				}
				break;
			case 'b':
				if (factoryAssigned[2]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[1]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Alice to factory 3.";
					assistantAssigned[1] = true;
					factoryAssigned[2] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Alice to a factory.";
				}
				break;
			case 'c':
				if (factoryAssigned[2]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[2]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Adelheid to factory 3.";
					assistantAssigned[2] = true;
					factoryAssigned[2] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Adelheid to a factory.";
				}
				break;
			case 'd':
				if (factoryAssigned[2]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[3]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Bernard to factory 3.";
					assistantAssigned[3] = true;
					factoryAssigned[2] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Bernard to a factory.";
				}
				break;
			case 'e':
				if (factoryAssigned[2]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[4]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Adler to factory 3.";
					assistantAssigned[4] = true;
					factoryAssigned[2] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Adler to a factory.";
				}
				break;
			case 'f':
				if (factoryAssigned[2]) {
					assistantSelected = true;
					assignmentInfo = "Factory 2 already has an assistant!";
				}
				else if (!assistantAssigned[5]) {
					assistantSelected = true;
					assignmentInfo = "You assigned Karl to factory 3.";
					assistantAssigned[5] = true;
					factoryAssigned[2] = true;
				}
				else {
					assistantSelected = true;
					assignmentInfo = "You already assigned Karl to a factory.";
				}
				break;
			default:
				break;
			}
			if (selectionChoice != 'g') {
				selectionChoice = _getch();
			}
		}
		selectionArea = 'Q';
		selectionChoice = '/';
		break;
	case 'd':
		selectionArea = 'T';
		return 'l';
	default:
		return '/';
	}
}