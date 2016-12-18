#pragma once
#include "Character.h"

class NPC :
	public Character
{
private:
	char *charName;
	char *charRace;
	char *charClass;
	unsigned short int health;
public:
	NPC(unsigned short int = 1, char[] = "NPC", char[] = "Rasa", char[] = "Klasa");
	~NPC();
	void move();
};

