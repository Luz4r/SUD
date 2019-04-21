#pragma once

class File_Manager
{
public:
	File_Manager();
	~File_Manager();
	static void save_game(Game&);
	static void load_game(Game&);
private:
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

