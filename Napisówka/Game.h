#pragma once
#include "curses.h"
#include <ctime>
#include <cstdlib>
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "NPC.h"

class Game
{
private:
	const char option1[12] = "1. Nowa Gra";
	const char option2[15] = "2. Wczytaj gre";
	const char option3[9] = "3. Wyjdz";
	unsigned short int which = 1;
	unsigned short int mark;
	void intro();

	enum Gamestate { MENU, GAME, END, FIGHT };
	Gamestate state;
public:
	Game();
	~Game();
	void runGame();
	void createColors();
	void runMenu();
	void play();
	void fight(Player, Enemy);
};

