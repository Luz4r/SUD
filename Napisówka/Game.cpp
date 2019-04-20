#include "Game.h"

void Game::intro()
{
	char mesg[] = "Witaj w mojej grze ktora jest pretekstem do nauki C++";
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	mvprintw(ycord/3, (xcord-strlen(mesg))/2,"%s", mesg);
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));
	attron(A_REVERSE);
	mvprintw((ycord/2)+2, (xcord-6)/2, "ENJOY!\n");
	mvcur(0, 0, (ycord / 2) + 2, (xcord / 2) + 3);
	attroff(A_REVERSE);
}

void Game::createColors()
{
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
}

Game::Game()
{
	initscr();
	resize_term(60, 120);
	scrollok(stdscr, TRUE);
	getmaxyx(stdscr, ycord, xcord);
	srand(time(NULL));
	if (has_colors() == false)
	{
		endwin();
		printf("Twoja konsola nie obsluguje kolorow\n");
		return;
	}
	player = new Character;

	createColors();
	createCommands();
	
	state = MENU;
}


Game::~Game()
{
	delete player;
	endwin();
}

void Game::runGame()
{
	intro();
	noecho();
	getch();
	while (state != END)
	{
		switch (state)
		{
		case MENU:
			runMenu();
			break;
		case GAME:
			play();
			break;
		}
	}
}

void Game::runMenu()
{
	unsigned short int which = 1;
	unsigned short int mark;

	const char *choices[] = {
		"1. Nowa Gra",
		"2. Wczytaj gre",		//menu choices
		"3. Wyjdz",
	};

	int n_choices = sizeof(choices) / sizeof(char *);

	do
	{
		keypad(stdscr, true);
		clear();
		attron(COLOR_PAIR(1));
		mvprintw((ycord / 3), (xcord - 14) / 2, "Wybierz opcje:");
		attroff(COLOR_PAIR(1));
		int y = 2;

		for (int i = 0; i < n_choices; i++)
		{
			if (which == i + 1)
			{
				attron(A_REVERSE);
				mvprintw((ycord / 3) + y, (xcord - strlen(choices[i])) / 2, "%s", choices[i]);
				attroff(A_REVERSE);
			}
			else
				mvprintw((ycord / 3) + y, (xcord - strlen(choices[i])) / 2, "%s", choices[i]);
			y++;
		}

		mark = getch();
		if (mark == KEY_UP && which != 1)
			which--;
		else if (mark == KEY_DOWN && which != n_choices)
			which++;
		else if (mark == KEY_UP && which == 1)
			which = 3;
		else if (mark == KEY_DOWN && which == n_choices)
			which = 1;
		if (mark == 10)
		{
			switch (which)
			{
			case 1:
				clear();
				createPlayer();
				if (state != GAME)
					break;
				saveGame();
				getch();
				break;
			case 2:
				clear();
				loadGame();
				break;
			case 3:
				clear();
				state = END;
				break;
			}
		}
	} while (state == MENU);
}

void Game::checkInput()
{
	char* buffor = new char[50];
	char* buffor2 = new char[50];

	printw("Wpisz komende [save, quit, kill <mob>, info, menu, north, south, west, east, look]: ");
	echo();
	scanw("%s%s", buffor, buffor2);
	printw("\n");
	noecho();
	string input = buffor;
	string input_rest = buffor2;
	delete buffor;
	delete buffor2;

	auto search = Commands.find(input);
	auto search2 = Commands2.find(input);
	if (search != Commands.end())
	{
		myfunction = search->second;
		(this->*(this->myfunction))();
	}
	else if (search2 != Commands2.end())
	{
		myfunction2 = search2->second;
		(this->*(this->myfunction2))(input_rest);
	}
	else
		printw("Nie znaleziono komendy!\n\n");
}

void Game::play()
{
	Character gnom("Gnom", Character::Gnom, Character::Wojownik, 200, 20, 53, 74, 69, 9);
	currentTile.tileMobs["gnom"] = gnom;
	clear();
	look();
	while (GAME == state)
	{
		checkInput();
	}
}

