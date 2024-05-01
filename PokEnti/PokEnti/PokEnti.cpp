#include <iostream>
#include "Ash.h"
#include "Mapa.h"

int main() {
    Map map;
    Ash ash(5, 5); // Initial position of Ash

    // Update the map with the initial position of Ash
    map.updateMap(ash.getX(), ash.getY());
    map.drawMap();

    char movement;
    while (true) {
        std::cout << "Enter movement (W/A/S/D): ";
        std::cin >> movement;

        // Move Ash according to user input
        switch (movement) {
        case 'W':
            ash.moveUp();
            break;
        case 'A':
            ash.moveLeft();
            break;
        case 'S':
            ash.moveDown();
            break;
        case 'D':
            ash.moveRight();
            break;
        default:
            std::cout << "Invalid input!" << std::endl;
            continue; // Restart the loop for valid input
        }

        // Clear the previous position of Ash on the map
        map.updateMap(ash.getX(), ash.getY());
        map.drawMap();
    }

    return 0;
}
