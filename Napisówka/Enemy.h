#pragma once
#include "Character.h"

class Enemy :
	public Character
{
private:
	char *charName;
	char *charRace;
	char *charClass;
	unsigned int hit_chance;
	unsigned int crit_chance;
	unsigned short int damage_max;
	unsigned short int damage_min;
	unsigned short int health;
	unsigned short int defense_value;
public:
	Enemy(unsigned short int = 1, char[] = "Wrog", char[] = "Rasa", char[] = "Klasa", unsigned int = 1);
	~Enemy();
	void move();
	/*int getValue(char[]);
	void setValue(char[], int);*/
};

