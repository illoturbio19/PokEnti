#pragma once
#include "Pokemons.h"
enum class Movement { UP, DOWN, LEFT, RIGHT, INVALID };
class Ash {

    Position2D m_pos;

    char direction;
    int num_pokemons_captured;


public:
    Position2D GetPos() const;
    void CapturedPokemons(Ash& player);
    void SetPos(const Position2D pos);
    char GetDirection() const;
    void SetDirection(char newDirection);
};
