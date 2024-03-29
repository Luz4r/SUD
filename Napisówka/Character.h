#pragma once
#include <string>

using namespace std;

class Character
{
public:
	enum Rasa { NULL_Race, Cz�owiek, Elf, Krasnolud, Gnom, Wolf };
	enum Klasa { NULL_Class, Wojownik, �ucznik, �otrzyk };
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

	int x;
	int y;
public:
	Character(string = "Nazwa", Rasa = NULL_Race, Klasa = NULL_Class, unsigned short int = 1, unsigned short int = 1, unsigned short int = 1, unsigned short int = 3, unsigned short int = 50, unsigned short int = 5, int = 0, int = 0);
	~Character();
	enum settingValue {
		setHealth, defenseValueMinus, defenseValuePlus, hit_chanceMinus, hit_chancePlus, crit_chanceMinus, crit_chancePlus, damage_minMinus, damage_minPlus, damage_maxMinus, damage_maxPlus, CORDX_plus, CORDY_plus,
		CORDX_minus, CORDY_minus, CORDX_replace, CORDY_replace};
	enum gettingValue {getHealth, Defense, HitChance, CritChance, DamageMin, DamageMax, CharacterRace, CharacterClass, CORDX, CORDY};
	int getValue(gettingValue);
	void setValue(settingValue, int);
	char* getCharName();
	string getStringName();
	char* getRace();
	char* getClass();
};