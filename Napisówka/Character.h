#pragma once

class Character
{
private:
	char *charName;
	char *charRace;
	char *charClass;
	unsigned short int health;
	unsigned short int attack_value;
	unsigned short int defense_value;
public:
	Character(unsigned short int = 1, char[] = "Nazwa", char[] = "Rasa", char[] = "Klasa", unsigned int = 1, unsigned int = 1);
	~Character();
	virtual void move();
	virtual int getValue(char[]);
	virtual void setValue(char[], int);
};