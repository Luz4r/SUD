#pragma once
#include "Character.h"

class Player :
	public Character
{
private:
	char *charName;
	char *charRace;
	char *charClass;
	unsigned short int health;
	unsigned short int hit_chance;
	unsigned short int crit_chance;
	unsigned short int damage_max;
	unsigned short int damage_min;
	unsigned short int defense_value;
public:
	Player(unsigned short int = 1, char[] = "Gracz", char[] = "Rasa", char[] = "Klasa", unsigned int = 1, unsigned short int = 1, unsigned short int = 3, unsigned int = 50, unsigned int = 5);
	~Player();
	void move();
	int getValue(Value);
	void setValue(Value, int);
	char* getChar(Value);
};

