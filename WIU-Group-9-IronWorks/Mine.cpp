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
    for (int m = 0; m < 10; m++) { //// initiating each machine to not spawn
        machineActive[m] = false;
        machinelocationx[m] = 0;
        machinelocationy[m] = 0;
    }
    machinecount = 0;

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
    for (int y = 0; y < 7; y++) {
        inventory[y] = 0; ////initialising all values in inventory to be 0 on start unless linked to main inventory by Justin
    }

    for (int y = 0; y < 5; y++) {
        machineinventory[y] = 2; ////initialising all values in machine inventory to be 2 for testing on start 
    }                            ////unless linked to main inventory by Justin

    for (int i = 0; i < 100; i++) {
        oreActive[i] = true; ////setting all ores to be true for collision checks
    }

    srand(static_cast<unsigned int>(time(0))); ////randomise ore positions on start
    for (int r = 0; r < 100; r++) {
        orelocationx[r] = rand() % 100;
        orelocationy[r] = rand() % 100;
        world[orelocationy[r]][orelocationx[r]] = ores[rand() % 7];
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

    switch (keyPressed) {
    case 'w':
        changeY--;
        break;
    case 's':
        changeY++;
        break;
    case 'a':
        changeX--;
        break;
    case 'd':
        changeX++;
        break;
    case 'e': {
        if (machinecount < 10) {
            Game::overwriteText("What machine would you like to place down? (Press 1-5)", 50, 0, true, 0x0F);
            Game::overwriteText("Machine lvl 1: ", 50, 1, true, 0x0F); ////Listing down machines available
            Game::overwriteText("Machine lvl 2: ", 50, 2, true, 0x0F);
            Game::overwriteText("Machine lvl 3: ", 50, 3, true, 0x0F);
            Game::overwriteText("Machine lvl 4: ", 50, 4, true, 0x0F);
            Game::overwriteText("Machine lvl 5: ", 50, 5, true, 0x0F);

            Game::overwriteText(std::to_string(machineinventory[0]), 65, 1, true, 0x0F); ////Listing down machines available in inventory
            Game::overwriteText(std::to_string(machineinventory[1]), 65, 2, true, 0x0F);
            Game::overwriteText(std::to_string(machineinventory[2]), 65, 3, true, 0x0F);
            Game::overwriteText(std::to_string(machineinventory[3]), 65, 4, true, 0x0F);
            Game::overwriteText(std::to_string(machineinventory[4]), 65, 5, true, 0x0F);

            char machineselect = _getch(); //// getting player to choose machine level to place

            //// DO NOT INTEGRATE YET, CONDITION CHECK NOT FINSIHED
            if (machineselect != '1' && machineselect != '2' && machineselect != '3' && machineselect != '4' && machineselect != '5') {
                Game::overwriteText("Please choose a valid number (1-5)", 50, 6, true, 0x0F);
                char machineselect = _getch();
            }

            int targetX = playerlocationx + 1; ////  Using current player location to place machine
            int targetY = playerlocationy;
            int worldX = startcamx + targetX;
            int worldY = startcamy + targetY;
            for (int f = 0; f < 10; f++) { ////  checks for any machine to the left of player and move to right side of machine
                if (worldX == machinelocationx[f] && worldY == machinelocationy[f]) {
                    worldX++;
                }
            }
            for (int f = 0; f < 100; f++) { ////  checks for any ore to the left of player and move to right side of ore
                if (worldX == orelocationx[f] && worldY == orelocationy[f]) {
                    worldX++;
                }
            }
            for (int f = 0; f < 10; f++) { ////  double check
                if (worldX == machinelocationx[f] && worldY == machinelocationy[f]) {
                    worldX++;
                }
            }
            machinelocationx[machinecount] = worldX; //// placing machine on world map
            machinelocationy[machinecount] = worldY;
            switch (machineselect) {
            case '1':
                if (machineinventory[0] > 0) {
                    world[machinelocationy[machinecount]][machinelocationx[machinecount]] = '1';
                    machineActive[machinecount] = true;
                    machineinventory[0]--;
                }
                break;
            case '2':
                if (machineinventory[1] > 0) {
                    world[machinelocationy[machinecount]][machinelocationx[machinecount]] = '2';
                    machineActive[machinecount] = true;
                    machineinventory[1]--;
                }
                break;
            case '3':
                if (machineinventory[2] > 0) {
                    world[machinelocationy[machinecount]][machinelocationx[machinecount]] = '3';
                    machineActive[machinecount] = true;
                    machineinventory[2]--;
                }
                break;
            case '4':
                if (machineinventory[3] > 0) {
                    world[machinelocationy[machinecount]][machinelocationx[machinecount]] = '4';
                    machineActive[machinecount] = true;
                    machineinventory[3]--;
                }
                break;
            case '5':
                if (machineinventory[4] > 0) {
                    world[machinelocationy[machinecount]][machinelocationx[machinecount]] = '5';
                    machineActive[machinecount] = true;
                    machineinventory[4]--;
                }
                break;
            }

            oreTimer[machinecount] = 2.0f; //// initiating auto mine feature

            updateMine();
            change = 'M';
            system("cls");
            drawMine();
        }
        break;
    }
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
    for (int d = 0; d < 100;d++) {
        ////checking if player has collided with an ore based on location
        if (playerWorldY == orelocationy[d] && playerWorldX == orelocationx[d] && oreActive[d]) {
            //std::cout << "obtained" << std::endl;
            //Sleep(2000);

            ////symbol on board displayed is used to compare to add to inventory
            char symbol = world[orelocationy[d]][orelocationx[d]];
            switch (symbol) {
            case 'T':
                if (inventory[0] < 128) {
                    inventory[0]++;
                }
                break;
            case 'S':
                if (inventory[1] < 128) {
                    inventory[1]++;
                }
                break;
            case 'I':
                if (inventory[2] < 128) {
                    inventory[2]++;
                }
                break;
            case 'C':
                if (inventory[3] < 128) {
                    inventory[3]++;
                }
                break;
            case 'Z':
                if (inventory[4] < 128) {
                    inventory[4]++;
                }
                break;
            case 'A':
                if (inventory[5] < 128) {
                    inventory[5]++;
                }
                break;
            case 'D':
                if (inventory[6] < 128) {
                    inventory[6]++;
                }
                break;
            }
            oreActive[d] = false;
            system("cls");
            drawMine();
            world[orelocationy[d]][orelocationx[d]] = ' '; //// empty core collected area
        }

    }
    return '/';
}

void Mine::updateMine()
{
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

    Game::overwriteText(std::to_string(inventory[0]), 0, 22, true, 0x0F);
    Game::overwriteText(std::to_string(inventory[1]), 0, 23, true, 0x0F);
    Game::overwriteText(std::to_string(inventory[2]), 0, 24, true, 0x0F);
    Game::overwriteText(std::to_string(inventory[3]), 0, 25, true, 0x0F);
    Game::overwriteText(std::to_string(inventory[4]), 0, 26, true, 0x0F);
    Game::overwriteText(std::to_string(inventory[5]), 0, 27, true, 0x0F);
    Game::overwriteText(std::to_string(inventory[6]), 0, 28, true, 0x0F);
    std::cout << std::endl;
}

void Mine::update(float dt)
{
    for (int f = 0; f < 10; f++) {
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
        if (change == 'M') {
            Game::overwriteText(std::string(1, 'M'), machinelocationx[machinecount] * 2 + 1, machinelocationy[machinecount] + 1, true, 0x0F);

            machinecount++;
            if (machinecount == 10) {
                machinecount = 0;
            }
        }

        change = '/';
    }
    for (int f = 0; f < 10; f++) {   //// THIS CODE DOES NOT INCLUDE INVENTORY LIMITS, WILL ADD TMR
        if (machineActive[f]) {
            if (world[machinelocationy[f]][machinelocationx[f]] = '1') { //// machine level 1 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 2.0f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 30) {
                        inventory[0]++;
                        Game::overwriteText(std::to_string(inventory[0]), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 30 && oreRarity < 55) {
                        inventory[1]++;
                        Game::overwriteText(std::to_string(inventory[1]), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 55 && oreRarity < 75) {
                        inventory[2]++;
                        Game::overwriteText(std::to_string(inventory[2]), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 75 && oreRarity < 90) {
                        inventory[3]++;
                        Game::overwriteText(std::to_string(inventory[3]), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 90 && oreRarity < 95) {
                        inventory[4]++;
                        Game::overwriteText(std::to_string(inventory[4]), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 95 && oreRarity < 98) {
                        inventory[5]++;
                        Game::overwriteText(std::to_string(inventory[5]), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 98 && oreRarity < 101) {
                        inventory[6]++;
                        Game::overwriteText(std::to_string(inventory[6]), 0, 28, true, 0x0F);
                    }
                }
            }
            if (world[machinelocationy[f]][machinelocationx[f]] = '2') { //// machine level 2 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 2.0f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 25) {
                        inventory[0]++;
                        Game::overwriteText(std::to_string(inventory[0]), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 25 && oreRarity < 55) {
                        inventory[1]++;
                        Game::overwriteText(std::to_string(inventory[1]), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 55 && oreRarity < 75) {
                        inventory[2]++;
                        Game::overwriteText(std::to_string(inventory[2]), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 75 && oreRarity < 90) {
                        inventory[3]++;
                        Game::overwriteText(std::to_string(inventory[3]), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 90 && oreRarity < 95) {
                        inventory[4]++;
                        Game::overwriteText(std::to_string(inventory[4]), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 95 && oreRarity < 98) {
                        inventory[5]++;
                        Game::overwriteText(std::to_string(inventory[5]), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 98 && oreRarity < 101) {
                        inventory[6]++;
                        Game::overwriteText(std::to_string(inventory[6]), 0, 28, true, 0x0F);
                    }
                }
            }
            if (world[machinelocationy[f]][machinelocationx[f]] = '3') { //// machine level 3 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 2.0f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 20) {
                        inventory[0]++;
                        Game::overwriteText(std::to_string(inventory[0]), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 20 && oreRarity < 45) {
                        inventory[1]++;
                        Game::overwriteText(std::to_string(inventory[1]), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 45 && oreRarity < 75) {
                        inventory[2]++;
                        Game::overwriteText(std::to_string(inventory[2]), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 75 && oreRarity < 90) {
                        inventory[3]++;
                        Game::overwriteText(std::to_string(inventory[3]), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 90 && oreRarity < 95) {
                        inventory[4]++;
                        Game::overwriteText(std::to_string(inventory[4]), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 95 && oreRarity < 98) {
                        inventory[5]++;
                        Game::overwriteText(std::to_string(inventory[5]), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 98 && oreRarity < 101) {
                        inventory[6]++;
                        Game::overwriteText(std::to_string(inventory[6]), 0, 28, true, 0x0F);
                    }
                }
            }
            if (world[machinelocationy[f]][machinelocationx[f]] = '4') { //// machine level 4 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 2.0f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 15) {
                        inventory[0]++;
                        Game::overwriteText(std::to_string(inventory[0]), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 15 && oreRarity < 30) {
                        inventory[1]++;
                        Game::overwriteText(std::to_string(inventory[1]), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 30 && oreRarity < 50) {
                        inventory[2]++;
                        Game::overwriteText(std::to_string(inventory[2]), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 50 && oreRarity < 80) {
                        inventory[3]++;
                        Game::overwriteText(std::to_string(inventory[3]), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 80 && oreRarity < 95) {
                        inventory[4]++;
                        Game::overwriteText(std::to_string(inventory[4]), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 95 && oreRarity < 98) {
                        inventory[5]++;
                        Game::overwriteText(std::to_string(inventory[5]), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 98 && oreRarity < 101) {
                        inventory[6]++;
                        Game::overwriteText(std::to_string(inventory[6]), 0, 28, true, 0x0F);
                    }
                }
            }
            if (world[machinelocationy[f]][machinelocationx[f]] = '5') { //// machine level 5 chances
                if (oreTimer[f] < 0.0f) {
                    oreTimer[f] = 2.0f;
                    oreRarity = rand() % 100;
                    if (oreRarity < 10) {
                        inventory[0]++;
                        Game::overwriteText(std::to_string(inventory[0]), 0, 22, true, 0x0F);
                    }
                    if (oreRarity >= 10 && oreRarity < 25) {
                        inventory[1]++;
                        Game::overwriteText(std::to_string(inventory[1]), 0, 23, true, 0x0F);
                    }
                    if (oreRarity >= 25 && oreRarity < 35) {
                        inventory[2]++;
                        Game::overwriteText(std::to_string(inventory[2]), 0, 24, true, 0x0F);
                    }
                    if (oreRarity >= 35 && oreRarity < 50) {
                        inventory[3]++;
                        Game::overwriteText(std::to_string(inventory[3]), 0, 25, true, 0x0F);
                    }
                    if (oreRarity >= 50 && oreRarity < 75) {
                        inventory[4]++;
                        Game::overwriteText(std::to_string(inventory[4]), 0, 26, true, 0x0F);
                    }
                    if (oreRarity >= 75 && oreRarity < 90) {
                        inventory[5]++;
                        Game::overwriteText(std::to_string(inventory[5]), 0, 27, true, 0x0F);
                    }
                    if (oreRarity >= 90 && oreRarity < 101) {
                        inventory[6]++;
                        Game::overwriteText(std::to_string(inventory[6]), 0, 28, true, 0x0F);
                    }
                }
            }
        }
    }


}

void Mine::updateFOV() //// Make the map become a blank state
{
    for (int frow = 0; frow < 20; frow++) {
        for (int fcol = 0; fcol < 20; fcol++) {
            FOV[frow][fcol] = world[startcamy + frow][startcamx + fcol];
        }
    }
}