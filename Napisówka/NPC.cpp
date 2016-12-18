#include "NPC.h"

NPC::NPC(unsigned short int x, char name[], char race[], char cClass[])
{
	health = x;
	charName = new char[sizeof(name)];
	charRace = new char[sizeof(race)];
	charClass = new char[sizeof(cClass)];

	charName = name;
	charRace = race;
	charClass = cClass;
}


NPC::~NPC()
{
}

void NPC::move()
{
}
