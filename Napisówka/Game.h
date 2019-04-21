#pragma once
#include "curses.h"
#include "Tile.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

class Player_Commands;

class Game
{
public:
	typedef void(Player_Commands::*pointer_type)();
	typedef void(Player_Commands::*pointer_type2)(string);
	enum Gamestate { MENU, GAME, END, FIGHT };
	Tile currentTile;
	Character* player;
	Gamestate state;
	map<vector<int>, Tile>all_tiles;
	int ammount_of_tiles;
private:
	Player_Commands *player_commands;
	void createPlayer();
	void chooseRace();
	void chooseClass();

	map <string, pointer_type> commands;
	map <string, pointer_type2> commands2;
	pointer_type myfunction;
	pointer_type2 myfunction2;
	void checkInput();

	int ycord, xcord;
	void create_colors();
	void intro();
	void play();
	void run_menu();

	void create_commands();
public:
	Game();
	~Game();

	void run_game();
};
