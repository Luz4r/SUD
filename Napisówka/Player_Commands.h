#pragma once
#include "Game.h"
#include "File_Manager.h"

class Player_Commands
{
public:
	Player_Commands(Game*);
	~Player_Commands();
	void look();
	void save_game();
	void load_game();
	void playerInfo();
	void goToMenu();
	void quit();
	void move_north();
	void move_south();
	void move_west();
	void move_east();
	void fight(string);
private:
	void wait(int);
	Game *_game;
};

