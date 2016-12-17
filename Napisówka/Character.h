#pragma once
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "NPC.h"


class Character
{
	unsigned short int health;
	char *charName;
	char *charRace;
	char *charClass;
public:
	unsigned int attack_value;
	unsigned int defense_value;
	Character(unsigned short int = 1, char[] = "Nazwa", char[] = "Rasa", char[] = "Klasa");
	~Character();
	virtual void move();
	void variable_out(Character);
};

