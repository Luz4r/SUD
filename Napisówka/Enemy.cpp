#include "Enemy.h"



Enemy::Enemy(unsigned short int x, char name[], char race[], char cClass[], unsigned int defense, unsigned short int damageMIN, unsigned short int damageMAX, unsigned int hitChance, unsigned int critChance)
{
	health = x;
	defense_value = defense;
	damage_min = damageMIN;
	damage_max = damageMAX;
	crit_chance = critChance;
	hit_chance = hitChance;


	charName = new char[sizeof(name)];
	charRace = new char[sizeof(race)];
	charClass = new char[sizeof(cClass)];
	charName = name;
	charRace = race;
	charClass = cClass;
}


Enemy::~Enemy()
{
}

void Enemy::move()
{
}

int Enemy::getValue(Value value)
{
	switch (value)
	{
	case Health:
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
	}
}

void Enemy::setValue(Value value, int x)
{
	switch (value)
	{
	case Health:
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

char* Enemy::getChar(Value value)
{
	switch (value)
	{
	case Name:
		return charName;
		break;
	case Race:
		return charRace;
		break;
	case Class:
		return charClass;
		break;
	}
}