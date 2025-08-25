#include <iostream>
#include <thread>
#include "Game.h"
#include <Windows.h>
using std::cout;
using std::endl;
using std::thread;

int main(void) {
	Game game;

    game.fullsc();
    Sleep(1000); // Give time for console window to enter full screen
    game.ShowConsoleCursor(false); // Hides the cursor

    thread gameOutput(&Game::gameDisplay, &game);
    thread gameInput(&Game::gameInput, &game);

    if (gameInput.joinable()) {
        gameInput.join();
    }

    if (gameOutput.joinable()) {
        gameOutput.join();
    }

    game.ShowConsoleCursor(true); // Shows the cursor again
	return 0;
}
