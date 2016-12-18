#pragma once

class Character
{
private:
	char *charName;
	char *charRace;
	char *charClass;
	unsigned short int health;
	unsigned int hit_chance;
	unsigned int crit_chance;
	unsigned short int damage_min;
	unsigned short int damage_max;
	unsigned short int defense_value;
public:
	Character(unsigned short int = 1, char[] = "Nazwa", char[] = "Rasa", char[] = "Klasa", unsigned int = 1, unsigned short int = 1, unsigned short int = 3, unsigned int = 50, unsigned int = 5);
	~Character();
	enum Value { Health, defenseValueMinus, defenseValuePlus, hit_chanceMinus, hit_chancePlus, crit_chanceMinus, crit_chancePlus, damage_minMinus, damage_minPlus, damage_maxMinus, damage_maxPlus };
	virtual void move();
	virtual int getValue(char[]);
	virtual void setValue(Value, int);
};