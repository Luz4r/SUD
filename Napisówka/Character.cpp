#include "Character.h"

Character::Character(string name, Rasa race, Klasa cClass, unsigned short int a, unsigned short int defense, unsigned short int damageMIN, unsigned short int damageMAX, unsigned short int hitChance, unsigned short int critChance, int cx, int cy)
{
	charName = name;
	charRace = race;
	charClass = cClass;

	health = a;
	defense_value = defense;
	damage_min = damageMIN;
	damage_max = damageMAX;
	crit_chance = critChance;
	hit_chance = hitChance;
	x = cx;
	y = cy;
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
		return (int)charRace;
	case CharacterClass:
		return (int)charClass;
	case CORDX:
		return x;
	case CORDY:
		return y;
	}
}

void Character::setValue(settingValue value, int a)
{
	switch (value)
	{
	case setHealth:
		health = a;
		break;
	case defenseValuePlus:
		defense_value += a;
		break;
	case defenseValueMinus:
		defense_value -= a;
		break;
	case damage_maxPlus:
		damage_max += a;
		break;
	case damage_maxMinus:
		damage_max -= a;
		break;
	case damage_minPlus:
		damage_min += a;
		break;
	case damage_minMinus:
		damage_min -= a;
		break;
	case hit_chancePlus:
		hit_chance += a;
		break;
	case hit_chanceMinus:
		hit_chance -= a;
		break;
	case crit_chancePlus:
		crit_chance += a;
		break;
	case crit_chanceMinus:
		crit_chance -= a;
		break;
	case CORDX_plus:
		x += a;
		break;
	case CORDX_minus:
		x -= a;
		break;
	case CORDY_plus:
		y += a;
		break;
	case CORDY_minus:
		y -= a;
		break;
	case CORDX_replace:
		x = a;
		break;
	case CORDY_replace:
		y = a;
		break;
	}
}

char * Character::getCharName()
{
	char* Name = (char *)(charName.c_str());
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
	case Gnome:
		return "Gnome";
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


