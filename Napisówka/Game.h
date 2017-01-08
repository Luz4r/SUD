#pragma once
#include "curses.h"
#include <ctime>
#include <cstdlib>
#include "Character.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Game
{
private:
	Character* player;
	unsigned short int which = 1;
	unsigned short int mark;
	void intro();
	void createColors();
	Character createPlayer();
	void chooseRace();
	void chooseClass();
	void play();
	void fight(Character, Character);
	void runMenu();
	void saveGame(Character&);
	void loadGame();

	enum Gamestate { MENU, GAME, END, FIGHT };
	Gamestate state;
public:
	Game();
	~Game();
	void runGame();
	struct Gamesaver
	{
		unsigned short int health;
		unsigned short int hit_chance;
		unsigned short int crit_chance;
		unsigned short int damage_min;
		unsigned short int damage_max;
		unsigned short int defense_value;
		unsigned short int charRace;
		unsigned short int charClass;
	};
};

