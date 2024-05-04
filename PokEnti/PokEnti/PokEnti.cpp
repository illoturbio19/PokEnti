#include "Mapa.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>

int main() {
    // Seed for random number generation
    srand(time(NULL));
    const int FPS = 60;

    // Create an instance of the player and the map
    Ash player;
    Map gameMap;

    // Initialize the game map with the player
    gameMap.InitializeMap(player);

    // Game loop control
    bool gameRunning = true;

    // Game loop
    while (gameRunning && !gameMap.GameOver()) {
        system("cls"); // Clear screen

        // Print the game board
        gameMap.PrintBoard(player);

        // Get movement input
        Movement move = Movement::INVALID;

        // Set movement direction
        gameMap.SetMovement(player, move);

        // Check if movement is valid
        if (gameMap.CheckMovement(player, move)) {
            // Move the player if the input direction matches the direction Ash is facing
            if (move == Movement::UP && player.GetDirection() == '^') {
                gameMap.MovementAsh(player, move);
            }
            else if (move == Movement::DOWN && player.GetDirection() == 'v') {
                gameMap.MovementAsh(player, move);
            }
            else if (move == Movement::LEFT && player.GetDirection() == '<') {
                gameMap.MovementAsh(player, move);
            }
            else if (move == Movement::RIGHT && player.GetDirection() == '>') {
                gameMap.MovementAsh(player, move);
            }

        }

       
        if (GetAsyncKeyState(VK_SPACE)) {
            gameMap.CapturePokemon(player);
        }

        // Wait for a key release to prevent rapid movement
        while (_kbhit()) {
            _getch(); // Clear the keyboard buffer
        }

        // Sleep for a short duration to prevent unnecessary CPU usage
        Sleep(10000 / FPS);
    }

    // Game over
    system("cls");
    std::cout << "Game Over!" << std::endl;

    return 0;
}
