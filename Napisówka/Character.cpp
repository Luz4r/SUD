#include "Character.h"


Character::Character(unsigned short int x, char name[], char race[], char cClass[], unsigned int defense, unsigned short int damageMIN, unsigned short int damageMAX, unsigned int hitChance, unsigned int critChance)
{
	health = x;
	defense_value = defense;
	damage_min = damageMIN;
	damage_max = damageMAX;
	crit_chance = critChance;
	hit_chance = hitChance;


	charName = new char [sizeof(name)];
	charRace = new char [sizeof(race)];			
	charClass = new char [sizeof(cClass)];
	charName = name;
	charRace = race;
	charClass = cClass;
}


Character::~Character()
{
}

void Character::move()
{
}

int Character::getValue(char value[])
{
	if ("defense" == value)
		return defense_value;
	else if ("health" == value)
		return health;
	else if ("crit_chance" == value)
		return crit_chance;
	else if ("hit_chance" == value)
		return hit_chance;
	else if ("damage_min" == value)
		return damage_min;
	else if ("damage_max" == value)
		return damage_max;
	else
		return 0;
}

void Character::setValue(Value value, int x)
{
	switch (value)
	{
	case Health:
		health = x;
	case defenseValuePlus:
		defense_value += x;
	case defenseValueMinus:
		defense_value -= x;
	case damage_maxPlus:
		damage_max += x;
	case damage_maxMinus:
		damage_max -= x;
	case damage_minPlus:
		damage_min += x;
	case damage_minMinus:
		damage_min -= x;
	case hit_chancePlus:
		hit_chance += x;
	case hit_chanceMinus:
		hit_chance -= x;
	case crit_chancePlus:
		crit_chance += x;
	case crit_chanceMinus:
		crit_chance -= x;
	}
	/*if ("defense" == value)
		defense_value = x;
	else if ("health" == value)
		health = x;
	else if ("crit_chance" == value)
		crit_chance = x;
	else if ("hit_chance" == value)
		hit_chance = x;
	else if ("damage_min" == value)
		damage_min = x;
	else if ("damage_max" == value)
		damage_max = x;*/
}
