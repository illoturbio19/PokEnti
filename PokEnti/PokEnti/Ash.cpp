#include "Ash.h"




void Ash::CapturedPokemons(Ash& player)
{
	player.num_pokemons_captured++;
}

Position2D Ash::GetPos() const
{
	return m_pos;
}

void Ash::SetPos(const Position2D pos)
{
	m_pos = pos;
}

char Ash::GetDirection() const
{
	return direction;
}

void Ash::SetDirection(char newDirection)
{
	direction = newDirection;
}
