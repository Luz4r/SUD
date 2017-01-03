#pragma once
#include "curses.h"
#include <ctime>
#include <cstdlib>
#include "Character.h"

class Game
{
private:
	unsigned short int which = 1;
	unsigned short int mark;
	void intro();
	void createColors();
	void createPlayer();
	void chooseRace();
	void chooseClass();
	void play();
	void fight(Character, Character);

	enum Gamestate { MENU, GAME, END, FIGHT };
	Gamestate state;
public:
	Game();
	~Game();
	void runGame();
	void runMenu();
};

