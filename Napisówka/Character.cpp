#include "Character.h"


Character::Character(unsigned short int x, char name[], char race[], char cClass[])
{
	health = x;
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

void Character::variable_out(Character postac)
{
	printw("Nazwa: %s\n", postac.charName);
	printw("Rasa: %s\n", postac.charRace);
	printw("Klasa: %s\n", postac.charClass);
	printw("Ilosc punktow zycia: %d\n", postac.health);
}
