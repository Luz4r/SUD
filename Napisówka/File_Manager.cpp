#include "Player_Commands.h"



File_Manager::File_Manager()
{
}


File_Manager::~File_Manager()
{
}

void File_Manager::save_game(Game &game)
{
	Playersaver save =
	{
		game.player->getValue(Character::getHealth),
		game.player->getValue(Character::HitChance),
		game.player->getValue(Character::CritChance),
		game.player->getValue(Character::DamageMin),
		game.player->getValue(Character::DamageMax),
		game.player->getValue(Character::Defense),
		game.player->getValue(Character::CharacterRace),
		game.player->getValue(Character::CharacterClass),
		game.player->getValue(Character::CORDX),
		game.player->getValue(Character::CORDY)
	};

	typedef map<vector<int>, Tile>::iterator it_type;

	ofstream file("save.bin", ios::binary);
	ofstream tiles("files\\savedTiles.txt", ios::out);
	if (file.good() && tiles.good())
	{
		file.write((const char *)& save, sizeof save);
		file.write((game.player->getStringName()).c_str(), game.player->getStringName().size() + 1);

		for (it_type iterator = game.all_tiles.begin(); iterator != game.all_tiles.end(); iterator++)
		{
			tiles << iterator->second.getStringName() << endl;
			tiles << iterator->second.getStringDesc() << endl;
			tiles << iterator->second.cords[0] << endl;
			tiles << iterator->second.cords[1] << endl;
			tiles.flush();
		}

		printw("Zapis pomyslnie wykonany\n\n");
	}
	else
	{
		printw("Wystapil blad podczas zapisywania pliku\n\n");
	}
	file.close();
	tiles.close();
}

void File_Manager::load_game(Game &game)
{
	game.all_tiles.clear();
	Playersaver save;
	string name;

	ifstream file("save.bin", ios::binary);

	ifstream tiles("files\\savedTiles.txt", ios::in);

	clear();

	if (file.good() && tiles.good())
	{
		file.read((char *)& save, sizeof(save));
		getline(file, name, '\0');

		game.player = new Character(name, Character::Rasa(save.charRace), Character::Klasa(save.charClass), save.health, save.defense_value, save.damage_min, save.damage_max, save.hit_chance, save.crit_chance, save.x, save.y);

		string buffor;
		string name;
		string desc;
		int nr_linii = 1;
		game.ammount_of_tiles = 0;
		vector<int> cords;

		while (getline(tiles, buffor))
		{
			switch (nr_linii)
			{
			case 1:
				name = buffor;
				break;
			case 2:
				desc = buffor;
				break;
			case 3:
				cords.push_back(stoi(buffor));
				break;
			case 4:
				cords.push_back(stoi(buffor));
				game.all_tiles[cords] = Tile(name, desc, cords[0], cords[1]);
				game.ammount_of_tiles++;
				nr_linii = 0;
				cords.clear();
				break;
			}
			nr_linii++;
		}

		auto cordinates = game.all_tiles.find({ game.player->getValue(Character::CORDX), game.player->getValue(Character::CORDY) });
		game.currentTile = cordinates->second;

		printw("Pomyslnie wczytano twoj zapis");
		game.state = Game::GAME;
	}
	else
	{
		printw("Twoj zapis jest niemozliwy do odczytania\n");
		printw("Sprawdz pliki:\n");
		attron(A_REVERSE);
		printw("save.bin\n\n");
		printw("savedTiles.txt");
		attroff(A_REVERSE);
		game.state = Game::MENU;
	}
	file.close();
	tiles.close();
	getch();
}
