#include "Character.h"

Character::Character(string name, Rasa race, Klasa cClass, unsigned short int x, unsigned int defense, unsigned short int damageMIN, unsigned short int damageMAX, unsigned int hitChance, unsigned int critChance)
{
	charName = name;
	charRace = race;
	charClass = cClass;

	health = x;
	defense_value = defense;
	damage_min = damageMIN;
	damage_max = damageMAX;
	crit_chance = critChance;
	hit_chance = hitChance;
}


Character::~Character()
{
}

int Character::getValue(gettingValue value)
{
	switch (value)
	{
	case getHealth:
		return health;
	case Defense:
		return defense_value;
	case DamageMax:
		return damage_max;
	case DamageMin:
		return damage_min;
	case HitChance:
		return hit_chance;
	case CritChance:
		return crit_chance;
	case CharacterRace:
		return (unsigned short int)charRace;
	case CharacterClass:
		return (unsigned short int)charClass;
	}
}

void Character::setValue(settingValue value, int x)
{
	switch (value)
	{
	case setHealth:
		health = x;
		break;
	case defenseValuePlus:
		defense_value += x;
		break;
	case defenseValueMinus:
		defense_value -= x;
		break;
	case damage_maxPlus:
		damage_max += x;
		break;
	case damage_maxMinus:
		damage_max -= x;
		break;
	case damage_minPlus:
		damage_min += x;
		break;
	case damage_minMinus:
		damage_min -= x;
		break;
	case hit_chancePlus:
		hit_chance += x;
		break;
	case hit_chanceMinus:
		hit_chance -= x;
		break;
	case crit_chancePlus:
		crit_chance += x;
		break;
	case crit_chanceMinus:
		crit_chance -= x;
		break;
	}
}

char * Character::getCharName()
{
	char* Name = (char *)(const char*)(charName.c_str());
	return Name;
}

string Character::getStringName()
{
	return charName;
}

char* Character::getRace()
{
	switch (charRace)
	{
	case NULL_Race:
		return "Brak rasy";
	case Cz³owiek:
		return "Czlowiek";
	case Elf:
		return "Elf";
	case Krasnolud:
		return "Krasnolud";
	case Gnom:
		return "Gnom";
	}
}

char* Character::getClass()
{
	switch (charClass)
	{
	case NULL_Class:
		return "Brak klasy";
	case Wojownik:
		return "Wojownik";
	case £ucznik:
		return "Lucznik";
	case £otrzyk:
		return "Lotrzyk";
	}
}


