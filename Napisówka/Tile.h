#pragma once
#include <map>
#include <vector>
#include "Character.h"

using namespace std;

class Tile
{
private:
	string name;
	string description;

public:
	Tile(string = "Nazwa", string = "Opis", int = 0, int = 0);
	~Tile();

	vector<int> cords;
	map <string, Character> tileMobs;
	string getStringName();
	char* getDesc();
	string getStringDesc();
	char* getCharName();
};

