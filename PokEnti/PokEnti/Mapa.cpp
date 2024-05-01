#include "Mapa.h"


Map::Map() {
    // Initialize the map with empty spaces
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            grid[i][j] = ' ';
        }
    }
}

void Map::drawMap() {
    // Draw the map
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Map::updateMap(int ashX, int ashY) {
    // Update the map with the position of Ash
    grid[ashY][ashX] = 'A'; // 'A' represents Ash on the map
}