#pragma once
#include <iostream>
#include <Windows.h>
enum class Movement { UP, DOWN, LEFT, RIGHT, INVALID };
class Ash
{
	std::string m_name;
	char m_char;

	int m_x, m_y;
public:
	int pokemons;

	Ash();

	~Ash();
};

