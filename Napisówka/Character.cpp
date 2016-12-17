#include "Character.h"


Character::Character(unsigned short int x, char name[], char race[], char cClass[], unsigned int attack, unsigned int defense)
{
	health = x;
	defense_value = defense;
	attack_value = attack;
	charName = new char [sizeof(name)];
	charRace = new char [sizeof(race)];			
	charClass = new char [sizeof(cClass)];

	charName = name;
	charRace = race;
	charClass = cClass;
}


Character::~Character()
{
}

void Character::move()
{
}

int Character::getValue(char value[])
{
	if ("attack" == value)
		return attack_value;
	if ("defense" == value)
		return defense_value;
	else
		return 0;
}

void Character::setValue(char value[], int x)
{
	if ("attack" == value)
		attack_value = x;
	if ("defense" == value)
		defense_value = x;
}
