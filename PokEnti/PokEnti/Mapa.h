#pragma once
#include "Ash.h"
#include <iostream>
#include <Windows.h>


const int WIDTH = 40;
const int HEIGHT = 40;

enum class TypeOfCell
{
	EMPTY,
	PLAYER,
	POKEMON,
	WALL,
	COUNT
};


class Map {
private:
	TypeOfCell typeCell;
	
	char grid;
	static const int MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_1 = 12;
	static const int NUM_ROWS = 4;
	static const int NUM_COLUMNS = 4;


public:
	void InitializeMap(Ash& player);
	void PrintBoard(Ash& player);
	void SetPos(Ash& player, Movement move);
	bool CheckMovement(const Ash& player, Movement move); 
	void MovementAsh(Ash& player, Movement move);
	void SetMovement(Ash& player, Movement& move);
	void CapturePokemon(Ash& player);
	bool GameOver();
	
	//Void CalculateDistancePokemon    "calcular la distancia entre pokemon i player
	// Void CapturePokemon "if distance es x & imput spacebar = capturar pokemon"  Si es posible tmb la direció

	//move player

	
};
