#pragma once
#include "Game.h"
#include "Enemy.h"
#include "Player.h"
#include "NPC.h"

class Character
{
private:
	unsigned short int health;
	char *charName;
	char *charRace;
	char *charClass;
	unsigned int attack_value;
	unsigned int defense_value;
public:
	Character(unsigned short int = 1, char[] = "Nazwa", char[] = "Rasa", char[] = "Klasa", unsigned int = 1, unsigned int = 1);
	~Character();
	virtual void move();
	virtual int getValue(char[]);
	virtual void setValue(char[], int);
};