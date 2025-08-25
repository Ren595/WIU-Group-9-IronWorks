// Including local header files
#include "Game.h"
#include "Factory.h"
#include "Mine.h"
#include "Inventory.h"
#include "Shop.h"

// Inlcuding standard libraries and headers
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>

// Including library for audio
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
	sceneArea = 'F';
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
                Sleep(10);
			}
            break;
        // Factory area
        case 'F':
            PlayMusic(L"Factory OST.mp3", true);
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
        // Shop screen
        case 'S':
            PlayMusic(L"Shop.mp3", true);
            while (sceneArea == 'S') {
                shop.shopDisplay();
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
                // Checking if W or S was pressed
                if (keyPressed == 'W' || keyPressed == 'w') {
                    menuChoice--;
                }
                else if (keyPressed == 'S' || keyPressed == 's') {
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
            else if (action == 'S') {
                sceneArea = 'S';
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
        // Shop screen
        case 'S':
            action = shop.shopInput();
            if (action == 'E') {
                sceneArea = 'F';
            }
            break;
        // Pause screen
        case 'P':
            keyPressed = _getch();
            if (keyPressed == 'M' || keyPressed == 'm') {
                sceneArea = 'W';
            }
            if (keyPressed == 'P' || keyPressed == 'p') {
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

//void Game::saveScreen() {
//    system("cls");
//    const char* saveSlots[] = { "SAVE SLOT 1", "SAVE SLOT 2", "SAVE SLOT 3", "SAVE SLOT 4", "SAVE SLOT 5" };
//    int selection = 0;
//    bool showBlink = true;
//    COORD menuStart = { 5, 10 };
//    while (true) {
//        // Instructions
//        SetConsoleCursorPosition(h, { 5, (SHORT)(menuStart.Y - 2) });
//        SetConsoleTextAttribute(h, 11);
//        cout << "Use ARROW KEYS to move, ENTER to select, BACKSPACE to return.            ";
//        // Menu display
//        for (int i = 0; i < 5; i++) {
//            SetConsoleCursorPosition(h, { menuStart.X, (SHORT)(menuStart.Y + i) });
//            if (i == selection) {
//                SetConsoleTextAttribute(h, showBlink ? 11 : 15);
//                cout << "> " << saveSlots[i] << " <   ";
//            }
//            else {
//                SetConsoleTextAttribute(h, 7);
//                cout << "  " << saveSlots[i] << "     ";
//            }
//        }
//        showBlink = !showBlink;
//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
//        if (_kbhit()) {
//            int key = _getch();
//            if (key == 224) {
//                key = _getch();
//                if (key == 72) selection = (selection + 4) % 5; // Up
//                if (key == 80) selection = (selection + 1) % 5; // Down
//            }
//            else if (key == 13) { // Enter
//                SetConsoleCursorPosition(h, { 5, (SHORT)(menuStart.Y + 7) });
//                SetConsoleTextAttribute(h, 10);
//                cout << "Game saved in " << saveSlots[selection] << "!" << endl;
//                std::this_thread::sleep_for(std::chrono::seconds(2));
//                return; // Return to Pause Menu after saving
//            }
//            else if (key == 8) { // Backspace
//                return; // Return to Pause Menu
//            }
//        }
//    }
//}

//void Game::pauseScreen() {
//    system("cls");
//
//    // ASCII art
//    const char* asciiArt = R"( 
//   ..................................:--=-::.:...-+*%%#*=-::...................:::.....................
//................................:.----###-..:===*****####%*@+%**-.......:::::::::::.................
//................................:.:-::::::.:===-==#**%*%###*#########*---:::::::::==:...............
//................................:=++++++**+=::::.::::::-:=-=++#*%*%*::::::::::::*#*+-:..............
//.............................:++*+++*++++*+=##::::::::--:--::::---::-::.:::+--*%+:::-:+.............
//.........................=****+++==+=+=+===+==%*:::::::----------=%##*=::::-==---------:............
//....................:+****+**+=+++*+==++=+--=*=#%-::::::---------+##+=+-::-=-----------=:...........
//................-*****##+=+++#*=-==*+=--==*=:=+=#%-::::::---------*%%#*=:::--=--::----===...........
//............+#*#%%#*+*=##*+-=+#+=:--*+-:-+=+-:=*=%#-:::::--=-----===***+-:-=-=--:-::--==+#..........
//.......=*##%%%**+%%#+=-+#*+=:-*+=---=+=-:-++==:=+#%=::::::--------==####::-==+=---=-====+%#.........
//...=+*%%%+#%%%#+-*%#*=--##+==-=*=-=:=*==+-+*++==+*%#-:::::-------===+%##=:-=-=---=*==+**#%%:........
//.:+#%%%%%+%%%%%*=#%%*++-##*++==**+*-+#*+*=+#***=**%%=:::::-===========+====+======++**##*:%+........
//..=%@@%%*%@@@%%#*%%###*+#**##++**##+***##+**#%#+**%@-:--:--===========+===++***+****#*%@+..#-.......
//....-*%%@@%%%%#*%%%###+####%**#*#%#+**#%#+**%%****%@=------====+=+++++=----::=%%@#*++*@+....+.......
//........*%@@@%%%%%%%%+#%%%%#+##%%%+*##%@*#*#%@**+#@@-------=====----------::::-----::::----=-:=.....
//...........-#%@@@@@%*%@@@@%**%@@@%*#%@@%**#%@%#**@@*------==::::::::::::::::--==:::::-==-::::-==....
//..............=##%%%@@@@%%##@@@%%##@@@%%*#@@%%**%@%=----=-::::::::::::::--::=++++=-::===+=-:-==+-...
//.............::::=*#####%%@@@@%%#%@@@%%*#@@%%#*%@@+====+=:::::::::::::::=-::-=++*=-::=+=*=-:-===+...
//............::::::::=*#####%%%%%@@@%%%#%@@%%%*@@@+++++**-------------====-::==+**+-:-=+=#+=:-===#-..
//............-#@@@@@@@@@%#%%%##%%%@%%#%@@%%%##@@%#***###%=#@@@@@@@@@@@@#+=-::=+@#**=--=*%**+--=###:..
//............:#%%%%##%%%#+=+*#**##%%%%%%%%##@@%%#***###%%##@@%%%@%%@%@@#*=-::-#@#***--=%%***--=@#+:..
//............:#%%%%%%%%*##=+++**#***###%%%%%%%#***+----*%%#%%%@@@@@@@%%%+=-::=##****--+#****--***+:..
//............:##%%%%%%##%%++=+%#**%#*####%%#****##*+###%%%@%%####%%%%@@%#=--:=####**-=*%#%%#==*%%%+:.
//............-@@#*#####%%%=-++#%%%%@%***********##########%%*##%%###%##@#+=---#@%#**===*%#**===+#+...
//............:#%%####*#*%@+=+=+%%%@@@@%%%%%%%%%%%%%%@@-..:#%@%%%%%%%%##%#+==+***%@@%**###@@%*##%@:...
//.............-%@@@@@@@%%@%=##*#%@@@%@%@%%%@@%@%@%%@@+....*%%%%%%%%%%%%@%+*+*%%%@%%@*+%#@@%@%*#%#....
//..............-%@@@@@@@@@@@**%@@@@@@@%@@@@@@@@@@@@@+.....=#@@@@@%@@@@%%@%+@%#%@@@##%%%@@@%%%%@%:....
//................*%@@@@@@@@@@@@@@@@@@@@@@@@@@@%##+:........-@@@@@@@@@@@@@@@%%@@@@@@@@@@@@@@@@@@:.....
//...........................::::.............................+%@@@@@%%##%@@@@@@@@@@@@%##*++==:.......
//    )";
//    SetConsoleTextAttribute(h, 14);
//    cout << asciiArt << endl;
//
//    const char* options[] = { "SAVE/LOAD", "SETTINGS", "QUIT" };
//    int selection = 0;
//    bool showBlink = true;
//    COORD menuStart = { 5, 20 };
//
//    while (true) {
//        // Instructions
//        SetConsoleCursorPosition(h, { 5, (SHORT)(menuStart.Y - 2) });
//        SetConsoleTextAttribute(h, 11);
//        cout << "Use ARROW KEYS to move, ENTER to select.            ";
//
//        // Menu display
//        for (int i = 0; i < 3; i++) {
//            SetConsoleCursorPosition(h, { menuStart.X, (SHORT)(menuStart.Y + i) });
//            if (i == selection) {
//                SetConsoleTextAttribute(h, showBlink ? 11 : 15);
//                cout << "> " << options[i] << " <   ";
//            }
//            else {
//                SetConsoleTextAttribute(h, 7);
//                cout << "  " << options[i] << "     ";
//            }
//        }
//
//        showBlink = !showBlink;
//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
//
//        if (_kbhit()) {
//            int key = _getch();
//            if (key == 224) {
//                key = _getch();
//                if (key == 72) selection = (selection + 2) % 3; // Up
//                if (key == 80) selection = (selection + 1) % 3; // Down
//            }
//            else if (key == 13) { // Enter
//                if (selection == 0) saveScreen(); // New 5-slot save/load menu
//                else if (selection == 1) cout << "Settings menu not implemented yet." << endl; // Placeholder for settings
//				else if (selection == 2) return; // Quit Pause Menu
//            }
//        }
//    }
//}

void Game::pauseScreen() {
    cout << "Placeholder until Yu'on is done revamping and integrating his to the system" << endl;
    cout << "Press M to go back to the main menu" << endl;
    cout << "Press P to unpause the game" << endl;
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
    if (repeat) {
        // Stop any existing music if its a repeating ost
        StopMusic("mp3");

        std::wstring command = L"open \"" + filename + L"\" type mpegvideo alias mp3";
        mciSendString(command.c_str(), NULL, 0, NULL);

        // Checking if the audio is playing on repeat
        std::wstring playCommand = L"play mp3 repeat";
        mciSendString(playCommand.c_str(), NULL, 0, NULL);
    }
    else {
        // Do similarly but for sound effects
        StopMusic("sfx");

        std::wstring command = L"open \"" + filename + L"\" type mpegvideo alias sfx";
        mciSendString(command.c_str(), NULL, 0, NULL);

        std::wstring playCommand = L"play sfx";
        mciSendString(playCommand.c_str(), NULL, 0, NULL);
    }
}

void Game::StopMusic(std::string type) {
    if (type == "mp3") {
        mciSendString(L"stop mp3", NULL, 0, NULL);
        mciSendString(L"close mp3", NULL, 0, NULL);
    }
    else {
        mciSendString(L"stop sfx", NULL, 0, NULL);
        mciSendString(L"close sfx", NULL, 0, NULL);
    }
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
