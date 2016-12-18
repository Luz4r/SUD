#pragma once
#include "Character.h"

class Enemy :
	public Character
{
private:
	char *charName;
	char *charRace;
	char *charClass;
	unsigned short int health;
	unsigned short int attack_value;
	unsigned short int defense_value;
public:
	Enemy(unsigned short int = 1, char[] = "Wrog", char[] = "Rasa", char[] = "Klasa", unsigned int = 1, unsigned int = 1);
	~Enemy();
	void move();
	int getValue(char[]);
	void setValue(char[], int);
};

