#include "Game.h"
#include "Factory.h"
#include "Mine.h"
#include "Inventory.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <chrono>
#pragma comment(lib, "Winmm.lib")
#include <mmsystem.h>
using std::cout;
using std::endl;
using steadyClock = std::chrono::steady_clock;
using seconds = std::chrono::duration<float>;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

// Initialising static values
char Game::factoryWorlds[3][20][20];
float Game::money = 0.0f;

Game::Game()
{
    // Miscellaneous
    keyPressed = -1000;
	sceneArea = 'W';
    prevSceneArea = '/';
    action = '/';
	gameStatus = true;
    visible = true;
    menuChoice = 0;
    start = steadyClock::now();
    lineFinished = false;
    storyDone = false;
    goNextLine = false;
    inInventory = false;
    skip = false;

    // Setting up factory board
    for (int f = 0;f < 3;f++) {
        for (int r = 0;r < 20;r++) {
            for (int c = 0;c < 20;c++) {
                factoryWorlds[f][r][c] = ' ';
            }
        }
    }
}

void Game::gameDisplay()
{
	while (gameStatus) {
        switch (sceneArea) {
        // Main menu
        case 'W':
            menuScreen();
            menuChoice = 0;
            PlayMusic(L"Menu.mp3", true);
            while (sceneArea == 'W') {
                for (int i = 0;i < 3;i++) {
                    overwriteText(options[i], 0, 34 + i, true, choiceColours[i]);
                }
                if (!visible) {
                    overwriteText(options[menuChoice], 0, 34 + menuChoice, visible, choiceColours[menuChoice]);
                }
                visible = !visible;
                Sleep(250);
            }
            break;
        // Story intro
        case 'N':
            storyScreen();
            while (sceneArea == 'N') {
                continue;
			}
            break;
        // Factory area
        case 'F':
            PlayMusic(L"Factory.mp3", true);
            factory.drawScreen();
            while (sceneArea == 'F') {
                float dt = obtainDeltaTime();
                factory.updateScreen(dt);
            }
            break;
        // Mine area
        case 'M':
            PlayMusic(L"Mine.mp3", true);
            mine.drawMine();
            while (sceneArea == 'M') {
                mine.update();
            }
            break;
        // Inventory menu
        case 'I':
            inventory.displayWhichInventory(); // Show inventory choice menu initially

            // Loop while the player is in the inventory
            while (inInventory) {
                if (inventory.needsRedraw) {  // Only redraw if something changed (flag is set)
                    system("cls"); // clear the console
                    if (inventory.isChoosingInventory) {
                        inventory.displayWhichInventory(); // Show inventory selection menu
                    }
                    else {
                        inventory.displayInventory(); // Show selected inventory
                        inventory.displayOreInfo(); // Show info about selected ore
                        inventory.displayResourceInfo(); // Show info about selected resource
                        inventory.displayMachineInfo(); // Show info about selected machine
                    }

                    inventory.needsRedraw = false; // reset flag

                    Sleep(10); // Small delay to reduce CPU usage
                }
            }
            break;
        // Save screen
        case 'C':
            saveScreen();
            while (sceneArea == 'C') {
                continue;
            }
            break;
        // Pause screen
        case 'P':
            pauseScreen();
            while (sceneArea == 'P') {
                continue;
            }
            break;
        // Exiting program
        case 'E':
            break;
        default:
            cout << "Display error" << endl;
            break;
        }
        // clear screen
        system("cls");

        // Reset color
        SetConsoleTextAttribute(h, 0x0F);
	}
}