void Game::createPlayer()
{
	char *buffor = new char[50];
	Character::Rasa playerRace;
	Character::Klasa playerClass;

	unsigned short int number;

	mvprintw((ycord / 3), (xcord - 19) / 2, "Podaj swoje imie: ");

	echo();

	getnstr(buffor, 50);

	string stringname = buffor;

	delete buffor;

	char *name = (char*)(stringname.c_str());

	do {
		chooseRace();
		number = getch();
	} while (number < 49 || number > 52);

	switch (number)
	{
	case 49:
		playerRace = Character::Cz³owiek;
		break;
	case 50:
		playerRace = Character::Elf;
		break;
	case 51:
		playerRace = Character::Krasnolud;
		break;
	case 52:
		playerRace = Character::Gnom;
		break;
	}

	do {
		chooseClass();
		number = getch();
	} while (number < 49 || number > 51);

	switch (number)
	{
	case 49:
		playerClass = Character::Wojownik;
		break;
	case 50:
		playerClass = Character::£ucznik;
		break;
	case 51:
		playerClass = Character::£otrzyk;
		break;
	}

	noecho();

	player = new Character(name, playerRace, playerClass, 500, 50, 50, 55, 80, 50, 0, 0);		//tworzenie gracza

	ifstream file("files\\tiles.txt", ios::in);
		if (file.good())
		{
			string buffor;
			string name;
			string desc;
			int nr_linii = 1;
			ammountOfTiles = 0;
			vector<int> cords;

			while (getline(file, buffor))
			{
				switch(nr_linii)
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
					AllTiles[cords] = Tile(name, desc, cords[0], cords[1]);
					ammountOfTiles++;
					nr_linii = 0;
					cords.clear();
					break;
				}
				nr_linii++;
			}
			
			auto cordinates = AllTiles.find({ 0,0 });
			currentTile = cordinates->second;

			player->setValue(Character::CORDX_replace, currentTile.cords[0]);
			player->setValue(Character::CORDY_replace, currentTile.cords[1]);

			state = GAME;
		}
		else
		{
			clear();
			printw("Nie mozna odczytac pliku: 'tiles.txt' !");
			state = MENU;
		}
		file.close();
		clear();
}

void Game::chooseRace()
{
	char *raceChoices[] =
	{
		"1. Czlowiek",
		"2. Elf",
		"3. Krasnolud",				//Rasy
		"4. Gnom",
		"5. ...",
		"6. ..."
	};

	int n_choices = sizeof(raceChoices) / sizeof(char *);
	int y_max = n_choices / 2;

	clear();
	mvprintw((ycord / 3), (xcord - 29) / 2, "Wybierz rase swojej postaci:");

	int y = 2;
	int x = 15;

	for (int i = 0; i < n_choices; i++)
	{
		if (i < y_max)
			mvprintw((ycord / 3) + y, ((xcord - strlen(raceChoices[i])) / 2) - x, "%s", raceChoices[i]);
		else
			mvprintw((ycord / 3) + y, ((xcord - strlen(raceChoices[i])) / 2) + x, "%s", raceChoices[i]);
		y++;
		if (i == y_max - 1)
			y = 2;
	}
	mvprintw((ycord / 3) + y_max + 3, (xcord - 16) / 2, "Wybierz numer: ");
}

void Game::chooseClass()
{
	char *classChoices[] =
	{
		"1. Wojownik",
		"2. Lucznik",
		"3. Lotrzyk",			//Klasy
		"4. ...",
		"5. ...",
		"6. ..."
	};

	int n_choices = sizeof(classChoices) / sizeof(char *);
	int y_max = n_choices / 2;

	clear();
	mvprintw((ycord / 3), (xcord - 30) / 2, "Wybierz klase swojej postaci:");

	int y = 2;
	int x = 15;

	for (int i = 0; i < n_choices; i++)
	{
		if (i < y_max)
			mvprintw((ycord / 3) + y, ((xcord - strlen(classChoices[i])) / 2) - x, "%s", classChoices[i]);
		else
			mvprintw((ycord / 3) + y, ((xcord - strlen(classChoices[i])) / 2) + x, "%s", classChoices[i]);
		y++;
		if (i == y_max - 1)
			y = 2;
	}
	mvprintw((ycord / 3) + y, (xcord - strlen("Wybierz numer: ")) / 2, "Wybierz numer: ");
}

void Game::createCommands()
{
	pointerType pointer[] =
	{
		&Game::saveGame,
		&Game::quit,
		&Game::playerInfo,
		&Game::goToMenu,
		&Game::move_north,
		&Game::move_south,
		&Game::move_west,
		&Game::move_east,
		&Game::look
	};

	pointerType2 pointer2[] =
	{
		&Game::fight
	};

	string commandName[] =														//tworzenie komend
	{
		"save",
		"quit",
		"info",
		"menu",
		"north",
		"south",
		"west",
		"east",
		"look"
	};

	string commandName2[] =
	{
		"kill"
	};

	int n_pointer = sizeof(pointer) / sizeof(pointerType);
	int n_pointer2 = sizeof(pointer2) / sizeof(pointerType);

	for (int i = 0; i < n_pointer; i++)
		Commands[commandName[i]] = pointer[i];
	for (int i = 0; i < n_pointer2; i++)
		Commands2[commandName2[i]] = pointer2[i];
}

