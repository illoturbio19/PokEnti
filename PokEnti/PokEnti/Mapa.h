#pragma once
#include "Ash.h"
#include <iostream>

const int NUM_ROWS = 4;
const int NUM_COLUMNS = 4;


class Map {
private:
	static const int WIDTH = 10; // Width of the map
	static const int HEIGHT = 10; // Height of the map
	char grid[WIDTH][HEIGHT]; // Grid representing the map

public:
	Map();
	void drawMap();
	void updateMap(int ashX, int ashY);
};




//codi de aa1_03

//move ash
/*void MovePlayer(Player& player, Movement move)
{
	board[player.pos_x][player.pos_y].player = false;
	SetPos(player, move);
	if (ExistCoin(player))
	{
		player.AddScore(player);
		board[player.pos_x][player.pos_y].coin = false;
		board[player.pos_x][player.pos_y].player = true;
	}
}*/

//set pos
/*void SetPos(Player& player, Movement& move)
{
	if (move == Movement::UP) { player.pos_x--; }
	else if (move == Movement::DOWN) { player.pos_x++; }
	else if (move == Movement::LEFT) { player.pos_y--; }
	else if (move == Movement::RIGHT) { player.pos_y++; } // Corrected syntax, removed unnecessary condition
}*/

//check movement
/*bool CheckMovement(Player player, Movement move)
{
	int newRow = player.pos_x, newColumn = player.pos_y;
	if (move == Movement::UP) { newRow--; }
	else if (move == Movement::DOWN) { newRow++; }
	else if (move == Movement::RIGHT) { newColumn++; }
	else if (move == Movement::LEFT) { newColumn--; }
	if (newRow < 0 || newRow >= NUM_ROWS || newColumn < 0 || newColumn >= NUM_COLUMNS || board[newRow][newColumn].rock == true)
	{
		std::cout << "The movement is invalid, try another" << std::endl;
		system("pause");
		return false;
	}
	return true;
}*/

//set movement
/*bool SetMovement(char movement, Movement& move)
{
	if (movement == 'w' || movement == 'W' || movement == UP_ARROW) { movement == UP; }
	else if (movement == 's' || movement == 'S' || movement == DOWN_ARROW) { move = Movement::DOWN; }
	else if (movement == 'a' || movement == 'A' || movement == LEFT_ARROW) { move = Movement::LEFT; }
	else if (movement == 'd' || movement == 'D' || movement == RIGHT_ARROW) { move = Movement::RIGHT; }
	else return false;
	return true;
}*/