void Game::gameInput()
{
	while (gameStatus) {
        switch (sceneArea) {
        // Main menu
        case 'W':
            keyPressed = _getch();
            while (keyPressed != 13) {
                // Checking if up or down arrow was pressed
                if (keyPressed == 119) {
                    menuChoice--;
                }
                else if (keyPressed == 115) {
                    menuChoice++;
                }

                // Fixing out of range values
                if (menuChoice < 0) {
                    menuChoice = 2;
                }
                else if (menuChoice > 2) {
                    menuChoice = 0;
                }

                keyPressed = _getch();
            }
            sceneArea = destinations[menuChoice];
            break;
        // Story segment
        case 'N':
            keyPressed = _getch();
            if (keyPressed == 13) {
                if (lineFinished) {
                    goNextLine = true;
                }
                else {
                    skip = true;
                }
                Sleep(10);
            }
            if (storyDone) {
                sceneArea = 'F';
            }
            break;
        // Factory map
        case 'F':
            action = factory.factoryInput();
            // Go pause screen
            if (action == 'P') {
                sceneArea = 'P';
                prevSceneArea = 'F';
            }
            else if (action == 'M') {
                sceneArea = 'M';
            }
            else if (action == 'I') {
                sceneArea = 'I';
            }
            break;
        // Mine map
        case 'M':
            action = mine.mineInput();
            if (action == 'P') {
                sceneArea = 'P';
                prevSceneArea = 'M';
            }
            else if (action == 'F') {
                sceneArea = 'F';
            }
            break;
        // Inventory menu
        case 'I':
            inInventory = true; // Set flag that player is inside inventory 

            // Loop until inventory.moveAround() returns false (player exits)
            while (inventory.moveAround()) {
                continue; // keep moving around until exit
            }
            inInventory = false; // Player has exited the inventory
            sceneArea = 'F';
            break;
        // Pause screen
        case 'P':
            keyPressed = _getch();
            if (keyPressed == 109) {
                sceneArea = 'W';
            }
            if (keyPressed == 112) {
                sceneArea = prevSceneArea;
            }
            break;
        // Save screen
        case 'C':
            keyPressed = _getch();
            sceneArea = 'W';
            break;
        // Exiting program
        case 'E':
            gameStatus = false;
            break;
        // To catch errors
        default:
            cout << "input error" << endl;
            break;
        }
	}
}

void Game::menuScreen() // created by justin and yuon  
{
    // Set color for the title
    SetConsoleTextAttribute(h, 0x0E); // Yellow

    std::cout <<
        R"(
  _____                   
 |_   _|                                            _
   | |  ____  _____   _ _\ \          / _____  ____| | ______
   | | |  __|/  _  \ | '_ \ \   /\   / /  _  \|  __| |/ / __/
  _| |_| |   | (_) | | | | \ \_/  \_/ /| (_) || |  |   <\__ \
 |_____|_|   \_____/ |_| |_|\__/ \___/ \_____/|_|  |_|\_/___/
)" << std::endl; // R"() is a raw string literal

    std::cout << R"(
                  %%%%%%%%%%%%%%%%%
                  %%%%%%%%%%%%%%%%%
               %%%#---===++++++===@%%%%%####
               %%%#-===++++++++===@%%%######
                  %%%%@@@@@@@@@+++++++@@#%%@
                   %%%@@@@@@@@@###+==+++@%@@
                               %%%@==+++@@@@
                            %%%###%@@#+++==+@@@
                            %%%###%%%#+++==+@@@
                         %%%@@@%%%@  @@@#+++@@@
                      %%%######%@@@  @@@#+++@@@
                     %%%%###%%%@     @@@#+++@@@
                  %%%#@@@%%@@        @@@#==+@@@
                  %%%#@@@%%%@        @@@#==+@@@
               %%%####%%%            @@@#--=@@@
            %%%#######%%@            @@@#==+@@@
            %%%#@@@%%%                  @@@@
         %%%####%%%@@@                   @@@
         %%%####%%@
      %%%@@#%%%
      %%%#@#@%@
    %%%%%%@
    @@@@@@@

)";

    // Set color for subtitle
    SetConsoleTextAttribute(h, 0x0B); // Aqua
    std::cout << "Welcome to IronWorks!" << std::endl;

    // Set color for prompt
    std::cout << "Start New Game" << std::endl;
    std::cout << "Continue Game" << std::endl;
    std::cout << "Exit" << std::endl;
}

void Game::saveScreen()
{
    cout << "Nothing here for now" << endl;
    cout << "Press any key to go back to the main menu" << endl;
}

