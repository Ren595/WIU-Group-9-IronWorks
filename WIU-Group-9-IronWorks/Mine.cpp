#include "Mine.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include "Game.h"


Mine::Mine()
{
    playerlocationx = 19;
    playerlocationy = 3;
    Dminefloor = 1;
    Lminefloor = 1;
    change = ' ';
    keyPressed = ' ';
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 20; col++) {
            world[row][col] = ' ';
        }
    }
    for (int y = 0; y < 6; y++) {
        inventory[y] = 0;
    }
    for (int i = 0; i < 5; i++) {
        oreActive[i] = true;
    }

    srand(static_cast<unsigned int>(time(0)));
    for (int r = 0; r < 5; r++) {
        orelocationx[r] = rand() % 20;
        orelocationy[r] = rand() % 20;
    }


}

char Mine::mineInput()
{

    keyPressed = _getch();
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
    case 'p':
        return 'P';
    case '2':
        return 'F';
    default:
        break;
    }



    if (changeX != 0 || changeY != 0) {
        int newX = playerlocationx + changeX;
        int newY = playerlocationy + changeY;

        if (newX < 20 && newX > -1 && newY < 20 && newY > -1 && change == '/') {
            change = 'R';
            Sleep(10); // Giving the computer time to synce this information with the other thread
            playerlocationx = newX;
            playerlocationy = newY;
            change = 'A';
        }

        else if (newX <= -1 && Lminefloor < 6) {
            system("cls");
            for (int o = 0; o < 5; o++) {
                oreActive[o] = true;
            }

            Lminefloor++;
            for (int x = 0; x < 5; x++) {
                do {
                    orelocationx[x] = rand() % 20;
                    orelocationy[x] = rand() % 20;
                } while (playerlocationy == orelocationy[x] && playerlocationx == orelocationx[x]);
            }
            drawMine();
            change = 'R';
            Sleep(10); // Giving the computer time to synce this information with the other thread
            playerlocationx = 19;
            change = 'S';

            change = 'A';
        }
        else if (newY >= 20 && Dminefloor < 6) {
            system("cls");
            Dminefloor++;
            for (int o = 0; o < 5; o++) {
                oreActive[o] = true;
            }
            for (int x = 0; x < 5; x++) {
                do {
                    orelocationx[x] = rand() % 20;
                    orelocationy[x] = rand() % 20;
                } while (playerlocationy == orelocationy[x] && playerlocationx == orelocationx[x]);
            }
            drawMine();
            change = 'R';
            Sleep(10); // Giving the computer time to synce this information with the other thread
            playerlocationy = 0;
            change = 'S';
            change = 'A';

        }

        else if (newX >= 20 && Lminefloor > 1) {
            system("cls");
            Lminefloor--;
            for (int o = 0; o < 5; o++) {
                oreActive[o] = true;
            }
            for (int x = 0; x < 5; x++) {
                do {
                    orelocationx[x] = rand() % 20;
                    orelocationy[x] = rand() % 20;
                } while (playerlocationy == orelocationy[x] && playerlocationx == orelocationx[x]);
            }
            drawMine();
            change = 'R';
            Sleep(10); // Giving the computer time to synce this information with the other thread
            playerlocationx = 0;
            change = 'S';
            change = 'A';

        }
        else if (newY <= -1 && Dminefloor > 1) {
            system("cls");
            Dminefloor--;
            for (int o = 0; o < 5; o++) {
                oreActive[o] = true;
            }
            for (int x = 0; x < 5; x++) {
                do {
                    orelocationx[x] = rand() % 20;
                    orelocationy[x] = rand() % 20;
                } while (playerlocationy == orelocationy[x] && playerlocationx == orelocationx[x]);
            }
            drawMine();
            change = 'R';
            Sleep(10); // Giving the computer time to synce this information with the other thread
            playerlocationy = 19;
            change = 'S';
            change = 'A';
        }
    }
    for (int d = 0; d < 5; d++) {
        for (int e = 0; e < 5; e++) {
            if (playerlocationy == orelocationy[d] && playerlocationx == orelocationx[d] && oreActive[d] == true) {
                //std::cout << "obtained" << std::endl;
                //Sleep(2000);
                switch (ores[Dminefloor - 1]) {
                case 'I':
                    inventory[0]++;
                    break;
                case 'S':
                    inventory[1]++;
                    break;
                case 'G':
                    inventory[2]++;
                    break;
                case 'R':
                    inventory[3]++;
                    break;
                case 'A':
                    inventory[4]++;
                    break;
                case 'P':
                    inventory[5]++;
                    break;
                }
                system("cls");
                oreActive[d] = false;
                Game::PlayMusic(L"Dig.mp3", false);
                drawMine();
            }
        }
    }
    return '/';
}

void Mine::drawMine() ////Show physical map
{
    clearMine();
    world[playerlocationy][playerlocationx] = '+';
    for (int a = 0; a < 5; a++) {
        if (oreActive[a]) {
            world[orelocationy[a]][orelocationx[a]] = ores[Dminefloor - 1];
        }
    }
    std::cout << "+----------------------------------------+" << std::endl;
    for (int row = 0; row < 20; row++) {
        std::cout << "|";
        for (int col = 0; col < 20; col++) {
            std::cout << world[row][col] << ' ';
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+----------------------------------------+" << std::endl;
    for (int v = 0; v < 6; v++) {
        std::cout << inventory[v] << ' ' << orelist[v] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Mine level(Down): " << Dminefloor << std::endl;
    std::cout << "Mine level(Left): " << Lminefloor << std::endl;
}

void Mine::update()
{

    if (change != '/') {
        if (change == 'R') {

            Game::overwriteText(std::string(1, '+'), playerlocationx * 2 + 1, playerlocationy + 1, false, 0x0F);

        }
        else if (change == 'A') {
            std::string temp(1, '+');
            Game::overwriteText(temp, playerlocationx * 2 + 1, playerlocationy + 1, true, 0x0F);
        }
        else if (change == 'S') {
            for (int w = 0; w < 5; w++) {
                Game::overwriteText(std::string(1, ores[Dminefloor - 1]), orelocationx[w] * 2 + 1, orelocationy[w] + 1, true, 0x0F);
            }
        }

        change = '/';
    }

}

void Mine::clearMine() //// Make the map become a blank state
{
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 20; col++) {
            world[row][col] = ' ';
        }
    }

}