void Game::saveGame()
{
	Playersaver save =
	{
		player->getValue(Character::getHealth),
		player->getValue(Character::HitChance),
		player->getValue(Character::CritChance),
		player->getValue(Character::DamageMin),
		player->getValue(Character::DamageMax),
		player->getValue(Character::Defense),
		player->getValue(Character::CharacterRace),
		player->getValue(Character::CharacterClass),
		player->getValue(Character::CORDX),
		player->getValue(Character::CORDY)
	};

	typedef map<vector<int>, Tile>::iterator it_type;

	ofstream file("save.bin", ios::binary);
	ofstream tiles("files\\savedTiles.txt", ios::out);
	if (file.good() && tiles.good())
	{
		file.write((const char *)& save, sizeof save);
		file.write((player->getStringName()).c_str(), player->getStringName().size() + 1);

		for (it_type iterator = AllTiles.begin(); iterator != AllTiles.end(); iterator++)
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

void Game::loadGame()
{
	AllTiles.clear();
	Playersaver save;
	string name;

	ifstream file("save.bin", ios::binary);

	ifstream tiles("files\\savedTiles.txt", ios::in);

	clear();

	if (file.good() && tiles.good())
	{
		file.read((char *)& save, sizeof(save));
		getline(file, name, '\0');

		player = new Character(name, Character::Rasa(save.charRace), Character::Klasa(save.charClass), save.health, save.defense_value, save.damage_min, save.damage_max, save.hit_chance, save.crit_chance, save.x, save.y);

		string buffor;
		string name;
		string desc;
		int nr_linii = 1;
		ammountOfTiles = 0;
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
				AllTiles[cords] = Tile(name, desc, cords[0], cords[1]);
				ammountOfTiles++;
				nr_linii = 0;
				cords.clear();
				break;
			}
			nr_linii++;
		}

		auto cordinates = AllTiles.find({ player->getValue(Character::CORDX), player->getValue(Character::CORDY)});
		currentTile = cordinates->second;

		printw("Pomyslnie wczytano twoj zapis");
		state = GAME;
	}
	else
	{
		printw("Twoj zapis jest niemozliwy do odczytania\n");
		printw("Sprawdz pliki:\n");
		attron(A_REVERSE);
		printw("save.bin\n\n");
		printw("savedTiles.txt");
		attroff(A_REVERSE);
		state = MENU;
	}
	file.close();
	tiles.close();
	getch();
}

void Game::wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

void Game::quit()
{
	state = END;
	saveGame();
}