void Game::pauseScreen()
{
    cout << "Pause menu" << endl;
    cout << "Click M to go Menu" << endl;
    cout << "Click P to unpause" << endl;
}

void Game::storyScreen()
{
    storyDone = false;

    std::ifstream f("ironworksstory.txt");
    std::string s;

    if (!f.is_open()) {
        std::cout << "Error opening the file" << std::endl;
    }

    while (std::getline(f, s)) {
        lineFinished = false;
        skip = false;
        for (int i = 0; i < s.size(); i++) { // Text generation
            std::cout << s[i];
            Sleep(25);
            
            if (skip) {
                for (int j = i + 1; j < s.size();j++) {
                    std::cout << s[j];
                }
                break;
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        lineFinished = true;
        while (!goNextLine) {
            continue;
        }
        goNextLine = false;
    }
    storyDone = true;
}

// Code provided by chatgpt with some minor changes by Rendell
void Game::overwriteText(const std::string& text, int x, int y, bool show, int colour)
{
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(h, coord);
    SetConsoleTextAttribute(h, colour);

    if (show) {
        std::cout << text;
    }
    else {
        SetConsoleTextAttribute(h, 0x0F);
        std::cout << std::string(text.size(), ' '); // blank it
    }

    // Reset after use
    SetConsoleTextAttribute(h, 0x0F);
}

// Code provided by chatgpt with some minor changes by Rendell
void Game::clearArea(int x, int y, int width, int height) {
    COORD coord;
    DWORD count;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int row = 0; row < height; row++) {
        coord.X = x;
        coord.Y = y + row;
        FillConsoleOutputCharacter(hConsole, ' ', width, coord, &count);
        FillConsoleOutputAttribute(hConsole, 0x0F, width, coord, &count); // reset attributes to white
    }
}

// Full screen code provided by a stack overflow user
void Game::fullsc()
{
    HWND Hwnd = GetForegroundWindow();
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    LONG winstyle = GetWindowLong(Hwnd, GWL_STYLE);
    SetWindowLong(Hwnd, GWL_STYLE, (winstyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(Hwnd, HWND_TOP, 0, 0, x, y, 0);

}

// Code made with the assistance of chatgpt
// Obtains delta time when called
float Game::obtainDeltaTime()
{
    static bool first = true;
    auto currentTime = steadyClock::now();

    // List of frozen scenes
    if (sceneArea == 'W' || sceneArea == 'N' || sceneArea == 'C' || sceneArea == 'P' || sceneArea == 'E') {
        start = currentTime;
        return 0.0f;
    }

    seconds dt = currentTime - start;
    start = currentTime;
    return dt.count();
}

void Game::ShowConsoleCursor(bool showCursor) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showCursor; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// ---- Music via MCI ----
void Game::PlayMusic(const std::wstring& filename, bool repeat) {
    // Stop any existing music if its a repeating ost
    if (repeat) {
        StopMusic();
    }
    
    std::wstring extra[2] = { L"", L" repeat" };
    
    std::wstring command = L"open \"" + filename + L"\" type mpegvideo alias mp3";
    mciSendString(command.c_str(), NULL, 0, NULL);

    // Checking if the audio is playing on repeat
    std::wstring playCommand = L"play mp3" + extra[repeat];
    mciSendString(playCommand.c_str(), NULL, 0, NULL);
}

void Game::StopMusic() {
    mciSendString(L"stop mp3", NULL, 0, NULL);
    mciSendString(L"close mp3", NULL, 0, NULL);
}

void Game::updateFactoryWorld(int x, int y, int factoryNo, char value)
{
    factoryWorlds[factoryNo][y][x] = value;
}

void Game::updateMoneyCount(float value)
{
    money = value;
}

const char Game::returnFactoryEntity(int x, int y, int factoryNo)
{
    return factoryWorlds[factoryNo][y][x];
}

const float Game::returnMoneyCount()
{
    return money;
}

Game::~Game()
{
	cout << "Game finished" << endl;
}
