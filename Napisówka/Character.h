#pragma once
#include <string>

using namespace std;

class Character
{
public:
	enum Rasa { NULL_Race, Cz³owiek, Elf, Krasnolud, Gnom };
	enum Klasa { NULL_Class, Wojownik, £ucznik, £otrzyk };
private:
	string charName;
	Rasa charRace;
	Klasa charClass;

	unsigned short int health;
	unsigned short int hit_chance;
	unsigned short int crit_chance;
	unsigned short int damage_min;
	unsigned short int damage_max;
	unsigned short int defense_value;
public:
	Character(string = "Nazwa", Rasa = NULL_Race, Klasa = NULL_Class, unsigned short int = 1, unsigned int = 1, unsigned short int = 1, unsigned short int = 3, unsigned int = 50, unsigned int = 5);
	~Character();
	enum settingValue {setHealth, defenseValueMinus, defenseValuePlus, hit_chanceMinus, hit_chancePlus, crit_chanceMinus, crit_chancePlus, damage_minMinus, damage_minPlus, damage_maxMinus, damage_maxPlus};
	enum gettingValue {getHealth, Defense, HitChance, CritChance, DamageMin, DamageMax, CharacterRace, CharacterClass};
	int getValue(gettingValue);
	void setValue(settingValue, int);
	char* getCharName();
	string getStringName();
	char* getRace();
	char* getClass();
};