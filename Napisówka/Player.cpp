#include "Player.h"



Player::Player(unsigned short int x, char name[], char race[], char cClass[], unsigned int defense)
{
	health = x;
	defense_value = defense;
	charName = new char[sizeof(name)];
	charRace = new char[sizeof(race)];
	charClass = new char[sizeof(cClass)];

	charName = name;
	charRace = race;
	charClass = cClass;
}


Player::~Player()
{
}

void Player::move()
{
}

/*int Player::getValue(char value[])
{
	if ("defense" == value)
		return defense_value;
	else if ("health" == value)
		return health;
	else
		return 0;
}

void Player::setValue(char value[], int x)
{
	if ("defense" == value)
		defense_value = x;
	else if ("health" == value)
		health = x;
}*/
