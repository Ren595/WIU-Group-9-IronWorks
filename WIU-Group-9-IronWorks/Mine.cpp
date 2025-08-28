#include "Mine.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "Game.h"


Mine::Mine()
{
    ////  player stuff
    playerlocationx = 0; //// world location
    playerlocationy = 0;
    startcamx = 0; //// FOV
    startcamy = 0;

    ////  machine stuff

    machineplaced = 0;


    for (int m = 0; m < getAllowedMachineCount(); m++) { //// initiating each machine to not spawn
        machineActive[m] = false;
        machinelocationx[m] = 0;
        machinelocationy[m] = 0;
    }

    for (int o = 0; o < 10; o++) {
        oreTimer[o] = 0.0f;
    }
    oreRarity = 0; //// for randomising ore chances

    ////  overall world building
    change = ' ';
    keyPressed = ' ';
    for (int row = 0; row < 100; row++) {
        for (int col = 0; col < 100; col++) {
            world[row][col] = ' ';
        }
    }
    for (int i = 0; i < 200; i++) {
        oreActive[i] = true; ////setting all ores to be true for collision checks
    }

    srand(static_cast<unsigned int>(time(0))); ////randomise ore positions on start
    for (int r = 0; r < 200; r++) {
        orelocationx[r] = rand() % 100;
        orelocationy[r] = rand() % 100;
        orespawnRarity = rand() % 100;
        if (orespawnRarity < 50) {
            world[orelocationy[r]][orelocationx[r]] = 'T';
        }
        if (orespawnRarity >= 50 && oreRarity < 70) {
            world[orelocationy[r]][orelocationx[r]] = 'Z';
        }
        if (orespawnRarity >= 70 && oreRarity < 85) {
            world[orelocationy[r]][orelocationx[r]] = 'I';
        }
        if (orespawnRarity >= 85 && oreRarity < 95) {
            world[orelocationy[r]][orelocationx[r]] = 'C';
        }
        if (orespawnRarity >= 95 && oreRarity < 97) {
            world[orelocationy[r]][orelocationx[r]] = 'Z';
        }
        if (orespawnRarity >= 97 && oreRarity < 99) {
            world[orelocationy[r]][orelocationx[r]] = 'A';
        }
        if (orespawnRarity >= 99 && oreRarity < 101) {
            world[orelocationy[r]][orelocationx[r]] = 'D';
        }

    }

    for (int g = 0; g < 20; g++) { ////vector for FOV
        FOV.push_back({ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' });
    }
}

char Mine::mineInput()
{

    keyPressed = _getch(); ////movement input
    int changeX = 0;
    int changeY = 0;
    int deleteX = 0;
    int deleteY = 0;
    int returnX = 0;
    int returnY = 0;



    switch (keyPressed) {
    case 'w':
    case 'W':
        changeY--;
        break;
    case 's':
    case 'S':
        changeY++;
        break;
    case 'a':
    case 'A':
        changeX--;
        break;
    case 'd':
    case 'D':
        changeX++;
        break;
    case 'e': {
    case 'E':
        //Game::overwriteText(std::to_string(getAllowedMachineCount()), 65, 23, true, 0x0F);
        // Find the first inactive slot for a new machine
        int slot = -1;
        //Game::overwriteText(std::to_string(getAllowedMachineCount()), 65, 20, true, 0x0F);
        int allowedMachines = getAllowedMachineCount() + 100;
        if (machineplaced < allowedMachines) {
            // Find the first inactive slot for a new machine
            int slot = -1;
            for (int i = 0; i < allowedMachines; i++) {
                if (!machineActive[i]) {
                    slot = i;
                    break;
                }
            }
            if (slot != -1) {
                Game::overwriteText("What machine would you like to place down? (Press 1-5)", 50, 0, true, 0x0F);
                Game::overwriteText("Machine lvl 1: ", 50, 1, true, 0x0F); ////Listing down machines available
                Game::overwriteText("Machine lvl 2: ", 50, 2, true, 0x0F);
                Game::overwriteText("Machine lvl 3: ", 50, 3, true, 0x0F);
                Game::overwriteText("Machine lvl 4: ", 50, 4, true, 0x0F);
                Game::overwriteText("Machine lvl 5: ", 50, 5, true, 0x0F);

                Game::overwriteText(std::to_string(Game::returnMachineQuantity(0)), 65, 1, true, 0x0F); ////Listing down machines available in inventory
                Game::overwriteText(std::to_string(Game::returnMachineQuantity(1)), 65, 2, true, 0x0F);
                Game::overwriteText(std::to_string(Game::returnMachineQuantity(2)), 65, 3, true, 0x0F);
                Game::overwriteText(std::to_string(Game::returnMachineQuantity(3)), 65, 4, true, 0x0F);
                Game::overwriteText(std::to_string(Game::returnMachineQuantity(4)), 65, 5, true, 0x0F);

                char machineselect;
                do {
                    machineselect = _getch(); //// getting player to choose machine level to place
                    if (machineselect < '1' || machineselect > '5') {
                        Game::overwriteText("Invalid input! Please choose a valid number (1-5)", 50, 6, true, 0x0F);
                    }
                } while (machineselect < '1' || machineselect > '5');

                int targetX = playerlocationx + 1; ////  Using current player location to place machine
                int targetY = playerlocationy;
                int worldX = startcamx + targetX;
                int worldY = startcamy + targetY;
                for (int f = 0; f < 50; f++) { ////  checks for any machine to the left of player and move to right side of machine
                    if (worldX == machinelocationx[f] && worldY == machinelocationy[f]) {
                        worldX++;
                    }
                }
                for (int f = 0; f < 200; f++) { ////  checks for any ore to the left of player and move to right side of ore
                    if (worldX == orelocationx[f] && worldY == orelocationy[f]) {
                        worldX++;
                    }
                }
                for (int f = 0; f < 50; f++) { ////  double check
                    if (worldX == machinelocationx[f] && worldY == machinelocationy[f]) {
                        worldX++;
                    }
                }
                machinelocationx[slot] = worldX; //// placing machine on world map
                machinelocationy[slot] = worldY;
                world[machinelocationy[slot]][machinelocationx[slot]] = ' ';
                switch (machineselect) {
                case '1':
                    Sleep(20);
                    if (Game::returnMachineQuantity(0) > 0) {
                        world[machinelocationy[slot]][machinelocationx[slot]] = '1';
                        machineActive[slot] = true;
                        Game::updateMachineQuantity(0, Game::returnMachineQuantity(0) - 1);
                        machineplaced++;
                    }
                    break;
                case '2':
                    Sleep(20);
                    if (Game::returnMachineQuantity(1) > 0) {
                        world[machinelocationy[slot]][machinelocationx[slot]] = '2';
                        machineActive[slot] = true;
                        Game::updateMachineQuantity(1, Game::returnMachineQuantity(1) - 1);
                        machineplaced++;
                    }
                    break;
                case '3':
                    Sleep(20);
                    if (Game::returnMachineQuantity(2) > 0) {
                        world[machinelocationy[slot]][machinelocationx[slot]] = '3';
                        machineActive[slot] = true;
                        Game::updateMachineQuantity(2, Game::returnMachineQuantity(2) - 1);
                        machineplaced++;
                    }
                    break;
                case '4':
                    Sleep(20);
                    if (Game::returnMachineQuantity(3) > 0) {
                        world[machinelocationy[slot]][machinelocationx[slot]] = '4';
                        machineActive[slot] = true;
                        Game::updateMachineQuantity(3, Game::returnMachineQuantity(3) - 1);
                        machineplaced++;
                    }
                    break;
                case '5':
                    Sleep(20);
                    if (Game::returnMachineQuantity(4) > 0) {
                        world[machinelocationy[slot]][machinelocationx[slot]] = '5';
                        machineActive[slot] = true;
                        Game::updateMachineQuantity(4, Game::returnMachineQuantity(4) - 1);
                        machineplaced++;
                    }
                    break;
                }

                oreTimer[slot] = 5.0f; //// initiating auto mine feature

                updateMine();
                Sleep(20);
                system("cls");
                drawMine();
            }
        }
        break;
    }
    case 'q':
    case 'Q':
        deleteX = playerlocationx + 1; ////  Using current player location to place machine
        deleteY = playerlocationy;
        returnX = startcamx + deleteX;
        returnY = startcamy + deleteY;
        for (int f = 0; f < 50; f++) {
            if (returnX == machinelocationx[f] && returnY == machinelocationy[f]) {
                char returnmachine = world[machinelocationy[f]][machinelocationx[f]];
                switch (returnmachine) {
                case '1':
                    Game::updateMachineQuantity(0, Game::returnMachineQuantity(0) + 1);
                    machineActive[f] = false;
                    world[machinelocationy[f]][machinelocationx[f]] = ' ';
                    machineplaced--;
                    break;
                case '2':
                    Game::updateMachineQuantity(1, Game::returnMachineQuantity(1) + 1);
                    machineActive[f] = false;
                    world[machinelocationy[f]][machinelocationx[f]] = ' ';
                    machineplaced--;
                    break;
                case '3':
                    Game::updateMachineQuantity(2, Game::returnMachineQuantity(2) + 1);
                    machineActive[f] = false;
                    world[machinelocationy[f]][machinelocationx[f]] = ' ';
                    machineplaced--;
                    break;
                case '4':
                    Game::updateMachineQuantity(3, Game::returnMachineQuantity(3) + 1);
                    machineActive[f] = false;
                    world[machinelocationy[f]][machinelocationx[f]] = ' ';
                    machineplaced--;
                    break;
                case '5':
                    Game::updateMachineQuantity(4, Game::returnMachineQuantity(4) + 1);
                    machineActive[f] = false;
                    world[machinelocationy[f]][machinelocationx[f]] = ' ';
                    machineplaced--;
                    break;
                }


                updateMine();
                Sleep(20);
                system("cls");
                drawMine();
            }

        }
        break;
    case 'R':
    case 'r':
        updateMine(); ////redraw display map
        Sleep(10); // Giving the computer time to synce this information with the other thread
        system("cls");
        drawMine();
        break;
    case 'P':
        return 'P';
    case '2':
        return 'F';
    default:
        break;
    }



    if (changeX != 0 || changeY != 0) {
        int newX = playerlocationx + changeX;
        int newY = playerlocationy + changeY;
        int newWorldX = startcamx + newX;
        int newWorldY = startcamy + newY;
        if (newX < 20 && newX > -1 && newY < 20 && newY > -1 && change == '/'  //// checking for invalid movements
            && world[newWorldY][newWorldX] != '1'
            && world[newWorldY][newWorldX] != '2'
            && world[newWorldY][newWorldX] != '3'
            && world[newWorldY][newWorldX] != '4'
            && world[newWorldY][newWorldX] != '5') {
            change = 'R';
            Sleep(10);
            int newWorldX = startcamx + newX; ////player location set
            int newWorldY = startcamy + newY;
            playerlocationx = newX;
            playerlocationy = newY;
            change = 'A';
        }
        else if (newX >= 20 && startcamx < 79) { //// when moving to area on left
            startcamx++;
            change = 'R';
            for (int r = 0; r < 10; r++) {
                if (newWorldX == machinelocationx[r] && newWorldY == machinelocationy[r]) {
                    playerlocationx--;
                }
            }
            for (int frow = 0; frow < 20; frow++) {
                FOV[frow].erase(FOV[frow].begin() + 0);
                FOV[frow].push_back(world[frow + startcamy][startcamx + 19]);
            }
            updateMine(); ////redraw display map
            Sleep(10); // Giving the computer time to synce this information with the other thread

            change = 'A';
        }
        else if (newY >= 20 && startcamy < 79) { //// when moving to area below
            startcamy++;
            change = 'R';
            for (int r = 0; r < 10; r++) {
                if (newWorldX == machinelocationx[r] && newWorldY == machinelocationy[r]) {
                    playerlocationy--;
                }
            }
            FOV.erase(FOV.begin() + 0);
            FOV.push_back({ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' });
            updateMine(); ////redraw display map
            Sleep(10); // Giving the computer time to synce this information with the other thread

            change = 'A';
        }
        else if (newX < 0 && startcamx > 0) { //// when moving to area on left
            startcamx--;
            change = 'R';
            for (int r = 0; r < 10; r++) {
                if (newWorldX == machinelocationx[r] && newWorldY == machinelocationy[r]) {
                    playerlocationx++;
                }
            }
            for (int frow = 0; frow < 20; frow++) {
                FOV[frow].pop_back();
                FOV[frow].insert(FOV[frow].begin() + 0, world[frow + startcamy][startcamx]);
            }
            updateMine(); ////redraw display map
            Sleep(10); // Giving the computer time to synce this information with the other thread

            change = 'A';
        }
        else if (newY < 0 && startcamy > 0) { //// when moving to are on top
            startcamy--;
            change = 'R';
            for (int r = 0; r < 10; r++) {
                if (newWorldX == machinelocationx[r] && newWorldY == machinelocationy[r]) {
                    playerlocationy++;
                }
            }
            FOV.pop_back();
            FOV.insert(FOV.begin(), { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' });
            updateMine();
            Sleep(10); // Giving the computer time to synce this information with the other thread
            change = 'A';
        }
    }

    int playerWorldX = startcamx + playerlocationx;
    int playerWorldY = startcamy + playerlocationy;
    for (int d = 0; d < 200;d++) {
        ////checking if player has collided with an ore based on location
        if (playerWorldY == orelocationy[d] && playerWorldX == orelocationx[d] && oreActive[d]) {
            //std::cout << "obtained" << std::endl;
            //Sleep(2000);

            ////symbol on board displayed is used to compare to add to inventory
            char symbol = world[orelocationy[d]][orelocationx[d]];
            switch (symbol) {
            case 'T':
                if (Game::returnItemQuantity(0) < 128) {
                    Game::updateItemQuantity(0, Game::returnItemQuantity(0) + 1);
                }
                break;
            case 'S':
                if (Game::returnItemQuantity(1) < 128) {
                    Game::updateItemQuantity(1, Game::returnItemQuantity(1) + 1);
                }
                break;
            case 'I':
                if (Game::returnItemQuantity(2) < 128) {
                    Game::updateItemQuantity(2, Game::returnItemQuantity(2) + 1);
                }
                break;
            case 'C':
                if (Game::returnItemQuantity(3) < 128) {
                    Game::updateItemQuantity(3, Game::returnItemQuantity(3) + 1);
                }
                break;
            case 'Z':
                if (Game::returnItemQuantity(4) < 128) {
                    Game::updateItemQuantity(4, Game::returnItemQuantity(4) + 1);
                }
                break;
            case 'A':
                if (Game::returnItemQuantity(5) < 128) {
                    Game::updateItemQuantity(5, Game::returnItemQuantity(5) + 1);
                }
                break;
            case 'D':
                if (Game::returnItemQuantity(6) < 128) {
                    Game::updateItemQuantity(6, Game::returnItemQuantity(6) + 1);
                }
                break;
            }
            oreActive[d] = false;
            system("cls");
            drawMine();
            world[orelocationy[d]][orelocationx[d]] = ' '; //// empty ore collected area
        }

    }
    return '/';
}

void Mine::updateMine()
{
    Sleep(10);
    updateFOV();
    for (int frow = 0; frow < 20; frow++) {
        for (int fcol = 0; fcol < 20; fcol++) {
            Game::overwriteText(std::string(1, FOV[frow][fcol]), fcol * 2 + 1, frow + 1, true, 0x0F);
        }
    }
}

void Mine::drawMine() ////Show physical map
{
    updateFOV();
    FOV[playerlocationy][playerlocationx] = '+';
    // Only draw machine if within FOV bounds (by AI)
    for (int r = 0; r < 10; r++) {
        int machineFOVx = machinelocationx[r] - startcamx;
        int machineFOVy = machinelocationy[r] - startcamy;
        if (machineActive[r] &&
            machineFOVx >= 0 && machineFOVx < 20 &&
            machineFOVy >= 0 && machineFOVy < 20) {
            FOV[machineFOVy][machineFOVx] = 'M';
        }
    }
    std::cout << "+----------------------------------------+" << std::endl; ////  printing out FOV
    for (int frow = 0; frow < 20; frow++) {
        std::cout << "|";
        for (int fcol = 0; fcol < 20; fcol++) {
            std::cout << FOV[frow][fcol] << ' ';
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+----------------------------------------+" << std::endl;

    Game::overwriteText(orelist[0], 3, 22, true, 0x0F); //// Printing out inventory
    Game::overwriteText(orelist[1], 3, 23, true, 0x0F);
    Game::overwriteText(orelist[2], 3, 24, true, 0x0F);
    Game::overwriteText(orelist[3], 3, 25, true, 0x0F);
    Game::overwriteText(orelist[4], 3, 26, true, 0x0F);
    Game::overwriteText(orelist[5], 3, 27, true, 0x0F);
    Game::overwriteText(orelist[6], 3, 28, true, 0x0F);

    Game::overwriteText(std::to_string(Game::returnItemQuantity(0)), 0, 22, true, 0x0F);
    Game::overwriteText(std::to_string(Game::returnItemQuantity(1)), 0, 23, true, 0x0F);
    Game::overwriteText(std::to_string(Game::returnItemQuantity(2)), 0, 24, true, 0x0F);
    Game::overwriteText(std::to_string(Game::returnItemQuantity(3)), 0, 25, true, 0x0F);
    Game::overwriteText(std::to_string(Game::returnItemQuantity(4)), 0, 26, true, 0x0F);
    Game::overwriteText(std::to_string(Game::returnItemQuantity(5)), 0, 27, true, 0x0F);
    Game::overwriteText(std::to_string(Game::returnItemQuantity(6)), 0, 28, true, 0x0F);

    Game::overwriteText("Controls", 50, 8, true, 0x0F); ////Listing down controls
    Game::overwriteText("Movement: wasd", 50, 9, true, 0x0F);
    Game::overwriteText("Placing machine: e", 50, 10, true, 0x0F);
    Game::overwriteText("Removing machine: q", 50, 11, true, 0x0F);

    Game::overwriteText("Bugs will appear, they include: ", 50, 13, true, 0x0F); ////Listing down bugs
    Game::overwriteText("-- Random numbers popping up on FOV or inventory UI", 50, 14, true, 0x0F);
    Game::overwriteText("-- and map flipping", 50, 15, true, 0x0F);
    Game::overwriteText("How to fix when bug appears: ", 50, 17, true, 0x0F);
    Game::overwriteText("-- Collect ore", 50, 18, true, 0x0F);
    Game::overwriteText("-- Place machine (even if inventory is empty)", 50, 19, true, 0x0F);
    Game::overwriteText("-- Or press r to reset the whole screen", 50, 20, true, 0x0F);

    Game::overwriteText("Press 2 while not in machine mode to go back to factory", 50, 22, true, 0x0F);
    std::cout << std::endl;
}

void Mine::update(float dt)
{


    for (int f = 0; f < 50; f++) {
        oreTimer[f] -= dt;
    }
    if (change != '/') {
        if (change == 'R') {

            Game::overwriteText(std::string(1, '+'), playerlocationx * 2 + 1, playerlocationy + 1, false, 0x0F);

        }
        else if (change == 'A') {
            std::string temp(1, '+');
            Game::overwriteText(temp, playerlocationx * 2 + 1, playerlocationy + 1, true, 0x0F);
        }
        if (change == 'S') {
            for (int w = 0; w < 5; w++) {
                Game::overwriteText(std::string(1, ores[rand() % 7]), orelocationx[w] * 2 + 1, orelocationy[w] + 1, true, 0x0F);
            }
        }

        change = '/';
    }


    for (int f = 0; f < 50; f++) {
        if (machineActive[f]) {
            if (world[machinelocationy[f]][machinelocationx[f]] == '1') { //// machine level 1 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 7.5f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 40) {
                        if (Game::returnItemQuantity(0) < 128) {
                            Game::updateItemQuantity(0, Game::returnItemQuantity(0) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(0)), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 40 && oreRarity < 55) {
                        if (Game::returnItemQuantity(1) < 128) {
                            Game::updateItemQuantity(1, Game::returnItemQuantity(1) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(1)), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 55 && oreRarity < 75) {
                        if (Game::returnItemQuantity(2) < 128) {
                            Game::updateItemQuantity(2, Game::returnItemQuantity(2) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(2)), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 75 && oreRarity < 90) {
                        if (Game::returnItemQuantity(3) < 128) {
                            Game::updateItemQuantity(3, Game::returnItemQuantity(3) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(3)), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 90 && oreRarity < 95) {
                        if (Game::returnItemQuantity(4) < 128) {
                            Game::updateItemQuantity(4, Game::returnItemQuantity(4) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(4)), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 95 && oreRarity < 98) {
                        if (Game::returnItemQuantity(5) < 128) {
                            Game::updateItemQuantity(5, Game::returnItemQuantity(5) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(5)), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 98 && oreRarity < 101) {
                        if (Game::returnItemQuantity(6) < 128) {
                            Game::updateItemQuantity(6, Game::returnItemQuantity(6) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(6)), 0, 28, true, 0x0F);
                    }
                }
            }
            if (world[machinelocationy[f]][machinelocationx[f]] == '2') { //// machine level 2 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 7.5f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 25) {
                        if (Game::returnItemQuantity(0) < 128) {
                            Game::updateItemQuantity(0, Game::returnItemQuantity(0) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(0)), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 25 && oreRarity < 55) {
                        if (Game::returnItemQuantity(1) < 128) {
                            Game::updateItemQuantity(1, Game::returnItemQuantity(1) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(1)), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 55 && oreRarity < 75) {
                        if (Game::returnItemQuantity(2) < 128) {
                            Game::updateItemQuantity(2, Game::returnItemQuantity(2) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(2)), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 75 && oreRarity < 90) {
                        if (Game::returnItemQuantity(3) < 128) {
                            Game::updateItemQuantity(3, Game::returnItemQuantity(3) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(3)), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 90 && oreRarity < 95) {
                        if (Game::returnItemQuantity(4) < 128) {
                            Game::updateItemQuantity(4, Game::returnItemQuantity(4) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(4)), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 95 && oreRarity < 98) {
                        if (Game::returnItemQuantity(5) < 128) {
                            Game::updateItemQuantity(5, Game::returnItemQuantity(5) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(5)), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 98 && oreRarity < 101) {
                        if (Game::returnItemQuantity(6) < 128) {
                            Game::updateItemQuantity(6, Game::returnItemQuantity(6) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(6)), 0, 28, true, 0x0F);
                    }
                }
            }
            if (world[machinelocationy[f]][machinelocationx[f]] == '3') { //// machine level 3 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 7.5f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 20) {
                        if (Game::returnItemQuantity(0) < 128) {
                            Game::updateItemQuantity(0, Game::returnItemQuantity(0) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(0)), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 20 && oreRarity < 45) {
                        if (Game::returnItemQuantity(1) < 128) {
                            Game::updateItemQuantity(1, Game::returnItemQuantity(0) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(0)), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 45 && oreRarity < 75) {
                        if (Game::returnItemQuantity(2) < 128) {
                            Game::updateItemQuantity(2, Game::returnItemQuantity(2) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(6)), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 75 && oreRarity < 90) {
                        if (Game::returnItemQuantity(3) < 128) {
                            Game::updateItemQuantity(3, Game::returnItemQuantity(3) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(3)), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 90 && oreRarity < 95) {
                        if (Game::returnItemQuantity(4) < 128) {
                            Game::updateItemQuantity(4, Game::returnItemQuantity(4) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(4)), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 95 && oreRarity < 98) {
                        if (Game::returnItemQuantity(5) < 128) {
                            Game::updateItemQuantity(5, Game::returnItemQuantity(5) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(5)), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 98 && oreRarity < 101) {
                        if (Game::returnItemQuantity(6) < 128) {
                            Game::updateItemQuantity(6, Game::returnItemQuantity(6) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(6)), 0, 28, true, 0x0F);
                    }
                }
            }
            if (world[machinelocationy[f]][machinelocationx[f]] == '4') { //// machine level 4 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 7.5f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 15) {
                        if (Game::returnItemQuantity(0) < 128) {
                            Game::updateItemQuantity(0, Game::returnItemQuantity(0) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(0)), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 15 && oreRarity < 30) {
                        if (Game::returnItemQuantity(1) < 128) {
                            Game::updateItemQuantity(1, Game::returnItemQuantity(1) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(1)), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 30 && oreRarity < 50) {
                        if (Game::returnItemQuantity(2) < 128) {
                            Game::updateItemQuantity(2, Game::returnItemQuantity(2) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(2)), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 50 && oreRarity < 80) {
                        if (Game::returnItemQuantity(3) < 128) {
                            Game::updateItemQuantity(3, Game::returnItemQuantity(3) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(3)), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 80 && oreRarity < 95) {
                        if (Game::returnItemQuantity(4) < 128) {
                            Game::updateItemQuantity(4, Game::returnItemQuantity(4) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(4)), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 95 && oreRarity < 98) {
                        if (Game::returnItemQuantity(5) < 128) {
                            Game::updateItemQuantity(5, Game::returnItemQuantity(5) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(5)), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 98 && oreRarity < 101) {
                        if (Game::returnItemQuantity(6) < 128) {
                            Game::updateItemQuantity(6, Game::returnItemQuantity(6) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(6)), 0, 28, true, 0x0F);
                    }
                }
            }
            if (world[machinelocationy[f]][machinelocationx[f]] == '5') { //// machine level 5 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 7.5f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 10) {
                        if (Game::returnItemQuantity(0) < 128) {
                            Game::updateItemQuantity(0, Game::returnItemQuantity(0) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(0)), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 10 && oreRarity < 25) {
                        if (Game::returnItemQuantity(1) < 128) {
                            Game::updateItemQuantity(1, Game::returnItemQuantity(1) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(1)), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 25 && oreRarity < 35) {
                        if (Game::returnItemQuantity(2) < 128) {
                            Game::updateItemQuantity(2, Game::returnItemQuantity(2) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(2)), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 35 && oreRarity < 50) {
                        if (Game::returnItemQuantity(3) < 128) {
                            Game::updateItemQuantity(3, Game::returnItemQuantity(3) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(3)), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 50 && oreRarity < 75) {
                        if (Game::returnItemQuantity(4) < 128) {
                            Game::updateItemQuantity(4, Game::returnItemQuantity(4) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(4)), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 75 && oreRarity < 90) {
                        if (Game::returnItemQuantity(5) < 128) {
                            Game::updateItemQuantity(5, Game::returnItemQuantity(5) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(5)), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 90 && oreRarity < 101) {
                        if (Game::returnItemQuantity(6) < 128) {
                            Game::updateItemQuantity(6, Game::returnItemQuantity(6) + 1);
                        }
                        Game::overwriteText(std::to_string(Game::returnItemQuantity(6)), 0, 28, true, 0x0F);
                    }
                }
            }
        }
    }


}

void Mine::updateFOV()
{
    Sleep(5);
    for (int frow = 0; frow < 20; frow++) {
        for (int fcol = 0; fcol < 20; fcol++) {
            FOV[frow][fcol] = world[startcamy + frow][startcamx + fcol];
            if (world[startcamy + frow][startcamx + fcol] == '1' ||
                world[startcamy + frow][startcamx + fcol] == '2' ||
                world[startcamy + frow][startcamx + fcol] == '3' ||
                world[startcamy + frow][startcamx + fcol] == '4' ||
                world[startcamy + frow][startcamx + fcol] == '5') {

                FOV[frow][fcol] = 'M';
            }
        }
    }
}

int Mine::getAllowedMachineCount() const {
    return Game::returnMachineQuantity(0) +
        Game::returnMachineQuantity(1) +
        Game::returnMachineQuantity(2) +
        Game::returnMachineQuantity(3) +
        Game::returnMachineQuantity(4);
}