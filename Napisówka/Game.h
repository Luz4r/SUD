#pragma once
#include "curses.h"
#include "Tile.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

class Game
{
public:
	typedef void(Game::*pointerType)();
	typedef void(Game::*pointerType2)(string);
private:
	Character* player;
	void createPlayer();
	void chooseRace();
	void chooseClass();

	int ammountOfTiles;
	Tile currentTile;
	map<vector<int>, Tile>AllTiles;


	map <string, pointerType> Commands;
	map <string, pointerType2> Commands2;
	pointerType myfunction;
	pointerType2 myfunction2;
	void checkInput();

	int ycord, xcord;
	void createColors();
	void intro();
	void play();
	void runMenu();
	void loadGame();
	void wait(int seconds);

	void createCommands();
	void saveGame();
	void quit();
	void fight(string);
	void playerInfo();
	void goToMenu();
	void move_north();
	void move_south();
	void move_west();
	void move_east();
	void look();

	enum Gamestate { MENU, GAME, END, FIGHT };
	Gamestate state;
public:
	Game();
	~Game();

	void runGame();

	struct Playersaver
	{
		int health;
		int hit_chance;
		int crit_chance;
		int damage_min;
		int damage_max;
		int defense_value;
		int charRace;
		int charClass;
		int x;
		int y;
	};
};

