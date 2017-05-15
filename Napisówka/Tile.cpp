#include "Tile.h"



Tile::Tile(string tileName, string desc, int cx, int cy/*, map <string, Character>mobs*/)
{
	name = tileName;
	description = desc;
	cords.push_back(cx);
	cords.push_back(cy);
	/*tileMobs = mobs;*/
}


Tile::~Tile()
{
}

string Tile::getStringName()
{
	return name;
}

char * Tile::getDesc()
{
	char* desc = (char*)(description.c_str());
	return desc;
}

string Tile::getStringDesc()
{
	return description;
}

char * Tile::getCharName()
{
	char* tileName = (char*)(name.c_str());
	return tileName;
}
