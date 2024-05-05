#pragma once
#include "Ash.h"
#include <iostream>
#include <Windows.h>
#include <vector>

const int WIDTH = 100;
const int HEIGHT = 100;
int MAX(int a, int b); 
int MIN(int a, int b);
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
    static const int MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_1 = 1;
    static const int MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_2 = 2;
    static const int MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_3 = 3;
    static const int MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_4 = 4;
    static const int NUM_ROWS = 4; // Adjust if needed
    static const int NUM_COLUMNS = 4; // Adjust if needed
    static const int VIEW_WIDTH = 30; // Width of the player's field of view
    static const int VIEW_HEIGHT = 15; // Height of the player's field of view
    std::vector<int> pokemonsLeftInZone;

public:
    Map();

    void InitializeMap(Ash& player);
    void SetPlayerPosition(Ash& player);
    void InitializePokemonsInZone(int startX, int endX, int startY, int endY, int numPokemons);
    void PrintBoard(Ash& player);
    void SetPos(Ash& player, Movement move);
    bool CheckMovement(const Ash& player, Movement move);
    void MovementAsh(Ash& player, Movement move);
    void SetMovement(Ash& player, Movement& move);
    void CapturePokemon(Ash& player);
    void OpenGate1(Ash& player);
    void OpenGate2(Ash& player);
    void OpenGate3(Ash& player);
    bool GameOver();
};