void Game::fight(string str)
{

	auto mob = currentTile.tileMobs.find(str);

	if (mob != currentTile.tileMobs.end())
	{
		clear();
		Character b = mob->second;
		state = FIGHT;
		printw("Rozpoczynasz walke z %s\n\n", b.getCharName());

		//Character a, values
		int player_health = player->getValue(Character::getHealth);
		int player_defense = (player->getValue(Character::Defense) / 2);
		int player_rawDamage;
		int player_damage;

		//Character b, values
		int b_health = b.getValue(Character::getHealth);
		int b_defense = (b.getValue(Character::Defense) / 2);
		int b_rawDamage;
		int b_damage;

		printw("Punkty zycia %s: %d\n", player->getCharName(), player_health);
		printw("Punkty zycia %s: %d\n\n", b.getCharName(), b_health);

		printw("Wcisnij [ENTER]: ");
		getch();

		while (state == FIGHT)
		{
			//Character a
			int player_hitchance = rand() % 1000 + 1;
			int player_critchance = rand() % 1000 + 1;

			//Character b
			int b_hitchance = rand() % 1000 + 1;
			int b_critchance = rand() % 1000 + 1;

			if (player_hitchance <= (player->getValue(Character::HitChance) * 10))  //Character a, randomazing hitchance
			{
				player_rawDamage = rand() % ((player->getValue(Character::DamageMax) - player->getValue(Character::DamageMin)) + 1) + player->getValue(Character::DamageMin);
				if (player_critchance <= (player->getValue(Character::CritChance) * 10))  //Character a - check if crit
				{
					player_rawDamage *= 2;
				}
				if (player_rawDamage < b_defense)
					player_damage = 0;
				else
					player_damage = (player_rawDamage - b_defense);

				if (player_damage > b_health)
					player_damage = b_health;
			}
			else
				player_damage = 0;

			if (b_hitchance <= (b.getValue(Character::HitChance) * 10))  //Character b, randomazing hitchance
			{
				b_rawDamage = rand() % ((b.getValue(Character::DamageMax) - b.getValue(Character::DamageMin)) + 1) + b.getValue(Character::DamageMin);
				if (b_critchance <= (b.getValue(Character::CritChance) * 10))  //Character b - check if crit
				{
					b_rawDamage *= 2;
				}
				if (b_rawDamage < player_defense)
					b_damage = 0;
				else
					b_damage = (b_rawDamage - player_defense);

				if (b_damage > player_health)
					b_damage = player_health;
			}
			else
				b_damage = 0;

			player_health -= b_damage;  //Dealing dmg
			b_health -= player_damage;

			clear();
			printw("%s zadaje %d obrazen %s\n", player->getCharName(), player_damage, b.getCharName());
			printw("%s zadaje %d obrazen %s\n\n", b.getCharName(), b_damage, player->getCharName());

			printw("Punkty zycia %s: %d\n", player->getCharName(), player_health);
			printw("Punkty zycia %s: %d\n", b.getCharName(), b_health);

			if (player_health == 0 || b_health == 0)  //When Character has 0 health
			{
				player->setValue(Character::setHealth, player_health);
				(mob->second).setValue(Character::setHealth, b_health);
				clear();
				if (player_health == 0)
					printw("Wygrywa: %s", b.getCharName());
				else
				{
					printw("Wygrywa: %s", player->getCharName());
					currentTile.tileMobs.erase(mob);
				}
				state = GAME;
				break;
			}
			refresh();
			wait(1);
		}
	}
	else
		printw("Z kim chcesz walczyc?\n");
}

void Game::playerInfo()
{
	printw("Imie: %s\nRasa: %s\nKlasa: %s\n", player->getCharName(), player->getRace(), player->getClass());
	printw("X: %d\nY: %d\n", player->getValue(Character::CORDX), player->getValue(Character::CORDY));
}

void Game::goToMenu()
{
	state = MENU;
	saveGame();
}

void Game::move_north()
{
	auto cordinates = AllTiles.find({ player->getValue(Character::CORDX), (player->getValue(Character::CORDY) + 1) });
	if (cordinates != AllTiles.end())
	{
		player->setValue(Character::CORDY_plus, 1);
		currentTile = cordinates->second;
		look();
	}
	else
	{
		attron(A_REVERSE);
		printw("Nie mozesz sie tam ruszyc!\n\n");
		attroff(A_REVERSE);
	}
}

void Game::move_south()
{
	auto cordinates = AllTiles.find({ player->getValue(Character::CORDX), (player->getValue(Character::CORDY) - 1)});
	if (cordinates != AllTiles.end())
	{
		player->setValue(Character::CORDY_minus, 1);
		currentTile = cordinates->second;
		look();
	}
	else
	{
		attron(A_REVERSE);
		printw("Nie mozesz sie tam ruszyc!\n\n");
		attroff(A_REVERSE);
	}
}

void Game::move_west()
{
	auto cordinates = AllTiles.find({ (player->getValue(Character::CORDX) - 1), player->getValue(Character::CORDY) });
	if (cordinates != AllTiles.end())
	{
		player->setValue(Character::CORDX_minus, 1);

		currentTile = cordinates->second;
		look();
	}
	else
	{
		attron(A_REVERSE);
		printw("Nie mozesz sie tam ruszyc!\n\n");
		attroff(A_REVERSE);
	}
}

void Game::move_east()
{
	auto cordinates = AllTiles.find({ (player->getValue(Character::CORDX) + 1), player->getValue(Character::CORDY) });
	if (cordinates != AllTiles.end())
	{
		player->setValue(Character::CORDX_plus, 1);
		currentTile = cordinates->second;
		look();
	}

	else
	{
		attron(A_REVERSE);
		printw("Nie mozesz sie tam ruszyc!\n\n");
		attroff(A_REVERSE);
	}
}

void Game::look()
{
	attron(COLOR_PAIR(3));
	printw("%s\n", currentTile.getCharName());
	attroff(COLOR_PAIR(3));

	attron(COLOR_PAIR(2));
	printw("%s\n\n", currentTile.getDesc());
	attroff(COLOR_PAIR(2));
}
