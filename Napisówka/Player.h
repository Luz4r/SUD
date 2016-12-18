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
	unsigned short int attack_value;
	unsigned short int defense_value;
public:
	Player(unsigned short int = 1, char[] = "Gracz", char[] = "Rasa", char[] = "Klasa", unsigned int = 1, unsigned int = 1);
	~Player();
	void move();
	int getValue(char[]);
	void setValue(char[], int);
};

