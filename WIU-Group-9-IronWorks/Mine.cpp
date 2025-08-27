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
    playerlocationx = 0;
    playerlocationy = 0;
    for (int m = 0; m < 10; m++) {
        machineActive[m] = false;
        machinelocationx[m] = 0;
        machinelocationy[m] = 0;
    }
    machinecount = 0;
    startcamx = 0;
    startcamy = 0;

    oreTimer = 0.0f;
    oreRarity = 0;

    change = ' ';
    keyPressed = ' ';
    for (int row = 0; row < 100; row++) {
        for (int col = 0; col < 100; col++) {
            world[row][col] = ' ';
        }
    }
    for (int y = 0; y < 7; y++) {
        inventory[y] = 0; ////initialising all values in inventory to be 0 on start
    }
    for (int i = 0; i < 100; i++) {
        oreActive[i] = true; ////setting all ores to be true for collision checks
    }

    srand(static_cast<unsigned int>(time(0))); ////randomise ore positions on start
    for (int r = 0; r < 100; r++) {
        orelocationx[r] = rand() % 100;
        orelocationy[r] = rand() % 100;
        world[orelocationy[r]][orelocationx[r]] = ores[rand() % 7];
    }

    for (int g = 0; g < 20; g++) {
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
            int targetX = playerlocationx + 1;
            int targetY = playerlocationy;
            int worldX = startcamx + targetX;
            int worldY = startcamy + targetY;
            for (int f = 0; f < 10; f++) {
                if (worldX == machinelocationx[f] && worldY == machinelocationy[f]) {
                    worldX++;
                }
            }
            for (int f = 0; f < 100; f++) {
                if (worldX == orelocationx[f] && worldY == orelocationy[f]) {
                    worldX++;
                }
            }
            for (int f = 0; f < 10; f++) {
                if (worldX == machinelocationx[f] && worldY == machinelocationy[f]) {
                    worldX++;
                }
            }
            world[machinelocationy[machinecount]][machinelocationx[machinecount]] = ' ';
            machinelocationx[machinecount] = worldX;
            machinelocationy[machinecount] = worldY;
            machineActive[machinecount] = true;
            world[machinelocationy[machinecount]][machinelocationx[machinecount]] = 'M';

            oreTimer = 2.0f;

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
        if (newX < 20 && newX > -1 && newY < 20 && newY > -1 && change == '/' && world[newWorldY][newWorldX] != 'M') {
            change = 'R';
            Sleep(10);
            int newWorldX = startcamx + newX;
            int newWorldY = startcamy + newY;
            playerlocationx = newX;
            playerlocationy = newY;
            change = 'A';
        }
        else if (newX >= 20 && startcamx < 79) { //// when moving to area on left
            startcamx++;
            //system("cls");                       //// reloads display and place ores
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
            //system("cls");                       //// reloads display and place ores
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
            //system("cls");                       //// reloads display and place ores
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
            /*std::cout << "Something";*/
            startcamy--;
            //system("cls");                       //// reloads display and place ores
            change = 'R';
            for (int r = 0; r < 10; r++) {
                if (newWorldX == machinelocationx[r] && newWorldY == machinelocationy[r]) {
                    playerlocationy++;
                }
            }
            FOV.pop_back();
            FOV.insert(FOV.begin(), { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' });
            //Game::OverwriteText(std::string(1, newTopRow[0]), 50, 0, true, 0x4F);
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
                if (inventory[0] < 64) {
                    inventory[0]++;
                }
                break;
            case 'S':
                if (inventory[1] < 64) {
                    inventory[1]++;
                }
                break;
            case 'I':
                if (inventory[2] < 64) {
                    inventory[2]++;
                }
                break;
            case 'C':
                if (inventory[3] < 64) {
                    inventory[3]++;
                }
                break;
            case 'Z':
                if (inventory[4] < 64) {
                    inventory[4]++;
                }
                break;
            case 'A':
                if (inventory[5] < 64) {
                    inventory[5]++;
                }
                break;
            case 'D':
                if (inventory[6] < 64) {
                    inventory[6]++;
                }
                break;
            }

            //std::cout << "Ore collected is: " << orelist[d] << std::endl;
            oreActive[d] = false;
            system("cls");
            drawMine();
            /*Game::OverwriteText("Ore collected", 50, 0, true, 0x0F);*/
            world[orelocationy[d]][orelocationx[d]] = ' ';
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
    //for (int c = 0; c < 10; c++) {
    //    if (machineActive[c] == true) {
    //        FOV[machinelocationy[c]][machinelocationx[c]] = 'M';
    //        //Game::OverwriteText("e", 50, 0, true, 0x0F);
    //    }
    //}
    // Only draw machine if within FOV bounds
    for (int r = 0; r < 10; r++) {
        int machineFOVx = machinelocationx[r] - startcamx;
        int machineFOVy = machinelocationy[r] - startcamy;
        if (machineActive &&
            machineFOVx >= 0 && machineFOVx < 20 &&
            machineFOVy >= 0 && machineFOVy < 20) {
            FOV[machineFOVy][machineFOVx] = 'M';
        }
    }
    std::cout << "+----------------------------------------+" << std::endl;
    for (int frow = 0; frow < 20; frow++) {
        std::cout << "|";
        for (int fcol = 0; fcol < 20; fcol++) {
            std::cout << FOV[frow][fcol] << ' ';
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+----------------------------------------+" << std::endl;
    //for (int v = 0; v < 7; v++) {
    //    std::cout  << ' ' << orelist[v] << std::endl; ////print out inventory info
    //}
    Game::overwriteText(orelist[0], 2, 22, true, 0x0F);
    Game::overwriteText(orelist[1], 2, 23, true, 0x0F);
    Game::overwriteText(orelist[2], 2, 24, true, 0x0F);
    Game::overwriteText(orelist[3], 2, 25, true, 0x0F);
    Game::overwriteText(orelist[4], 2, 26, true, 0x0F);
    Game::overwriteText(orelist[5], 2, 27, true, 0x0F);
    Game::overwriteText(orelist[6], 2, 28, true, 0x0F);

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

    oreTimer -= dt;

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
    if (machineActive[0]) {
        if (oreTimer < 0.0f) {
            oreTimer = 2.0f;
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

}

void Mine::updateFOV() //// Make the map become a blank state
{
    for (int frow = 0; frow < 20; frow++) {
        for (int fcol = 0; fcol < 20; fcol++) {
            FOV[frow][fcol] = world[startcamy + frow][startcamx + fcol];
        }
    }
}